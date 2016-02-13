/* This file is part of gconjugue
 **
 ** It is distributed under the GNU General Public License.
 ** See the file COPYING for details.
 **
 ** (c) 2005-2016 Jakson Aquino: jalvesaq@gmail.com
 **
 ***************************************************************/

#ifndef GCONJUGUE_CALLBACKS_H
#define GCONJUGUE_CALLBACKS_H

#include <gtk/gtk.h>

void on_miQuit_activate();
void on_miListV_activate();
void on_miListP_activate();
void on_miAbout_activate();
void on_miContents_activate();
void on_btFont_clicked();
void read_verb();
gboolean on_mainWindow_delete();

#endif
