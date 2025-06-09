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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "conjugue.h"

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
                printf("\n\n  %s [%s] %s\n", argv[0], _("output options"), _("verb"));
                printf("  %s -h | --help\n", argv[0]);
                printf("  %s -v | --version\n", argv[0]);
                printf("  %s -t                %s\n\n", argv[0], _("Conjugate all verbs and exit"));
                printf(_("Output options:"));
                printf("\n\n  --color              %s\n", _("Color output"));
                printf("  --xml                %s\n", _("Add XML tags to output"));
                printf("  --common             %s\n", _("Conjugate verbs as ordinary Brazilians do"));
                exit(0);
            }
            if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0){
                printf("conjugar - %s\n", VERSION);
                exit(0);
            }
            if(strcmp(argv[i], "-t") == 0){
                conjugue_all();
                exit(0);
            }
        }
    }

    if(argc > 1 && argc < 5){
        char *b1 = (char*)malloc(30000 * sizeof(char));
        char *b2 = (char*)malloc(40000 * sizeof(char));
        int xml = 0;
        int col = 0;

        for(int i = 1; i < argc; i++)
            if(argv[i][0] == '-' && argv[i][1] == '-'){
                if(strcmp(argv[i], "--color") == 0)
                    col = 1;
                else if(strcmp(argv[i], "--xml") == 0)
                    xml = 1;
                else if(strcmp(argv[i], "--common") == 0)
                    Normative = 0;
                else {
                    fprintf(stderr,
                            _("Invalid option for setting the output: %s\n"),
                            argv[i]);
                    exit(1);
                }
            }

        conjugue(argv[argc - 1], b1);

        if(col)
            color_text_buffer(b2, b1);
        else if(xml)
            xml_text_buffer(b2, b1);
        else
            clean_text_buffer(b2, b1);

        printf("%s\n", b2);
        free(b1);
        free(b2);
        exit(0);
    } else if(argc > 3){
        fprintf(stderr, _("Too many arguments to conjugar!\n"));
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    initialize(argc, argv);
    return 0;
}

