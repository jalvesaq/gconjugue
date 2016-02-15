## Process this file with automake to produce Makefile.in
## Based on script created by Anjuta

SUBDIRS = src po

verbdir = $(libdir)/gconjugue
verb_DATA = data/paradigms_and_verbs

gconjuguedocdir = ${prefix}/share/doc/gconjugue
gconjuguedoc_DATA = README.md

man_MANS =

if TUI
  man_MANS += data/conjugar.1
endif

if GTKGUI
  man_MANS += data/gconjugue.1
  desktopdir = $(datadir)/applications
  desktop_DATA = data/gconjugue.desktop
  appicondir = $(datadir)/pixmaps
  appicon_DATA = data/gconjugue.png
endif

EXTRA_DIST = $(gconjuguedoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache

# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(gconjuguedocdir)

dist-hook:
	if test -d data; then \
	  mkdir $(distdir)/data; \
	  for pixmap in data/*; do \
	    if test -f $$pixmap; then \
	      cp -p $$pixmap $(distdir)/data; \
	    fi \
	  done \
	fi

