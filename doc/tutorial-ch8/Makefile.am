
if TUTORIAL

noinst_PROGRAMS = mhd-example

if DEBUG
MORE_LIBS =
AM_CFLAGS = -include config.h -g3 -ggdb -O0 $(DEPS_CFLAGS)
mhd_example_SOURCES = main.c \
		      answer.c \
		      bad_method.c \
		      base64.c \
		      daemon_state.c \
		      forbidden.c \
		      html_encode.c \
		      method_options.c \
		      multi_form.c \
		      not_found.c \
		      request_cleanup.c \
		      request_state.c \
		      server_error.c \
		      service_unavailable.c \
		      session.c \
		      debug.c
else
MORE_LIBS =
AM_CFLAGS = -include config.h $(DEPS_CFLAGS)
mhd_example_SOURCES = main.c \
		      answer.c \
		      bad_method.c \
		      base64.c \
		      daemon_state.c \
		      forbidden.c \
		      html_encode.c \
		      method_options.c \
		      multi_form.c \
		      not_found.c \
		      request_cleanup.c \
		      request_state.c \
		      server_error.c \
		      service_unavailable.c \
		      session.c 
endif

endif

LIBS = $(DEPS_LIBS) -lm -lJudy $(MORE_LIBS)

