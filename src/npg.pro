TEMPLATE = app
TARGET = npg
QT += core \
    gui \
    xml

# Input
HEADERS += npg.h \
    send_thread.h \
    socket/arp.h \
    socket/dns.h \
    socket/icmp.h \
    socket/ip_raw_socket.h \
    socket/protocol/ethernet.h \
    socket/protocol/if_arp.h \
    socket/protocol/if_ether.h \
    socket/protocol/ip.h \
    socket/protocol/ip_icmp.h \
    socket/protocol/udp.h \
    socket/raw_udp.h \
    socket/socket_error.h \
    socket/socket_public.h \
    socket/socket_toolkit.h \
    socket/tcp.h \
    socket/udp.h \
    system/features.h \
    system/os.h \
    system/os_windows.h \
    system/types.h \
    widget/arp_widget.h \
    widget/dns_widget.h \
    widget/icmp_widget.h \
    widget/main_list_widget.h \
    widget/main_tab_widget.h \
    widget/npg_define.h \
    widget/tab_sheet.h \
    widget/tcp_widget.h \
    widget/udp_widget.h
FORMS += ui/arp_widget.ui \
    ui/dns_widget.ui \
    ui/icmp_widget.ui \
    ui/npg.ui \
    ui/tcp_widget.ui \
    ui/udp_widget.ui
SOURCES += main.cpp \
    npg.cpp \
    send_thread.cpp \
    socket/arp.cpp \
    socket/arp_pacp.cpp \
    socket/dns.cpp \
    socket/icmp.cpp \
    socket/ip_raw_socket.cpp \
    socket/raw_udp.cpp \
    socket/socket_error.cpp \
    socket/socket_toolkit.cpp \
    socket/tcp.cpp \
    socket/udp.cpp \
    widget/arp_widget.cpp \
    widget/dns_widget.cpp \
    widget/icmp_widget.cpp \
    widget/main_list_widget.cpp \
    widget/main_tab_widget.cpp \
    widget/tab_sheet.cpp \
    widget/tcp_widget.cpp \
    widget/udp_widget.cpp
RESOURCES += npg.qrc
