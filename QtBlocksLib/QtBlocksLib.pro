#-------------------------------------------------
#
# Project created by QtCreator 2012-05-20T14:48:18
#
#-------------------------------------------------

QT       += core xml xmlpatterns

QT       -= gui

TARGET = QtBlocksLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    pindefinition.cpp \
    pin.cpp \
    script.cpp \
    library.cpp \
    project.cpp \
    exceptions.cpp \
    constant.cpp \
    blockvariable.cpp \
    calldefinition.cpp \
    call.cpp \
    block.cpp

HEADERS += \
    pindefinition.h \
    pin.h \
    script.h \
    library.h \
    project.h \
    blockvariable.h \
    exceptions.h \
    constant.h \
    calldefinition.h \
    call.h \
    block.h \
    blocks.h \
    interface/deviceconnection.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
