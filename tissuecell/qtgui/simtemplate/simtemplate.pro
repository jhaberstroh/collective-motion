include(simtemplate.pri)
include(../rasterwindow/rasterwindow.pri)
include(../../src/module.pri)

# work-around for QTBUG-13496
CONFIG += no_batch


QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp

target.path = ../simtemplate
INSTALLS += target
