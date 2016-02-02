/* This file is part of gconjugue
**
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
**
** (c) 2005-2011 Jakson Aquino: jalvesaq@gmail.com
**
***************************************************************/

#ifndef GCONJUGUE_INTERFACE_H
#define GCONJUGUE_INTERFACE_H

#include <glib/gi18n.h>

extern GtkWidget *window1;
extern GtkWidget *vbox1;
extern GtkWidget *menubar1;
extern GtkWidget *menuitem1;
extern GtkWidget *menuitem1_menu;
extern GtkWidget *miQuit;
extern GtkWidget *miListV;
extern GtkWidget *miListP;
extern GtkWidget *menuitem4;
extern GtkWidget *menuitem4_menu;
extern GtkWidget *sobre1;
extern GtkWidget *hcontents;
extern GtkWidget *hbox1;
extern GtkWidget *entry1;
extern GtkWidget *btconjg;
extern GtkWidget *scrolledwindow1;
extern GtkWidget *textview1;
extern GtkAccelGroup *accel_group;

GtkWidget* create_window1 (void);

#endif
