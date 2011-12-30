TEMPLATE = app
TARGET = npg
QT += core \
    gui \
    xml \
    webkit

# Input
HEADERS += protocol/bit_builder.h \
    socket/ethernet.h \
    widget/ethernet_widget.h \
    widget/field_select_dialog.h \
    widget/tcp_response_dialog.h \
    widget/protocol_tree_item.h \
    system/os_linux.h \
    widget/protocol_tree.h \
    protocol/category.h \
    protocol/field.h \
    protocol/protocol.h \
    protocol/protocol_factory.h \
    system/error.h \
    socket/net/ethernet.h \
    socket/net/if_arp.h \
    socket/net/if_ether.h \
    socket/net/ip.h \
    socket/net/ip_icmp.h \
    socket/net/udp.h \
    npg.h \
    send_thread.h \
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
    widget/main_list_widget.h \
    widget/main_tab_widget.h \
    widget/tab_sheet.h \
    widget/tcp_widget.h \
    widget/base_protocol_widget.h \
    widget/data_tab_sheet.h \
    widget/ip_widget.h \
    widget/protocol_tab_sheet.h \
    widget/udp_widget.h
FORMS += ui/ethernet_widget.ui \
    ui/field_select_dialog.ui \
    ui/tcp_response_dialog.ui \
    ui/protocol_widget.ui \
    ui/npg.ui \
    ui/tcp_widget.ui \
    ui/ip_widget.ui \
    ui/protocol_tree_item.ui \
    ui/udp_widget.ui
SOURCES += protocol/bit_builder.cpp \
    socket/ethernet.cpp \
    socket/ethernet_pcap.cpp \
    widget/ethernet_widget.cpp \
    widget/field_select_dialog.cpp \
    widget/tcp_response_dialog.cpp \
    logger.cpp \
    protocol/protocol_builder.cpp \
    socket/ip.cpp \
    widget/base_protocol_widget.cpp \
    widget/data_tab_sheet.cpp \
    widget/ip_widget.cpp \
    widget/protocol_tab_sheet.cpp \
    widget/protocol_tree_item.cpp \
    widget/protocol_tree.cpp \
    protocol/category.cpp \
    protocol/field.cpp \
    protocol/protocol.cpp \
    protocol/protocol_factory.cpp \
    system/error.cpp \
    main.cpp \
    npg.cpp \
    send_thread.cpp \
    socket/ip_raw_socket.cpp \
    socket/raw_udp.cpp \
    socket/socket_toolkit.cpp \
    socket/tcp.cpp \
    socket/udp.cpp \
    widget/main_list_widget.cpp \
    widget/main_tab_widget.cpp \
    widget/tab_sheet.cpp \
    widget/tcp_widget.cpp \
    widget/udp_widget.cpp
RESOURCES += npg.qrc
