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
#include <sys/stat.h>
#include <errno.h>

#include "interface.h"
#include "conjugue.h"
#include "callbacks.h"


static void write_info_in_cache_dir(const char *fname, const char *str)
{
    char fpath[256];
    snprintf(fpath, 255, "%s/gconjugue", g_get_user_cache_dir());
    if(mkdir(fpath, S_IRUSR | S_IWUSR | S_IXUSR))
        if(errno != EEXIST)
            fprintf(stderr, "Error in mkdir: %d\n", errno);
    snprintf(fpath, 255, "%s/gconjugue/%s", g_get_user_cache_dir(), fname);
    FILE *f = fopen(fpath, "w");
    if(f){
        fprintf(f, "%s\n", str);
        fclose(f);
    } else {
        fprintf(stderr, "Could not open %s [errno = %d]\n", fpath, errno);
    }
}

static void finish_gconjugue()
{
    /* Save window dimensions */
    int h, w;
    gtk_window_get_size(GTK_WINDOW(mainWindow), &w, &h);
    if(w != initWidth || h != initHeight){
        char wh[64];
        snprintf(wh, 31, "height = %d\nwidth = %d\n", h, w);
        write_info_in_cache_dir("wdim", wh);
    }
    gtk_main_quit();
}

gboolean on_mainWindow_delete()
{
    finish_gconjugue();
    return FALSE;
}

void on_miQuit_activate()
{
    finish_gconjugue();
}

static void set_text(const char *str)
{
    int i, j, l;
    GtkTextBuffer *b = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview1));
    gtk_text_buffer_set_text(b, " ", 0);
    l = strlen(str);
    char letra;
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(b, &iter, 0);
    i = 0;
    j = 0;
    while(i < l){
        if(str[i] > 0 && str[i] < 7){
            letra = str[i];
            gtk_text_buffer_insert(b, &iter, str+j, i-j);
            i++;
            j = i;
            while(str[i] != 6)
                i++;
            if(letra == 5)
                gtk_text_buffer_insert_with_tags_by_name(b, &iter, str+j, i-j,
                        "large", "bold", NULL);
            if(letra == 4)
                gtk_text_buffer_insert_with_tags_by_name(b, &iter, str+j, i-j,
                        "bold", NULL);
            else if(letra == 3)
                gtk_text_buffer_insert_with_tags_by_name(b, &iter, str+j, i-j,
                        "blue", NULL);
            else if(letra == 2)
                gtk_text_buffer_insert_with_tags_by_name(b, &iter, str+j, i-j,
                        "green", NULL);
            else if(letra == 1)
                gtk_text_buffer_insert_with_tags_by_name(b, &iter, str+j, i-j,
                        "red", NULL);
            i++;
            j = i;
        } else
            i++;
    }
    gtk_text_buffer_insert(b, &iter, str+j, -1);
    gtk_widget_grab_focus(entry1);
}

void on_miListP_activate()
{
    char *buffer = (char*)calloc(1512000, sizeof(char));
    list_prdgms(buffer);
    set_text(buffer);
    free(buffer);
}

void on_miListV_activate()
{
    char *buffer = (char*)calloc(1512000, sizeof(char));
    list_verbs(buffer);
    set_text(buffer);
    free(buffer);
}

