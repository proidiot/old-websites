
LIBS = $(DEPS_LIBS)

if TUTORIAL

noinst_PROGRAMS = mhd-example

if DEBUG
AM_CFLAGS = -include config.h -g3 -ggdb -O0 $(DEPS_CFLAGS)
mhd_example_SOURCES = main.c answer.c bad_method.c method_options.c not_found.c request_cleanup.c server_error.c simple_form.c debug.c
else
AM_CFLAGS = -include config.h $(DEPS_CFLAGS)
mhd_example_SOURCES = main.c answer.c bad_method.c method_options.c not_found.c request_cleanup.c server_error.c simple_form.c
endif

endif

