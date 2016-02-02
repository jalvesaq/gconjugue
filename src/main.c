/* This file is part of gconjugue
**
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2005-2011 Jakson Aquino: jalvesaq@gmail.com
**
***************************************************************/

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "conjugue.h"

GtkWidget *window1;
int initHeight = 550, initWidth = 300;
char *confFileName;
extern void conjugar(const char *vrb, GtkTextBuffer *b);

void initialize(int argc, char *argv[])
{
#ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif

  read_verbs_file();
  int i;
  if(argc > 1){
    for(i = 1; i < argc; i++){
      if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
	printf(_("Usage:"));
	printf("\n\n  %s [%s]\n", argv[0], _("verb"));
	printf("  %s -h | --help\n", argv[0]);
	printf("  %s -v | --version\n", argv[0]);
	printf("  %s -t                %s\n\n",argv[0], _("Conjugate all verbs and exit"));
	exit(0);
      }
      if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0){
	printf("gconjugue - %s\n", VERSION);
	exit(0);
      }
      if(strcmp(argv[i], "-t") == 0){
	compare();
	exit(0);
      }
    }
  }

  if(argc > 1){
    char *b1 = (char*)malloc(20000 * sizeof(char));
    char *b2 = (char*)malloc(20000 * sizeof(char));
    conjugue(argv[1], b1);
    cleanTextBuffer(b2, b1);
    printf("%s\n", b2);
    free(b1);
    free(b2);
    exit(0);
  }

  setlocale (LC_ALL, "");
  gtk_init (&argc, &argv);

  window1 = create_window1 ();

  /* Set the window dimensions */
  confFileName = g_strdup_printf("%s/%s", g_get_home_dir(), ".gconjugue");
  FILE *F = fopen(confFileName, "r");
  if(F){
    char s[128];
    char b[128];
    i = 0;
    while(fgets(s, 127, F)){
      if(s[0] == '#' || strlen(s) < 6)
	continue;
      i = 0;
      snprintf(b, 127, "height = %%d\n");
      if(sscanf(s, b, &i) == 1 && i > 100 && i < 1000)
	initHeight = i;
      i = 0;
      snprintf(b, 127, "width = %%d\n");
      if(sscanf(s, b, &i) == 1 && i > 100 && i < 1500)
	initWidth = i;
    }
    fclose(F);
  }

  gtk_window_set_default_size((GtkWindow*)window1, initWidth, initHeight);
  gtk_text_view_set_wrap_mode((GtkTextView*)textview1, GTK_WRAP_WORD);
  GtkTextBuffer *buf =  gtk_text_view_get_buffer((GtkTextView*)textview1);
  gtk_text_buffer_create_tag(buf, "bold", "weight", PANGO_WEIGHT_BOLD, NULL);
  gtk_text_buffer_create_tag(buf, "red", "foreground", "red", NULL);
  gtk_text_buffer_create_tag(buf, "blue", "foreground", "blue", NULL);
  gtk_text_buffer_create_tag(buf, "large", "scale", PANGO_SCALE_LARGE, NULL);
  gtk_widget_show (window1);
}

int main (int argc, char *argv[]){
  initialize(argc, argv);
  gtk_main ();
  return 0;
}

