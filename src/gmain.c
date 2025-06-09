/* This file is part of gconjugue
 **
 ** It is distributed under the GNU General Public License.
 ** See the file COPYING for details.
 ** 
 ** (c) 2005-2025 Jakson Aquino: jalvesaq@gmail.com
 **
 ***************************************************************/

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "conjugue.h"
extern void create_main_window(); // interface.c

int main(int argc, char *argv[])
{
#ifdef ENABLE_NLS
    bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);
#endif
    setlocale(LC_ALL, "");
    read_verbs_file();
    gtk_init(&argc, &argv);
    create_main_window();
    gtk_main();
    return 0;
}

