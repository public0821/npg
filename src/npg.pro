TEMPLATE = app
TARGET = npg
QT += core \
    gui \
    xml

# Input
HEADERS += system/os_linux.h \
    widget/protocol_tree.h \
    protocol/category.h \
    protocol/field.h \
    protocol/protocol.h \
    protocol/protocol_factory.h \
    system/error.h \
    widget/protocol_widget.h \
    protocol/dns.h \
    socket/net/ethernet.h \
    socket/net/if_arp.h \
    socket/net/if_ether.h \
    socket/net/ip.h \
    socket/net/ip_icmp.h \
    socket/net/udp.h \
    npg.h \
    send_thread.h \
    socket/arp.h \
    socket/icmp.h \
    socket/ip_raw_socket.h \
    socket/raw_udp.h \
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
FORMS += ui/protocol_widget.ui \
    ui/arp_widget.ui \
    ui/dns_widget.ui \
    ui/icmp_widget.ui \
    ui/npg.ui \
    ui/tcp_widget.ui \
    ui/udp_widget.ui
SOURCES += widget/protocol_tree.cpp \
    protocol/category.cpp \
    protocol/field.cpp \
    protocol/protocol.cpp \
    protocol/protocol_factory.cpp \
    system/error.cpp \
    widget/protocol_widget.cpp \
    protocol/dns.cpp \
    main.cpp \
    npg.cpp \
    send_thread.cpp \
    socket/arp.cpp \
    socket/arp_pacp.cpp \
    socket/icmp.cpp \
    socket/ip_raw_socket.cpp \
    socket/raw_udp.cpp \
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
