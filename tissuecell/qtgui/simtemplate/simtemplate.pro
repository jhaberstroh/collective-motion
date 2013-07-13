include(../rasterwindow/rasterwindow.pri)
include(simtemplate.pri)

# work-around for QTBUG-13496
CONFIG += no_batch

SOURCES += \
    main.cpp

target.path = ../simtemplate
INSTALLS += target
