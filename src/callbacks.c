/* This file is part of gconjugue
**
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
**
** (c) 2005-2013 Jakson Aquino: jalvesaq@gmail.com
**
***************************************************************/

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "callbacks.h"
#include "interface.h"
#include "conjugue.h"


extern GtkWidget *window1;
extern int initWidth, initHeight;
extern char *confFileName;

void finish_gconjugue(){
  int h, w;

  /* Save window dimensions */
  gtk_window_get_size((GtkWindow*)window1, &w, &h);
  if(w != initWidth || h != initHeight){
    FILE *F = fopen(confFileName, "w");
    if(F){
      fprintf(F, "height = %d\n", h);
      fprintf(F, "width = %d\n", w);
      fclose(F);
    } else{
      fprintf(stderr,
	  _("gconjugue: could not write configuration file \"%s\".\n"),
	  confFileName);
    }
  }

  gtk_main_quit();
}

void erro_fatal(char *s){
  fprintf(stderr, _("gconjugue: FATAL ERROR:\n\n%s\n"), s);
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new (GTK_WINDOW (window1), GTK_DIALOG_MODAL | 
      GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
      _("gconjugue: FATAL ERROR:\n\n%s\n"), s);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
  exit(1);
}

void on_miQuit_activate(){
  finish_gconjugue();
}

void setText(const char *str)
{
  int i, j, l;
  GtkTextBuffer *b = gtk_text_view_get_buffer((GtkTextView*)textview1);
  gtk_text_buffer_set_text(b, " ", 0);
  l = strlen(str);
  char letra;
  GtkTextIter iter;
  gtk_text_buffer_get_iter_at_offset (b, &iter, 0);
  i = 0;
  j = 0;
  while(i < l){
    if(str[i] > 0 && str[i] < 6){
      letra = str[i];
      gtk_text_buffer_insert(b, &iter, str+j, i-j);
      i++;
      j = i;
      while(str[i] != 5)
	i++;
      if(letra == 4)
	gtk_text_buffer_insert_with_tags_by_name(b, &iter, str+j, i-j,
	    "bold", NULL);
      else
	if(letra == 3)
	  gtk_text_buffer_insert_with_tags_by_name(b, &iter, str+j, i-j,
	      "blue", NULL);
	else
	  if(letra == 2)
	    gtk_text_buffer_insert_with_tags_by_name(b, &iter, str+j, i-j,
		"red", NULL);
	  else
	    if(letra == 1)
	      gtk_text_buffer_insert_with_tags_by_name(b, &iter, str+j, i-j,
		  "large", "bold", NULL);
      i++;
      j = i;
    } else
      i++;
  }
  gtk_text_buffer_insert(b, &iter, str+j, -1);
}

void on_miListP_activate(){
  char *buffer = (char*)calloc(1512000, sizeof(char));
  listPrdgms(buffer);
  setText(buffer);
  free(buffer);
}

void on_miListV_activate(){
  char *buffer = (char*)calloc(1512000, sizeof(char));
  listVerbs(buffer);
  setText(buffer);
  free(buffer);
}

void on_hcontents_activate(){
  char *str = (char*)malloc(5000 * sizeof(char));
  snprintf(str, 4999, "\n\1Ajuda\5\n\n"
      "Ao iniciar, o GConjugue carrega um banco de dados contendo verbos "
      "conjugados. Esses verbos são usados como paradigmas para a conjugação "
      "dos demais verbos presentes no banco. Alguns dos verbos estão "
      "explicitamente listados como seguidores de um dos paradigmas, mas "
      "outros estão listados apenas como verbos existentes. O programa atribui "
      "um paradigma para esses verbos, bem como a qualquer verbo digitado pelo "
      "usuário.\n\n"
      "O GConjugue apresenta a seguinte informação antes da conjugação dos "
      "verbos:\n\n"
      "\3Paradigma: <verbo>\5: Indica qual verbo serve de paradigma para a "
      "conjugação; ou o próprio verbo conjugado é um paradigma ou está "
      "explicitamente listado como seguidor do paradigma.\n\n"
      "\3Paradigma deduzido: <verbo>\5: O verbo está presente no banco, mas "
      "não está classificado. Seu paradigma foi “calculado” pelo programa.\n\n"
      "\2Não consta do banco de verbos\5: Mesmo não constando do banco de "
      "verbos, o verbo fornecido pelo usuário poderá ser conjugado se for "
      "possível calcular um paradigma para ele.\n\n"
      "\2Não sei conjugar <verbo>\5: O GConjugue não conseguiu relacionar "
      "nenhum paradigma com a expressão fornecida pelo usuário. Isto somente "
      "deve acontecer com termos cujo tratamento como verbo é impossível na "
      "língua portuguesa (palavras não terminadas com a letra ‘r’, por "
      "exemplo).\n\n"
      "O número de paradigmas existente no banco de verbos do GConjugue é "
      "superior ao número de paradigmas reconhecidos pela gramática normativa "
      "da língua portuguesa porque o algoritmo do GConjugue não consegue "
      "extrair de um mesmo conjunto de regras a conjugação correta de verbos "
      "irregulares que, nas conjugações, alteram da mesma forma a última vogal "
      "do radical, como, por exemplo, “dormir” e “tossir”, convencionalmente "
      "considerados seguidores do mesmo paradigma.\n\n"
      "Um verbo não classificado no próprio banco como seguidor de um dos "
      "paradigmas, tem seu paradigma deduzido pelo programa pela comparação da "
      "sua terminação com a de alguns verbos. As comparações são feitas na "
      "sequência abaixo e são interrompidas quando é encontrada uma "
      "coincidência de terminações:\n\n"
      "   \4çar\5  abraçar\n"
      "   \4gar\5  chegar\n"
      "   \4car\5  comunicar\n"
      "   \4oar\5  magoar\n"
      "   \4ear\5  passear\n"
      "   \4ar\5  cantar\n"
      "\n"
      "   \4cer\5  conhecer\n"
      "   \4guer\5  erguer\n"
      "   \4ger\5  proteger\n"
      "   \4er\5  vender\n"
      "\n"
      "   \4ruir\5  ruir\n"
      "   \4guir\5  extinguir\n"
      "   \4uir\5  atribuir\n"
      "   \4air\5  cair\n"
      "   \4gir\5  afligir\n"
      "   \4zir\5  traduzir\n"
      "   \4ir\5  partir\n"
      "\n"
      "   \4or\5  propor\n\n"
      "Atualmente, o banco de verbos possui %d verbos, dos quais %d são "
      "considerados paradigmas de conjugação e %d estão classificados como "
      "seguidores de um dos paradigmas. Portanto, existem ainda %d verbos "
      "que precisam ser manualmente revisados e classificados. "
      "Eventualmente, poderá ser necessário criar um novo paradigma, se "
      "algum verbo não puder ser corretamente conjugado seguindo um dos "
      "paradigmas existentes.\n\n"
      "Se tiver curiosidade de ver o banco de verbos, abra o arquivo:\n\n"
      "   %s\n\n"
      "O GConjugue também pode ser executado sem o servidor X (em modo texto). "
      "Se desejar mais informações sobre essa funcionalidade, digite num "
      "terminal:\n\n"
      "   man gconjugue\n",
    nv, np, (nvc - np), (nv - nvc), verbsFile);
  setText(str);
  free(str);
}

