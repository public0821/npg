TEMPLATE = app
TARGET = npg
QT += core \
    gui \
    xml
HEADERS += dns_widget.h \
    socket/dns.h \
    socket/raw_udp.h \
    socket/ip_raw_socket.h \
    socket/socket_toolkit.h \
    arp_widget.h \
    socket/arp.h \
    icmp_widget.h \
    socket/icmp.h \
    send_thread.h \
    socket/socket_public.h \
    socket/tcp.h \
    socket/socket_error.h \
    tcp_widget.h \
    tab_sheet.h \
    public.h \
    main_list_widget.h \
    main_tab_widget.h \
    npg.h \
    socket/udp.h \
    udp_widget.h
SOURCES += dns_widget.cpp \
    socket/dns.cpp \
    socket/raw_udp.cpp \
    socket/ip_raw_socket.cpp \
    socket/socket_toolkit.cpp \
    arp_widget.cpp \
    socket/arp.cpp \
    icmp_widget.cpp \
    socket/icmp.cpp \
    send_thread.cpp \
    socket/tcp.cpp \
    socket/socket_error.cpp \
    tcp_widget.cpp \
    tab_sheet.cpp \
    main_list_widget.cpp \
    main_tab_widget.cpp \
    main.cpp \
    npg.cpp \
    socket/udp.cpp \
    udp_widget.cpp
FORMS += dns_widget.ui \
    arp_widget.ui \
    icmp_widget.ui \
    tcp_widget.ui \
    udp_widget.ui \
    npg.ui
RESOURCES += npg.qrc \
    npg.qrc
