/* This file is part of gconjugue
**
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
**
** (c) 2005-2011 Jakson Aquino: jalvesaq@gmail.com
**
***************************************************************/

#ifndef CONJUGUE_PTBR_H
#define CONJUGUE_PTBR_H

extern int conjugue(char *verbo, char *buffer);
extern void read_verbs_file();
extern void compare();
extern void cleanTextBuffer(char *dest, char *src);
extern void listVerbs(char *buffer);
extern void listPrdgms(char *buffer);
extern int nv, np, nvc;
extern char *verbsFile;

#endif
