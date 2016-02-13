/* This file is part of gconjugue
 **
 ** It is distributed under the GNU General Public License.
 ** See the file COPYING for details.
 ** 
 ** (c) 2005-2016 Jakson Aquino: jalvesaq@gmail.com
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

static void initialize(int argc, char *argv[])
{
#ifdef ENABLE_NLS
    bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);
#endif
    setlocale(LC_ALL, "");

    read_verbs_file();
    if(argc > 1){
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
                printf(_("Usage:"));
                printf("\n\n  %s [%s]\n", argv[0], _("verb"));
                printf("  %s -h | --help\n", argv[0]);
                printf("  %s -v | --version\n", argv[0]);
                printf("  %s -t                %s\n\n", argv[0], _("Conjugate all verbs and exit"));
                exit(0);
            }
            if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0){
                printf("gconjugue - %s\n", VERSION);
                exit(0);
            }
            if(strcmp(argv[i], "-t") == 0){
                conjugue_all();
                exit(0);
            }
        }
    }

    if(argc == 2 || argc == 3){
        char *b1 = (char*)malloc(30000 * sizeof(char));
        char *b2 = (char*)malloc(40000 * sizeof(char));

        if(argv[1][0] == '-')
            conjugue(argv[2], b1);
        else
            conjugue(argv[1], b1);

        if(argc == 2){
            clean_text_buffer(b2, b1);
        } else if(argc == 3){
            if(strcmp(argv[1], "--color") == 0 || strcmp(argv[1], "-c") == 0 ||
                    strcmp(argv[2], "--color") == 0 || strcmp(argv[2], "-c") == 0){
                color_text_buffer(b2, b1);
            } else if(strcmp(argv[1], "--xml") == 0 || strcmp(argv[1], "-x") == 0 ||
                    strcmp(argv[2], "--xml") == 0 || strcmp(argv[2], "-x") == 0){
                xml_text_buffer(b2, b1);
            } else {
                free(b1);
                fprintf(stderr, _("Invalid option for setting the output!\n"));
                exit(1);
            }
        }

        printf("%s\n", b2);
        free(b1);
        free(b2);
        exit(0);
    } else if(argc > 3){
        fprintf(stderr, _("Too many arguments to gconjugue!\n"));
        exit(1);
    }

    setlocale(LC_ALL, "");

    gtk_init(&argc, &argv);
    create_main_window();
}

int main(int argc, char *argv[])
{
    initialize(argc, argv);
    gtk_main();
    return 0;
}

