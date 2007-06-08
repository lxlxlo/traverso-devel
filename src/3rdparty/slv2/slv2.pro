include(../../libbase.pri)

contains(DEFINES, LV2_SUPPORT) {

CONFIG -= dll qt 
CONFIG += static  create_prl
TEMPLATE = lib 
INCLUDEPATH += slv2
QMAKE_CFLAGS_DEBUG += -std=c99
QMAKE_CFLAGS_RELEASE += -std=c99
QMAKE_LIBDIR = ../../../lib 
TARGET = slv2 
DESTDIR = ../../../lib 

SOURCES += \
	src/plugin.c \
	src/pluginclass.c \
	src/pluginclasses.c \
	src/plugininstance.c \
	src/plugins.c \
	src/port.c \
	src/query.c \
	src/util.c \
	src/value.c \
	src/values.c \
	src/world.c
}

