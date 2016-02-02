## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LIB_DIR=\""$(libdir)/gconjugue"\" \
	$(GCONJUGUE_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = gconjugue

gconjugue_SOURCES = \
	main.c \
	interface.c interface.h \
	callbacks.c callbacks.h \
	conjugue.c conjugue.h

# Avoids a compiler-flags-hidden warning.
export V=1

gconjugue_LDFLAGS = \
	-Wl,--export-dynamic \
	-Wl,--as-needed

gconjugue_LDADD = $(GCONJUGUE_LIBS)

