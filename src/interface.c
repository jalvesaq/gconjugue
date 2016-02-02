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

#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"

GtkWidget *window1;
GtkWidget *vbox1;
GtkWidget *menubar1;
GtkWidget *menuitem1;
GtkWidget *menuitem1_menu;
GtkWidget *miQuit;
GtkWidget *miListV;
GtkWidget *miListP;
GtkWidget *menuitem4;
GtkWidget *menuitem4_menu;
GtkWidget *sobre1;
GtkWidget *hcontents;
GtkWidget *hbox1;
GtkWidget *entry1;
GtkWidget *btconjg;
GtkWidget *scrolledwindow1;
GtkWidget *textview1;
GtkAccelGroup *accel_group;

GtkWidget*
create_window1 (void)
{

  accel_group = gtk_accel_group_new ();

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window1), _("GConjugue"));
  
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

  GdkPixbuf *icon_xpm = gdk_pixbuf_new_from_xpm_data ((const char **) &gconjugue_xpm);
  gtk_window_set_icon(GTK_WINDOW(window1), (GdkPixbuf*)icon_xpm);

  vbox1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (window1), vbox1);

  menubar1 = gtk_menu_bar_new ();
  gtk_widget_show (menubar1);
  gtk_box_pack_start (GTK_BOX (vbox1), menubar1, FALSE, FALSE, 0);

  menuitem1 = gtk_menu_item_new_with_mnemonic (_("_Program"));
  gtk_widget_show (menuitem1);
  gtk_container_add (GTK_CONTAINER (menubar1), menuitem1);

  menuitem1_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem1), menuitem1_menu);

  miListP = gtk_menu_item_new_with_mnemonic(_("List all _paradigms"));
  gtk_widget_show (miListP);
  gtk_container_add (GTK_CONTAINER (menuitem1_menu), miListP);

  miListV = gtk_menu_item_new_with_mnemonic(_("List all _verbs"));
  gtk_widget_show (miListV);
  gtk_container_add (GTK_CONTAINER (menuitem1_menu), miListV);

  miQuit = gtk_image_menu_item_new_from_stock ("gtk-quit", accel_group);
  gtk_widget_show (miQuit);
  gtk_container_add (GTK_CONTAINER (menuitem1_menu), miQuit);

  menuitem4 = gtk_menu_item_new_with_mnemonic (_("_Help"));
  gtk_widget_show (menuitem4);
  gtk_container_add (GTK_CONTAINER (menubar1), menuitem4);

  menuitem4_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem4), menuitem4_menu);

  hcontents = gtk_menu_item_new_with_mnemonic (_("_Contents (in Portuguese)"));
  gtk_widget_show (hcontents);
  gtk_container_add (GTK_CONTAINER (menuitem4_menu), hcontents);

  sobre1 = gtk_menu_item_new_with_mnemonic (_("_About"));
  gtk_widget_show (sobre1);
  gtk_container_add (GTK_CONTAINER (menuitem4_menu), sobre1);

  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox1, FALSE, FALSE, 0);

  entry1 = gtk_entry_new ();
  gtk_entry_set_max_length((GtkEntry*)entry1, 28);
  gtk_widget_show (entry1);
  gtk_box_pack_start (GTK_BOX (hbox1), entry1, FALSE, TRUE, 0);
  gtk_entry_set_activates_default (GTK_ENTRY (entry1), TRUE);

  btconjg = gtk_button_new_with_mnemonic (_("conjugate"));
  gtk_widget_show (btconjg);
  gtk_box_pack_start (GTK_BOX (hbox1), btconjg, FALSE, FALSE, 0);
  gtk_button_set_focus_on_click (GTK_BUTTON (btconjg), FALSE);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (vbox1), scrolledwindow1, TRUE, TRUE, 0);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_SHADOW_IN);

  textview1 = gtk_text_view_new ();
  gtk_text_view_set_left_margin ((GtkTextView*)textview1, 5);
  gtk_text_view_set_right_margin ((GtkTextView*)textview1, 5);
  gtk_widget_show (textview1);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), textview1);

  g_signal_connect((gpointer) window1, "delete_event", G_CALLBACK (on_window1_delete_event), NULL);
  g_signal_connect((gpointer) miQuit, "activate", G_CALLBACK (on_miQuit_activate), NULL);
  g_signal_connect((gpointer) miListP, "activate", G_CALLBACK (on_miListP_activate), NULL);
  g_signal_connect((gpointer) miListV, "activate", G_CALLBACK (on_miListV_activate), NULL);
  g_signal_connect((gpointer) hcontents, "activate", G_CALLBACK (on_hcontents_activate), NULL);
  g_signal_connect((gpointer) sobre1, "activate", G_CALLBACK (on_sobre1_activate), NULL);
  g_signal_connect((gpointer) entry1, "activate", G_CALLBACK (on_entry1_activate), NULL);
  g_signal_connect((gpointer) btconjg, "pressed", G_CALLBACK (on_btconjg_clicked),NULL);

  gtk_window_add_accel_group (GTK_WINDOW (window1), accel_group);

  return window1;
}

