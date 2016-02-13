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

#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "callbacks.h"
#include "interface.h"
#include "conjugue.h"

GtkWidget *mainWindow;
GtkWidget *vbox1;
GtkWidget *menubar1;
GtkWidget *menuProg;
GtkWidget *miProg;
GtkWidget *miSetFont;
GtkWidget *miListV;
GtkWidget *miListP;
GtkWidget *miQuit;
GtkWidget *menuHelp;
GtkWidget *miHelp;
GtkWidget *miContents;
GtkWidget *miAbout;
GtkWidget *hbox1;
GtkWidget *entry1;
GtkWidget *btConjg;
GtkWidget *label1;
GtkWidget *btFont;
GtkWidget *scrolledwindow1;
GtkWidget *textview1;
GtkEntryCompletion *vrbCompltn;
GtkAccelGroup *accel_group;

int initHeight = 550, initWidth = 300;
char FontDesc[128];

static gboolean on_match_select(GtkEntryCompletion *widget, GtkTreeModel *model,
        GtkTreeIter *iter, gpointer user_data)
{  
    GValue value = {0, };
    gtk_tree_model_get_value(model, iter, 0, &value);
    gtk_entry_set_text(GTK_ENTRY(entry1), g_value_get_string(&value));
    g_value_unset(&value);
    read_verb();
    return FALSE;
}    

