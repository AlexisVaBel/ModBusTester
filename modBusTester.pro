TEMPLATE=app

QT+=core
CONFIG+=qt

TARGET=modBusTester

SOURCES += \
    main.cpp \
    modbus/modbusregister.cpp \
    modbus/modbusprocs.cpp \
    yaml/yaml_parser.cpp

OTHER_FILES += \
    serial/qextserialport.pri
    include (./serial/qextserialport.pri)

HEADERS += \
    modbus/modbusregister.h \
    modbus/modbusprocs.h \
    yaml/yaml_parser.h
