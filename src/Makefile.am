lib_LTLIBRARIES = libkonio.la

libkonio_la_SOURCES = \
    konio.h \
		kutil.c \
    writer/writer.c \
    reader/reader.c \
		directory/directory.c


AM_CPPFLAGS = -I$(KCORE_DIR)/src
LDADD = $(KCORE_DIR)/.libs/libkcore.a

libkonio_la_LDFLAGS = -version-info 0:0:0

include_HEADERS = konio.h