void create_main_window()
{
    accel_group = gtk_accel_group_new();

    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(mainWindow), _("GConjugue"));

    const char * gconjugue_xpm[] = {
        "48 48 25 1",
        " 	c None",
        ".	c #3BB13B",
        "+	c #62C427",
        "@	c #76D827",
        "#	c #4EC43B",
        "$	c #EBFF14",
        "%	c #89D827",
        "&	c #9DD827",
        "*	c #B1D827",
        "=	c #C4EB27",
        "-	c #D8EB14",
        ";	c #76C427",
        ">	c #D8D814",
        ",	c #4EB13B",
        "'	c #89C427",
        ")	c #C4D827",
        "!	c #B1EB27",
        "~	c #EBEB14",
        "{	c #9DC427",
        "]	c #62C43B",
        "^	c #4EC427",
        "/	c #D8EB27",
        "(	c #B1C427",
        "_	c #3BC43B",
        ":	c #4EB127",
        "................................................",
        "................................................",
        "...+@@...@@@@@#.................................",
        "..+$$$$$$$$$$$$$$%............#&*$$$$$=&&*$$-#..",
        "..&$$$$$$$$$$$$$$$@...........&$$$$$$$$$$$$$$@..",
        ".;>$$$$$$$$$$$$$$$=..........,=$$$$$$$$$$$$$$@..",
        ".'>$$$$$$$$$$$$$$$=..........;)$$$$$$$$$$$$$-#..",
        ".'>$$$$$$$$$$$$$$$&..........;)$$$$$$$$$$$$$!...",
        ".+*-----~$$$$$$-)&...........+*$$$$$$$$$$$$-+...",
        ".#{*)))))$$$$$$$*]...........+{)--$$$$$$$-*;....",
        "..+;'';{)-$$$$$$%............#'**-$$$$$$$)'#....",
        "...##,.#{)-$$$$$-#............,#;-$$$$$$$+......",
        "........+*-$$$$$$%..............'-$$$$$$-.......",
        "........^*)$$$$$$!..............'-$$$$$$/.......",
        "........^')-$$$$$$#.............{-$$$$$$@.......",
        "........#;(-$$$$$$*.............{-$$$$$$#.......",
        ".........^{)$$$$$$=.............=$$$$$$=........",
        "........._;*-$$$$$$+...........#$$$$$$$+........",
        "..........,'-$$$$$$&...........*$$$$$$$.........",
        "...........+*$$$$$$-..........+~$$$$$$!.........",
        "...........#'-$$$$$$+.........'$$$$$$$%.........",
        "..........._;*$$$$$$-#.......,)$$$$$$-#.........",
        "............^'-$$$$$$&.......;$$$$$$$&..........",
        "............#;(-$$$$$-#......!$$$$$$$#..........",
        ".............+{)$$$$$$=#....#-$$$$$$$#..........",
        "............._;*-$$$$$$=#...{-$$$$$$$#..........",
        "..............#')-$$$$$$=^..{>$$$$$$$#..........",
        "...............+{)$$$$$$$=#.&-$$$$$$!...........",
        "................;*-$$$$$$$%.'~$$$$$$]...........",
        "................#*)$$$$$$$-.=$$$$$$=............",
        ".................;*~$$$$$$$@$$$$$$$+............",
        ".................#{=$$$$$$$-$$$$$$$+............",
        "..................;*~$$$$$$$$$$$$$$]............",
        "..................+{-$$$$$$$$$$$$$+.............",
        "..................,')-$$$$$$$$$$$=,.............",
        "...................^{)$$$$$$$$$$~#..............",
        "...................,;)$$$$$$$$$~'...............",
        "....................^{-$$$$$$$$&................",
        "....................^'*-$$$$$$*.................",
        ".....................+{*-$$$$$@.................",
        ".....................^;*)~$$$=#.................",
        "......................^{)-$$~+..................",
        ".......................+{*))'...................",
        ".......................:+'''#...................",
        "........................,^^#....................",
        "................................................",
        "................................................",
        "................................................"};

    GdkPixbuf *icon_xpm = gdk_pixbuf_new_from_xpm_data((const char **)&gconjugue_xpm);
    gtk_window_set_icon(GTK_WINDOW(mainWindow), (GdkPixbuf*)icon_xpm);

    vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_show(vbox1);
    gtk_container_add(GTK_CONTAINER(mainWindow), vbox1);

    menubar1 = gtk_menu_bar_new();
    gtk_widget_show(menubar1);
    gtk_box_pack_start(GTK_BOX(vbox1), menubar1, FALSE, FALSE, 0);

    miProg = gtk_menu_item_new_with_mnemonic(_("_Program"));
    gtk_widget_show(miProg);
    gtk_container_add(GTK_CONTAINER(menubar1), miProg);

    menuProg = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(miProg), menuProg);

    miSetFont = gtk_menu_item_new_with_mnemonic(_("Set _font"));
    gtk_widget_show(miSetFont);
    gtk_container_add(GTK_CONTAINER(menuProg), miSetFont);

    miListP = gtk_menu_item_new_with_mnemonic(_("List all _paradigms"));
    gtk_widget_show(miListP);
    gtk_container_add(GTK_CONTAINER(menuProg), miListP);

    miListV = gtk_menu_item_new_with_mnemonic(_("List all _verbs"));
    gtk_widget_show(miListV);
    gtk_container_add(GTK_CONTAINER(menuProg), miListV);

    miQuit = gtk_menu_item_new_with_mnemonic(_("_Quit"));
    gtk_widget_add_accelerator(miQuit, "activate", accel_group,
            GDK_KEY_Q, GDK_CONTROL_MASK, 0);
    gtk_widget_show(miQuit);
    gtk_container_add(GTK_CONTAINER(menuProg), miQuit);

    miHelp = gtk_menu_item_new_with_mnemonic(_("_Help"));
    gtk_widget_show(miHelp);
    gtk_container_add(GTK_CONTAINER(menubar1), miHelp);

    menuHelp = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(miHelp), menuHelp);

    miContents = gtk_menu_item_new_with_mnemonic(_("_Contents"));
    gtk_widget_show(miContents);
    gtk_container_add(GTK_CONTAINER(menuHelp), miContents);

    miAbout = gtk_menu_item_new_with_mnemonic(_("_About"));
    gtk_widget_show(miAbout);
    gtk_container_add(GTK_CONTAINER(menuHelp), miAbout);

    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_show(hbox1);
    gtk_box_pack_start(GTK_BOX(vbox1), hbox1, FALSE, FALSE, 0);

    entry1 = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry1), 28);


    vrbCompltn = gtk_entry_completion_new();
    gtk_entry_completion_set_text_column(vrbCompltn, 0);
    gtk_entry_set_completion(GTK_ENTRY(entry1), vrbCompltn);
    g_signal_connect(G_OBJECT(vrbCompltn), "match-selected", G_CALLBACK(on_match_select), NULL);

    GtkListStore *model;
    GtkTreeIter iter;
    Verb *vlist;

    model = gtk_list_store_new(1, G_TYPE_STRING);

    for(vlist = Vrb; vlist && vlist->v; vlist++){
        gtk_list_store_append(model, &iter);
        gtk_list_store_set(model, &iter, 0, vlist->v, -1);
    }
    gtk_entry_completion_set_model(vrbCompltn, GTK_TREE_MODEL(model));

    gtk_widget_show(entry1);
    gtk_box_pack_start(GTK_BOX(hbox1), entry1, FALSE, TRUE, 0);
    gtk_entry_set_activates_default(GTK_ENTRY(entry1), TRUE);

    btConjg = gtk_button_new_with_mnemonic(_("conjugate"));
    gtk_widget_show(btConjg);
    gtk_box_pack_start(GTK_BOX(hbox1), btConjg, FALSE, FALSE, 0);
    gtk_button_set_focus_on_click(GTK_BUTTON(btConjg), FALSE);

    label1 = gtk_label_new("      ");
    gtk_box_pack_start(GTK_BOX(hbox1), label1, FALSE, TRUE, 0);
    gtk_widget_show(label1);

    btFont = gtk_button_new_with_label("A");
    gtk_widget_set_tooltip_text (btFont, _("Set font"));
    gtk_widget_show(btFont);
    gtk_box_pack_start(GTK_BOX(hbox1), btFont, FALSE, FALSE, 0);
    gtk_button_set_focus_on_click(GTK_BUTTON(btFont), FALSE);

    scrolledwindow1 = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_show(scrolledwindow1);
    gtk_box_pack_start(GTK_BOX(vbox1), scrolledwindow1, TRUE, TRUE, 0);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolledwindow1), GTK_SHADOW_IN);

    textview1 = gtk_text_view_new();
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(textview1), 5);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(textview1), 5);
    gtk_widget_show(textview1);
    gtk_container_add(GTK_CONTAINER(scrolledwindow1), textview1);

    g_signal_connect((gpointer)mainWindow, "delete_event", G_CALLBACK(on_mainWindow_delete),   NULL);
    g_signal_connect((gpointer)miSetFont,  "activate",     G_CALLBACK(on_btFont_clicked),      NULL);
    g_signal_connect((gpointer)miListP,    "activate",     G_CALLBACK(on_miListP_activate),    NULL);
    g_signal_connect((gpointer)miListV,    "activate",     G_CALLBACK(on_miListV_activate),    NULL);
    g_signal_connect((gpointer)miQuit,     "activate",     G_CALLBACK(on_miQuit_activate),     NULL);
    g_signal_connect((gpointer)miContents, "activate",     G_CALLBACK(on_miContents_activate), NULL);
    g_signal_connect((gpointer)miAbout,    "activate",     G_CALLBACK(on_miAbout_activate),    NULL);
    g_signal_connect((gpointer)entry1,     "activate",     G_CALLBACK(read_verb),              NULL);
    g_signal_connect((gpointer)btConjg,    "clicked",      G_CALLBACK(read_verb),              NULL);
    g_signal_connect((gpointer)btFont,     "clicked",      G_CALLBACK(on_btFont_clicked),      NULL);

    gtk_window_add_accel_group(GTK_WINDOW(mainWindow), accel_group);

    /* Set the window dimensions */
    char fname[256];
    snprintf(fname, 255, "%s/gconjugue/wdim", g_get_user_cache_dir());
    FILE *F = fopen(fname, "r");
    if(F){
        char s[128];
        char b[128];
        int i = 0;
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


    gtk_window_set_default_size(GTK_WINDOW(mainWindow), initWidth, initHeight);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview1), GTK_WRAP_WORD);
    GtkTextBuffer *buf =  gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview1));
    gtk_text_buffer_create_tag(buf, "bold", "weight", PANGO_WEIGHT_BOLD, NULL);
    gtk_text_buffer_create_tag(buf, "red", "foreground", "red", NULL);
    gtk_text_buffer_create_tag(buf, "blue", "foreground", "blue", NULL);
    gtk_text_buffer_create_tag(buf, "green", "foreground", "green", NULL);
    gtk_text_buffer_create_tag(buf, "large", "scale", PANGO_SCALE_LARGE, NULL);

    /* Set text viewer font */
    FontDesc[0] = 0;
    snprintf(fname, 255, "%s/gconjugue/font_desc", g_get_user_cache_dir());
    F = fopen(fname, "r");
    if(F){
        int i = 0;
        if(fgets(FontDesc, 127, F) && strlen(FontDesc) > 3){
            for(i = 0; i < strlen(FontDesc); i++)
                if(FontDesc[i] == '\n' || FontDesc[i] == '\r')
                    FontDesc[i] = 0;
            PangoFontDescription *font_desc = pango_font_description_from_string(FontDesc);
            gtk_widget_modify_font(textview1, font_desc); // TODO: replace this deprecated code.
            pango_font_description_free(font_desc);
        }
        fclose(F);
    }

    gtk_widget_show(mainWindow);
}

