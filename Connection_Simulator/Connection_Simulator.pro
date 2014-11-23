#-------------------------------------------------
#
# Project created by QtCreator 2012-08-20T00:00:26
#
#-------------------------------------------------

#QT       -= core gui
QT       = core gui

TARGET = Connection_Simulator
TEMPLATE = lib
VERSION = 1.0.0

CONFIG += plugin

DEFINES += CONNECTION_SIMULATOR_LIBRARY

SOURCES += connection_simulator.cpp \

HEADERS +=\
    connection_simulator.h \
    ../QtBlocksLib/interface/deviceconnection.h

HEADERS += ../lib/angelscript_2.24.1/sdk/angelscript/include/angelscript.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_array.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_builder.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_bytecode.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_bytecodedef.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_compiler.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_config.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_configgroup.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_context.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_datatype.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_debug.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_generic.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_map.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_memory.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_module.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_objecttype.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_outputbuffer.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_parser.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_property.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_restore.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_scriptcode.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_scriptengine.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_scriptfunction.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_scriptnode.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_scriptobject.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_string.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_string_util.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_texts.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_thread.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_tokendef.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_tokenizer.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_typeinfo.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_variablescope.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_gc.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_criticalsection.h \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_arm_xcode.S \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_arm_gcc.S \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_atomic.h

SOURCES += ../lib/angelscript_2.24.1/sdk/angelscript/source/as_atomic.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_builder.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_bytecode.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_mips.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_sh4.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_x86.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_compiler.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_configgroup.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_context.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_datatype.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_gc.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_generic.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_globalproperty.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_memory.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_module.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_objecttype.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_outputbuffer.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_parser.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_restore.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_scriptcode.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_scriptengine.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_scriptfunction.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_scriptnode.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_scriptobject.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_string.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_string_util.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_thread.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_tokenizer.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_typeinfo.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_variablescope.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_xenon.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_x64_msvc.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_x64_mingw.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_x64_gcc.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_ppc_64.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_ppc.cpp \
           ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_arm.cpp

OTHER_FILES += \
    ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_x64_msvc_asm.asm \
    ../lib/angelscript_2.24.1/sdk/angelscript/source/as_callfunc_arm_msvc.asm
