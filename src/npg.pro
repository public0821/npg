TEMPLATE = app
TARGET = npg
QT += core \
    gui \
    xml
HEADERS += icmp_widget.h\
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
SOURCES += icmp_widget.cpp\
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
FORMS += icmp_widget.ui\
	tcp_widget.ui \
    udp_widget.ui \
    npg.ui
RESOURCES += npg.qrc \
    npg.qrc
