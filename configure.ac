dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(gconjugue, 0.8.3)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign])

AM_SILENT_RULES([yes])

AC_PROG_CC

AC_ARG_ENABLE([gtkgui],
              [  --enable-gtkgui    Build gtk gui],
              [case "${enableval}" in
               yes) gtkgui=true ;;
               no)  gtkgui=false ;;
               *) AC_MSG_ERROR([bad value ${enableval} for --enable-gtkgui]) ;;
           esac],[gtkgui=true])
AM_CONDITIONAL([GTKGUI], [test x$gtkgui = xtrue])

AC_ARG_ENABLE([tui],
              [  --enable-tui    Build text interface],
              [case "${enableval}" in
               yes) tui=true ;;
               no)  tui=false ;;
               *) AC_MSG_ERROR([bad value ${enableval} for --enable-tui]) ;;
           esac],[tui=true])
AM_CONDITIONAL([TUI], [test x$tui = xtrue])


dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=gconjugue
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])

AM_GLIB_GNU_GETTEXT

LT_INIT

AS_CASE(["$gtkgui"],
        [true], [PKG_CHECK_MODULES(GTK3, [gtk+-3.0 ])],
        [false], [],
        [PKG_CHECK_MODULES(GTK3, [gtk+-3.0 ])])

AS_CASE(["$tui"],
        [true], [AC_DEFINE(TUI, "1", "Enable TUI")],
        [false], [],
        [AC_DEFINE(TUI, "1", "Enable TUI")])

AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
])