void on_sobre1_activate(){
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new (GTK_WINDOW (window1), GTK_DIALOG_MODAL | 
      GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, _(
      "gconjugue %s\n(c) 2005-2014 Jakson A. Aquino <jalvesaq@gmail.com>\n\n"
      "gconjugue is based on \"conjugue\", "
      "which was developed by Ricardo Ueda Karpischek\n\n"
      "gconjugue is free software under GNU GPL license.\n\n"
      "Homepage:\nhttp://www.lepem.ufc.br/jaa/gconjugue"), VERSION);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}


void conjugar(const char *vrb){
  int i, j;
  char *b1;

  /* Skipping problematic chars...*/
  while(vrb[0] == ' ' || vrb[0] == '&' || vrb[0] == '>' || vrb[0] == '<'
      || vrb[0] == '(' || vrb[0] == ')' || vrb[0] == '|' || vrb[0] == '"'
      || vrb[0] == '\'' || vrb[0] == '$')
    vrb++;
  i = strlen(vrb);
  if(i > 40)
    return;
  char *verbo = (char*)malloc(sizeof(char) * (i + 1));
  if(verbo == NULL)
    return;
  strcpy(verbo, vrb);
  for(j = 0; j < i; j++)
    if(verbo[j] == ' ' ||verbo[j] == '&' || verbo[j] == '>' || verbo[j] == '<'
	|| verbo[j] == '(' || verbo[j] == ')' || verbo[j] == '|' ||
	verbo[j] == '"' || verbo[j] == '\'' || verbo[j] == '$')
      verbo[j] = 0;
  i = strlen(verbo);
  if(i < 2)
    return;

  gchar *verb2 = g_utf8_strdown(verbo, i);
  free(verbo);
  if(strcmp(verb2, "por") == 0){
    g_free(verb2);
    GtkWidget *dialog;
    /* TODO: replace "its homonym" with "the verb pôr" when the libintl-* has
     * support to UTF-8 */
    dialog = gtk_message_dialog_new_with_markup (GTK_WINDOW (window1), GTK_DIALOG_MODAL,
	GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, _("I can't conjugate the "
	  "preposition \"<b>por</b>\". Would you like to have its homonym "
	  "verb conjugated?"));
    gint answer = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy (dialog);
    if(answer == GTK_RESPONSE_YES)
      verb2 = g_strdup("pôr");
    else
      return;
  }

  i = strlen(verb2);

  b1 = (char*)calloc(10000, sizeof(char));
  conjugue(verb2, b1);

  /* TODO: Check whether b1 is valid utf8 */

  g_free(verb2);

  /* Inserting text with tags in the GtkTextBuffer */
  setText(b1);
  free(b1);
}

gboolean on_window1_delete_event (){
  finish_gconjugue();
  return FALSE;
}

void read_verb(){
  GtkEntry *e = (GtkEntry*)entry1;
  const char *vrb = gtk_entry_get_text(e);
  conjugar(vrb);
  gtk_editable_select_region(GTK_EDITABLE(e), 0, gtk_entry_get_text_length(e));
}

void on_btconjg_clicked(){
  read_verb();
}

void on_entry1_activate (){
  read_verb();
}

