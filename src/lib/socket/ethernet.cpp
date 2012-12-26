#ifdef __GNUC__

#include "ethernet.h"
#include "socket.h"
#include <string>
#include "../../logger.h"
#include <qobject.h>
#include "ip.h"

Ethernet::Ethernet(void)
{
	m_sockfd = socket(AF_PACKET, SOCK_RAW/*SOCK_RAW*/, htons(ETH_P_ALL));
	if (-1 == m_sockfd)
	{
		LOG_ERROR(npg_errno);
	}
}

Ethernet::~Ethernet(void)
{
	if (-1 != m_sockfd)
	{
		closesocket(m_sockfd);
	}
}

bool Ethernet::sendto(const ifi_info& dev, const char* eth_to_mac, const char* eth_from_mac, uint16_t protocol, const char* data, size_t len)
{
	if (-1 == m_sockfd)
	{
		return false;
	}
	if (data == NULL)
	{
		return false;
	}

	struct sockaddr_ll remote;
	bzero(&remote, sizeof(remote));
	remote.sll_ifindex = dev.ifi_index;
	//other fields not used when send data
	//	remote.sll_family = htons(AF_PACKET);
	//	remote.sll_protocol = htons(ETH_P_ARP);
	//	remote.sll_hatype = htons(ARPHRD_ETHER);
	//	remote.sll_halen = ETH_ALEN;
	//	remote.sll_pkttype = PACKET_OTHERHOST;
	//	memcpy(remote.sll_addr, arp->arp_sha, ETH_ALEN);

	uint32_t ethernet_size = sizeof(struct ethhdr) + len;
	char* buffer = new char[ethernet_size];
	bzero(buffer, ethernet_size);
	memcpy(buffer+sizeof(struct ethhdr), data, len);

	SocketToolkit toolkit;
	struct ethhdr *ethhdr = (struct ethhdr *) buffer;
	//	memset(ethhdr->h_dest, 0xFF, sizeof(ethhdr->h_dest));
	if(!toolkit.toMac(eth_to_mac, ethhdr->h_dest))
	{
		LOG_ERROR(QObject::tr("The format is not supported: %1").arg(eth_to_mac));
		return false;
	}
	if(!toolkit.toMac(eth_from_mac, ethhdr->h_source))
	{
		LOG_ERROR(QObject::tr("The format is not supported: %1").arg(eth_from_mac));
		return false;
	}
	ethhdr->h_proto = htons(protocol);

	if(protocol == ETH_P_IP) {
		addChecksum(buffer+sizeof(struct ethhdr), len);
	}
	int ret = ::sendto(m_sockfd, buffer, ethernet_size, 0, (struct sockaddr*) &remote,
			sizeof(remote));
	if (-1 == ret)
	{
		LOG_ERROR(npg_errno);
		delete[] buffer;
		return false;
	}

	delete[] buffer;

	return true;
}

void Ethernet::addChecksum( const char* data, size_t len) {
	if(len < sizeof(struct iphdr)) {
		return;
	}

	struct iphdr* iphdr = (struct iphdr*)data;
	size_t iph_len = iphdr->ihl*4;
	if(iph_len > len) {
		return;
	}
	if(iphdr->check == 0) {
		iphdr->check = Ip::checksum(data, iphdr->ihl*4);
	}

	Ip::addChecksum(iphdr->protocol, data+iph_len, len-iph_len);
//	Ip::addChecksum(iphdr->saddr, iphdr->daddr, iphdr->protocol, data+iph_len, len-iph_len);
}

#endif
