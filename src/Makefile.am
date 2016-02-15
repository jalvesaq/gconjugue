## Process this file with automake to produce Makefile.in

AM_CFLAGS = -Wall -g

bin_PROGRAMS = 

if TUI
  bin_PROGRAMS += conjugar
endif

if GTKGUI
  bin_PROGRAMS += gconjugue
endif

AM_CPPFLAGS = \
	      -DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	      -DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	      -DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	      -DPACKAGE_LIB_DIR=\""$(libdir)/gconjugue"\" \
	      $(GTK3_CFLAGS)

conjugar_CPPFLAGS = \
		    -DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
		    -DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
		    -DPACKAGE_DATA_DIR=\""$(datadir)"\" \
		    -DPACKAGE_LIB_DIR=\""$(libdir)/gconjugue"\"

gconjugue_SOURCES = \
	gmain.c \
	interface.c interface.h \
	callbacks.c callbacks.h \
	conjugue.c conjugue.h

conjugar_SOURCES = main.c conjugue.c conjugue.h

# Avoids a compiler-flags-hidden warning.
export V=1

conjugar_LDADD =

conjugar_CFLAGS =

conjugar_LDFLAGS = \
	-Wl,--export-dynamic \
	-Wl,--as-needed

gconjugue_LDFLAGS = \
	-Wl,--export-dynamic \
	-Wl,--as-needed

gconjugue_LDADD = $(GTK3_LIBS)

