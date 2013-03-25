
if TUTORIAL

if DEBUG
AM_CFLAGS = -g3 -ggdb -O0 $(DEPS_CFLAGS)
else
AM_CFLAGS = $(DEPS_CFLAGS)
endif

LIBS = $(DEPS_LIBS)

noinst_PROGRAMS = mhd-example

mhd_example_SOURCES = main.c answer.c onconnect.c

endif

