TEMPLATE = app
TARGET = npg
QT += core \
    gui \
    xml
CONFIG += qt \
    debug
RESOURCES += npg.qrc
TRANSLATIONS = npg_zh_CN.ts
UI_DIR = ./ui
MOC_DIR = ./tmp
OBJECTS_DIR = ./tmp

unix:QMAKE_CXXFLAGS += -std=c++0x

# Input
HEADERS += config.h \
    logger.h \
    lib/windows.h \
    lib/linux.h \
    lib/features.h \
    lib/os.h \
    lib/types.h \
    lib/socket/ethernet.h \
    lib/socket/ip.h \
    lib/socket/ip_address.h \
    lib/socket/ip_raw_socket.h \
    lib/socket/net/ethernet.h \
    lib/socket/net/if_arp.h \
    lib/socket/net/if_ether.h \
    lib/socket/net/ip.h \
    lib/socket/net/ip_icmp.h \
    lib/socket/net/udp.h \
    lib/socket/raw_udp.h \
    lib/socket/socket.h \
    lib/socket/socket_toolkit.h \
    lib/socket/tcp.h \
    lib/socket/udp.h \
    protocol/bit_builder.h \
    protocol/category.h \
    protocol/field.h \
    protocol/protocol.h \
    protocol/protocol_factory.h \
    protocol/protocol_builder.h \
    tools/converter.h \
    tools/ip_converter.h \
    tools/time_converter.h \
    tools/hex_converter.h \
    tools/base64_converter.h \
    widget/about_dialog.h \
    widget/base_protocol_widget.h \
    widget/converter_dialog.h \
    widget/data_tab_sheet.h \
    widget/ethernet_widget.h \
    widget/field_select_dialog.h \
    widget/ip_widget.h \
    widget/main_list_widget.h \
    widget/main_tab_widget.h \
    widget/protocol_tab_sheet.h \
    widget/protocol_tree_item_widget.h \
    widget/protocol_tree.h \
    widget/tab_sheet.h \
    widget/tcp_response_dialog.h \
    widget/tcp_widget.h \
    widget/udp_widget.h \
    npg_define.h \
    send_thread.h \
    npg.h
FORMS += ui/ethernet_widget.ui \
    ui/field_select_dialog.ui \
    ui/tcp_response_dialog.ui \
    ui/protocol_widget.ui \
    ui/npg.ui \
    ui/tcp_widget.ui \
    ui/ip_widget.ui \
    ui/protocol_tree_item.ui \
    ui/udp_widget.ui \
    ui/converter_dialog.ui \
    ui/about_dialog.ui
SOURCES += logger.cpp \
    lib/socket/ethernet.cpp \
    lib/socket/ethernet_pcap.cpp \
    lib/socket/ip.cpp \
    lib/socket/ip_address.cpp \
    lib/socket/ip_raw_socket.cpp \
    lib/socket/raw_udp.cpp \
    lib/socket/socket_toolkit.cpp \
    lib/socket/tcp.cpp \
    lib/socket/udp.cpp \
    protocol/bit_builder.cpp \
    protocol/category.cpp \
    protocol/field.cpp \
    protocol/protocol.cpp \
    protocol/protocol_factory.cpp \
    protocol/protocol_builder.cpp \
    tools/converter.cpp \
    tools/ip_converter.cpp \
    tools/time_converter.cpp \
    tools/hex_converter.cpp \
    tools/base64_converter.cpp \
    widget/about_dialog.cpp \
    widget/base_protocol_widget.cpp \
    widget/converter_dialog.cpp \
    widget/data_tab_sheet.cpp \
    widget/ethernet_widget.cpp \
    widget/field_select_dialog.cpp \
    widget/ip_widget.cpp \
    widget/main_list_widget.cpp \
    widget/main_tab_widget.cpp \
    widget/protocol_tab_sheet.cpp \
    widget/protocol_tree_item_widget.cpp \
    widget/protocol_tree.cpp \
    widget/tab_sheet.cpp \
    widget/tcp_response_dialog.cpp \
    widget/tcp_widget.cpp \
    widget/udp_widget.cpp \
    send_thread.cpp \
    npg.cpp \
    main.cpp
