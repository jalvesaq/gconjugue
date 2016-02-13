/* This file is part of gconjugue
 **
 ** It is distributed under the GNU General Public License.
 ** See the file COPYING for details.
 **
 ** (c) 2005-2016 Jakson Aquino: jalvesaq@gmail.com
 **
 ***************************************************************/

#ifndef CONJUGUE_PTBR_H
#define CONJUGUE_PTBR_H

#include <glib/gi18n.h>

extern void fix_entry(char *dest, const char *src, char *msg);
extern void conjugue(char *verb, char *buffer);
extern void read_verbs_file();
extern void conjugue_all();
extern void clean_text_buffer(char *dest, char *src);
extern void color_text_buffer(char *dest, char *src);
extern void xml_text_buffer(char *dest, char *src);
extern void list_verbs(char *buffer);
extern void list_prdgms(char *buffer);

extern int NV, NP, NVC;
extern char *verbsFile;

typedef struct {
    char *root;
    char *suffix;
    char *noun;// root + suffix
    char **FN; // Formas nominais
    char **IP; // Infinitivo pessoal
    char **PI; // Presente do indicativo
    char **II; // Imperfeito do indicativo
    char **EI; // Perfeito do indicativo
    char **MI; // Mais-que-perfeito do indicativo
    char **TI; // Futuro do pretérito
    char **FI; // Futuro do presente
    char **PS; // Presente do subjuntivo
    char **IS; // Imperfeito do subjuntivo
    char **FS; // Futuro do subjuntivo
    char **IA; // Imperativo afirmativo
    char **IN; // Imperativo negativo
} Paradigm;

typedef struct {
    Paradigm *p;
    char * v; // verb
    char * a; // abundante
} Verb;

typedef struct {
    char *verb;
    char **FN; // Formas nominais
    char **IP; // Infinitivo pessoal
    char **PI; // Presente do indicativo
    char **II; // Imperfeito do indicativo
    char **EI; // Perfeito do indicativo
    char **MI; // Mais-que-perfeito do indicativo
    char **TI; // Futuro do pretérito
    char **FI; // Futuro do presente
    char **PS; // Presente do subjuntivo
    char **IS; // Imperfeito do subjuntivo
    char **FS; // Futuro do subjuntivo
    char **IA; // Imperativo afirmativo
    char **IN; // Imperativo negativo
    char *a;   // Forma abundante
} ConjugatedVerb;

extern Paradigm **Prdgm;
extern Verb *Vrb;

#endif
