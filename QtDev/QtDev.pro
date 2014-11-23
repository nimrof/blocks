#-------------------------------------------------
#
# Project created by QtCreator 2012-05-20T10:40:19
#
#-------------------------------------------------

QT       += core gui xml xmlpatterns
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtDev
TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    blockconnectionitem.cpp \
    blockviewer.cpp \
    graphicsblockitem.cpp \
    projecttreeitem.cpp \
    projecttreemodel.cpp \
    scripteditor.cpp \
    graphicscallitem.cpp \
    graphicsconstitem.cpp \
    graphicstextedititem.cpp \
    scripteditorundocommands.cpp \
    pluginmanager.cpp \
    graphicspinitem.cpp

HEADERS  += mainwindow.h \
    blockconnectionitem.h \
    blockviewer.h \
    graphicsblockitem.h \
    projecttreeitem.h \
    projecttreemodel.h \
    scripteditor.h \
    graphicscallitem.h \
    graphicsconstitem.h \
    graphicstextedititem.h \
    blocksGraphicsTypes.h \
    scripteditorundocommands.h \
    pluginmanager.h \
    graphicspinitem.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    default.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtBlocksLib/ -lQtBlocksLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtBlocksLib/ -lQtBlocksLibd
else:unix: LIBS += -L$$OUT_PWD/../QtBlocksLib/ -lQtBlocksLib

INCLUDEPATH += $$PWD/../QtBlocksLib
DEPENDPATH += $$PWD/../QtBlocksLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QtBlocksLib/libQtBlocksLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QtBlocksLib/libQtBlocksLibd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QtBlocksLib/QtBlocksLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QtBlocksLib/QtBlocksLibd.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../QtBlocksLib/libQtBlocksLib.a
