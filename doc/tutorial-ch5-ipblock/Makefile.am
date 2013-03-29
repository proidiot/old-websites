
LIBS = $(DEPS_LIBS) -L/usr/local/lib -lJudy

if TUTORIAL

noinst_PROGRAMS = mhd-example

if DEBUG
AM_CFLAGS = -g3 -ggdb -O0 $(DEPS_CFLAGS)
mhd_example_SOURCES = main.c answer.c connect.c badlist.c debug.c
else
AM_CFLAGS = $(DEPS_CFLAGS)
mhd_example_SOURCES = main.c answer.c connect.c badlist.c
endif

endif

