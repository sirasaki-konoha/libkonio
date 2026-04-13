lib_LTLIBRARIES = libkonio.la

libkonio_la_SOURCES = \
    konio.h \
		kutil.c \
    writer/writer.c \
    reader/reader.c \
		directory/directory.c

libkonio_la_CPPFLAGS = $(KCORE_CPPFLAGS)

libkonio_la_LIBADD = $(KCORE_LDADD)

libkonio_la_LDFLAGS = -version-info 0:0:0

include_HEADERS = konio.h

