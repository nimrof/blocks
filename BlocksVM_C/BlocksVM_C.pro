TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.c \
    blVM.c \
    blHash.c \
    blFunctionList.c \
    blCall.c

HEADERS += \
    config.h \
    blVM.h \
    BlocksType.h \
    Blocks.h \
    blHash.h \
    blFunctionList.h \
    blCall.h

