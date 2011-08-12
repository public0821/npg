TEMPLATE = app
TARGET = npg
QT += core \
    gui \
    xml
HEADERS += type_item.h \
    socket/udp.h \
    socket/public.h \
    udp_widget.h \
    npg.h
SOURCES += type_item.cpp \
    socket/udp.cpp \
    udp_widget.cpp \
    main.cpp \
    npg.cpp
FORMS += udp_widget.ui \
    npg.ui
RESOURCES += npg.qrc
