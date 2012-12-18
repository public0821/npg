/*
 * ip_combobox.cpp
 *
 *  Created on: 2012-12-18
 *      Author: Young <public0821@gmail.com>
 */

#include "ip_combobox.h"
#include "lib/socket/toolkit.h"
#include "logger.h"

Q_DECLARE_METATYPE(IpAddress)

IpComboBox::IpComboBox(QWidget*parent):QComboBox(parent){
	SocketToolkit toolkit;
	std::vector<IpAddress> ipaddrs = toolkit.ipAddressInfo();
	for (size_t i = 0; i < ipaddrs.size(); i++) {
		const IpAddress& addr = ipaddrs.at(i);
		std::string addr_str = addr.to_string();
		if (addr_str.size() > 0) {
			addItem(addr_str.c_str(), QVariant::fromValue(addr));
		}
	}
}

IpComboBox::~IpComboBox()
{
	// TODO Auto-generated destructor stub
}

IpAddress IpComboBox::getIpAddress(){
	return itemData(currentIndex()).value<IpAddress>();
}

