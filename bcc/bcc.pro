#-------------------------------------------------
#
# Project created by QtCreator 2012-12-22T21:19:33
#
#-------------------------------------------------

QT       += core xml xmlpatterns
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       -= gui

TARGET   = bcc
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    compiler.cpp \
    simplecompiler.cpp \
    advancedcompiler.cpp \
    advancedthreadedcompiler.cpp \
    ast/metascript.cpp \
    ast/metabranch.cpp \
    ast/astElement.cpp \
    ast/astBranchIf.cpp \
    ast/astFunctionCall.cpp

HEADERS += \
    main.h \
    compiler.h \
    simplecompiler.h \
    advancedcompiler.h \
    advancedthreadedcompiler.h \
    ast/metascript.h \
    ast/astElement.h \
    ast/astbranch.h \
    ast/astBranchIf.h \
    ast/astFunctionCall.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtBlocksLib/release/ -lQtBlocksLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtBlocksLib/debug/ -lQtBlocksLib
else:unix: LIBS += -L$$OUT_PWD/../QtBlocksLib/ -lQtBlocksLib

INCLUDEPATH += $$PWD/../QtBlocksLib
DEPENDPATH += $$PWD/../QtBlocksLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QtBlocksLib/release/libQtBlocksLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QtBlocksLib/debug/libQtBlocksLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QtBlocksLib/release/QtBlocksLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QtBlocksLib/debug/QtBlocksLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../QtBlocksLib/libQtBlocksLib.a
