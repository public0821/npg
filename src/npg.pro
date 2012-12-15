TEMPLATE = app
TARGET = npg
QT += core \
    gui \
    xml
    
CONFIG = qt debug	#release
RESOURCES += npg.qrc
TRANSLATIONS = npg_zh_CN.ts 
UI_DIR = ./ui 
MOC_DIR = ./tmp
OBJECTS_DIR= ./tmp


unix{
    QMAKE_CXXFLAGS += -std=c++0x 
}

# Input
HEADERS += socket/socket.h \
    socket/ip_address.h \
    qerror.h \
    protocol/bit_builder.h \
    protocol/category.h \
    protocol/field.h \
    protocol/protocol.h \
    protocol/protocol_factory.h \
    protocol/protocol_builder.h \
    system/features.h \
    system/os.h \
    system/os_windows.h \
    system/types.h \
    system/os_linux.h \
    system/error.h \
    socket/net/ethernet.h \
    socket/net/if_arp.h \
    socket/net/if_ether.h \
    socket/net/ip.h \
    socket/net/ip_icmp.h \
    socket/net/udp.h \
    socket/ethernet.h \
    socket/ip_raw_socket.h \
    socket/raw_udp.h \
    socket/socket_toolkit.h \
    socket/tcp.h \
    socket/udp.h \
    socket/ip.h \
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
SOURCES += socket/ip_address.cpp \
    qerror.cpp \
    protocol/bit_builder.cpp \
    protocol/category.cpp \
    protocol/field.cpp \
    protocol/protocol.cpp \
    protocol/protocol_factory.cpp \
    protocol/protocol_builder.cpp \
    system/error.cpp \
    socket/ethernet.cpp \
    socket/ip_raw_socket.cpp \
    socket/raw_udp.cpp \
    socket/socket_toolkit.cpp \
    socket/tcp.cpp \
    socket/udp.cpp \
    socket/ip.cpp \
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
