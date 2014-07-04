TEMPLATE=app

QT+=core
CONFIG+=qt

TARGET=modBusTester

SOURCES += \
    main.cpp \
    modbus/modbusregister.cpp \
    modbus/modbusprocs.cpp \
    yaml/yamlparser.cpp \
    view/mainwindow.cpp

OTHER_FILES += \
    serial/qextserialport.pri
    include (./serial/qextserialport.pri)

HEADERS += \
    modbus/modbusregister.h \
    modbus/modbusprocs.h \
    yaml/yamlparser.h \
    view/mainwindow.h