void on_miContents_activate()
{
    char str[5000] = {0};
    char tmp[1024] = {0};
    snprintf(str, 64, "\n\5%s\6\n\n", _("Help"));
    strncat(str, _("GConjugue loads at startup a dataset of some conjugated "
    "verbs which are used as paradigms for conjugating the other verbs that are "
    "in the dataset. Some verbs are explicitly listed as followers of a "
    "paradigm, but others are only listed as existing verbs. The software will "
    "try to deduce what paradigm should be used to conjugate these verbs as well "
    "any other expression typed by the user."), 4999);
    strncat(str, "\n\n", 4999);
    strncat(str, _("GConjugue presents the following information before the "
    "conjugation of verbs:"), 4999);
    strncat(str, "\n\n\3", 4999);
    strncat(str, _("Paradigm: <verb>"), 4999);
    strncat(str, "\6: ", 4999);
    strncat(str, _("Indicates what verb was used as paradigm for the "
    "conjugation; either the verb itself is a paradigm or it is explicitly "
    "listed as follower of a paradigm."), 4999);
    strncat(str, "\n\n\3", 4999);
    strncat(str, _("Deduced paradigm: <verb>"), 4999);
    strncat(str, "\6: ", 4999);
    strncat(str, _("The verb is in the dataset, but it is not classified. Its "
    "paradigm was “calculated” by the software."), 4999);
    strncat(str, "\n\n\1", 4999);
    strncat(str, _("Not in the verbs dataset"), 4999);
    strncat(str, "\6: ", 4999);
    strncat(str, _("Although not in the dataset, the verb entered by the user "
    "will be conjugated if it is possible to deduce its paradigm."), 4999);
    strncat(str, "\n\n\1", 4999);
    strncat(str, _("I cannot conjugate <verb>"), 4999);
    strncat(str, "\6: ", 4999);
    strncat(str, _("GConjugue could not guess what is the proper paradigm for "
    "the expression the user entered. This should happen only when the expression "
    "cannot be treated as verb in Portuguese, such as words that do not "
    "end in ‘r’."), 4999);
    strncat(str, "\n\n", 4999);
    strncat(str, _("The number of existing paradigms in GConjugue dataset is "
    "higher than the number of paradigms recognized by the Portuguese normative "
    "grammar because GConjugue is not as smart as a human grammarian to apply general "
    "rules to exceptional cases."), 4999);
    strncat(str, "\n\n", 4999);
    strncat(str, _("Verbs not classified in the dataset as followers of a paradigm have "
            "their paradigms deduced through the comparison of its end with the "
            "last letters of some verbs. The comparisons are made in the following "
            "sequence, and are interrupted as soon as match is found:"), 4999);
    strncat(str, "\n\n", 4999);
    strncat(str, "   \4çar\6  abraçar\n"
            "   \4gar\6  chegar\n"
            "   \4car\6  comunicar\n"
            "   \4oar\6  magoar\n"
            "   \4ear\6  passear\n"
            "   \4ar\6  cantar\n"
            "\n"
            "   \4cer\6  conhecer\n"
            "   \4guer\6  erguer\n"
            "   \4ger\6  proteger\n"
            "   \4er\6  vender\n"
            "\n"
            "   \4ruir\6  ruir\n"
            "   \4guir\6  extinguir\n"
            "   \4uir\6  atribuir\n"
            "   \4air\6  cair\n"
            "   \4gir\6  afligir\n"
            "   \4zir\6  traduzir\n"
            "   \4ir\6  partir\n"
            "\n"
            "   \4or\6  propor\n\n", 4999);
    strncat(str, _("Currently, the dataset has:"), 4999);
    strncat(str, "\n\n   ", 4999);
    strncat(str, _("- Verbs treated as paradigms: "), 4999);
    sprintf(tmp, "%d", NP);
    strncat(str, tmp, 4999);
    strncat(str, "\n   ", 4999);
    strncat(str, _("- Verbs following paradigms: "), 4999);
    sprintf(tmp, "%d", NVC);
    strncat(str, tmp, 4999);
    strncat(str, "\n   ", 4999);
    strncat(str, _("- Verbs not classified yet: "), 4999);
    sprintf(tmp, "%d", NV - NVC);
    strncat(str, tmp, 4999);
    strncat(str, "\n\n", 4999);
    strncat(str, _("If you are curious to see the dataset of verbs, please, "
    "open the file:"), 4999);
    strncat(str, "\n\n   ", 4999);
    strncat(str, verbsFile, 4999);
    strncat(str, "\n\n", 4999);
    strncat(str, _("GConjugue might also be run from a terminal emulator as a "
    "text only application. If you want more information on this feature, do in "
    "a terminal emulator:"), 4999);
    strncat(str, "\n\n   man gconjugue\n", 4999);
    set_text(str);
}

void on_miAbout_activate()
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(mainWindow),
            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
            _("gconjugue %s\n(c) 2005-2016 Jakson A. Aquino <jalvesaq@gmail.com>\n\n"
                "gconjugue is based on \"conjugue\", "
                "which was developed by Ricardo Ueda Karpischek\n\n"
                "gconjugue is free software under GNU GPL license.\n\n"
                "Homepage:\nhttps://github.com/jalvesaq/gconjugue"), VERSION);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


static void gconjugue(const char *verb)
{
    char *b1;
    char v[64] = {0};
    strncpy(v, verb, 63);

    if(strcmp(v, "por") == 0){
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new_with_markup(GTK_WINDOW(mainWindow), GTK_DIALOG_MODAL,
                GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, _("I can't conjugate the "
                    "preposition “<b>por</b>”. Would you like to have the "
                    "verb “<b>pôr</b>” conjugated?"));
        gint answer = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        if(answer == GTK_RESPONSE_YES)
            strcpy(v, "pôr");
        else
            return;
    }

    b1 = (char*)calloc(10000, sizeof(char));
    conjugue(v, b1);

    /* Inserting text with tags in the GtkTextBuffer */
    if(g_utf8_validate(b1, -1, NULL)){
        set_text(b1);
    } else {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(mainWindow),
                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                _("GConjugue internal error: Invalid unicode characters!"));
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    free(b1);
}

void read_verb()
{
    GtkEntry *e = GTK_ENTRY(entry1);
    const char *verb = gtk_entry_get_text(e);
    gconjugue(verb);
    gtk_editable_select_region(GTK_EDITABLE(e), 0, gtk_entry_get_text_length(e));
}


GtkWidget *fdlg;

void on_font_selected()
{
    gchar *fdesc = gtk_font_chooser_get_font(GTK_FONT_CHOOSER(fdlg));
    PangoFontDescription *font_desc = pango_font_description_from_string(fdesc);
    gtk_widget_modify_font(textview1, font_desc); // TODO: replace this deprecated code.
    pango_font_description_free(font_desc);
    write_info_in_cache_dir("font_desc", fdesc);
    strncpy(FontDesc, fdesc, 127);
    free(fdesc);
}

void on_btFont_clicked()
{
    fdlg = gtk_font_chooser_dialog_new(_("Set font"),
            GTK_WINDOW(mainWindow));
    g_signal_connect((gpointer)fdlg, "font-activated",
            G_CALLBACK(on_font_selected), NULL);
    if(*FontDesc)
        gtk_font_chooser_set_font(GTK_FONT_CHOOSER(fdlg), FontDesc);
    gint r = gtk_dialog_run(GTK_DIALOG(fdlg));
    switch(r){
        case GTK_RESPONSE_OK:
            on_font_selected();
            break;
        default:
            break;
    }
    gtk_widget_destroy(fdlg);
}
