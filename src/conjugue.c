/* This file is part of gconjugue
 **
 ** It is distributed under the GNU General Public License.
 ** See the file COPYING for details.
 **
 ** (c) 2005-2017 Jakson Aquino: jalvesaq@gmail.com
 **
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
//#include <glib.h>

#include "conjugue.h"

int NP, NV, NVC; // number of paradigms and number of verbs
int sorted = 0;
int Normative = 1;
char *verbsFile;
Paradigm **Prdgm;
Verb *Vrb;

// TODO: should be dynamically defined:
#define MAXPRDGMS 150
#define MAXVRBS 8000

static void free_conjugated_verb(ConjugatedVerb *v)
{
    for(int i = 0; i < 6; i++){
        if(i < 3)
            free(v->FN[i]);
        if(i < 5){
            free(v->IA[i]);
            free(v->IN[i]);
        }
        free(v->IP[i]);
        free(v->PI[i]);
        free(v->II[i]);
        free(v->EI[i]);
        free(v->MI[i]);
        free(v->TI[i]);
        free(v->FI[i]);
        free(v->PS[i]);
        free(v->IS[i]);
        free(v->FS[i]);
    }
    free(v->FN);
    free(v->IA);
    free(v->IN);
    free(v->IP);
    free(v->PI);
    free(v->II);
    free(v->EI);
    free(v->MI);
    free(v->TI);
    free(v->FI);
    free(v->PS);
    free(v->IS);
    free(v->FS);
    free(v);
}

static Paradigm *get_paradigm(const char *v)
{
    int i;
    for(i = 0; i < NV; i++)
        if(strcmp(Vrb[i].v, v) == 0)
            return(Vrb[i].p);
    return NULL;
}

static Paradigm *deduce_paradigm(const char *v)
{
    Paradigm *p01 = get_paradigm("abraçar");
    /*Paradigm *p02 = get_paradigm("apoiar");*/
    Paradigm *p03 = get_paradigm("chegar");
    Paradigm *p04 = get_paradigm("comunicar");
    Paradigm *p05 = get_paradigm("magoar");
    Paradigm *p06 = get_paradigm("passear");
    Paradigm *p07 = get_paradigm("cantar");

    Paradigm *p08 = get_paradigm("conhecer");
    Paradigm *p09 = get_paradigm("erguer");
    Paradigm *p10 = get_paradigm("proteger");
    Paradigm *p11 = get_paradigm("vender");

    Paradigm *p12 = get_paradigm("ruir");
    Paradigm *p13 = get_paradigm("extinguir");
    Paradigm *p14 = get_paradigm("atribuir");
    Paradigm *p15 = get_paradigm("cair");
    Paradigm *p16 = get_paradigm("afligir");
    Paradigm *p17 = get_paradigm("traduzir");
    Paradigm *p18 = get_paradigm("partir");

    Paradigm *p19 = get_paradigm("propor");

    char c1, c2;
    int l = strlen(v);
    if(l > 1)
        c1 = v[l-2];
    else
        c1 = 0;
    if(l > 2)
        c2 = v[l-3];
    else
        c2 = 0;
    switch(c1){
        case 'a':
            switch(c2){
                case (char)0xa7: return p01; break;
                case 'g': return p03; break;
                case 'c': return p04; break;
                case 'o': return p05; break;
                case 'e': return p06; break;
                default : return p07; break;
            }
            break;
        case 'e':
            switch(c2){
                case 'c': return p08; break;
                case 'u':
                          if(l > 3 && v[l-4] == 'g')
                              return p09;
                          else
                              return p11;
                          break;
                case 'g': return p10; break;
                default : return p11; break;
            }
            break;
        case 'i':
            switch(c2){
                case 'u':
                    if(l > 3){
                        if(v[l - 4] == 'r')
                            return p12;
                        else
                            if(v[l - 4] == 'g')
                                return p13;
                            else
                                return p14;
                    } else
                        return p17;
                    break;
                case 'a': return p15; break;
                case 'g': return p16; break;
                case 'z':
                          if(l > 3 && v[l - 4] == 'u')
                              return p17;
                          else
                              return p18;
                          break;
                default : return p18; break;
            }
            break;
        case 'o':
            return p19;
            break;
        default:
            return NULL;
    }
    return NULL;
}

static char **alloc_n(char *root, char **p, int n)
{
    char cnjgtd[32];
    char **tmp = (char**)calloc(n, sizeof(char*));
    for(int i = 0; i < n; i++){
        if(p[i]){
            snprintf(cnjgtd, 31, "%s%s", root, p[i]);
            tmp[i] = (char*)calloc((strlen(cnjgtd) + 1), sizeof(char));
            strcpy(tmp[i], cnjgtd);
        }
    }
    return tmp;
}

static ConjugatedVerb *conjugate_one(char *v, Paradigm *p, char *a)
{
    ConjugatedVerb *cv = (ConjugatedVerb*)calloc(1, sizeof(ConjugatedVerb));
    cv->verb = v;
    int rlen = strlen(v) - strlen(p->suffix);
    char *root = (char*)calloc(rlen + 1, sizeof(char));
    for(int i = 0; i < rlen; i++)
        root[i] = v[i];
    cv->FN = alloc_n(root, p->FN, 3);
    cv->a = a;
    cv->IP = alloc_n(root, p->IP, 6);
    cv->PI = alloc_n(root, p->PI, 6);
    cv->II = alloc_n(root, p->II, 6);
    cv->EI = alloc_n(root, p->EI, 6);
    cv->MI = alloc_n(root, p->MI, 6);
    cv->TI = alloc_n(root, p->TI, 6);
    cv->FI = alloc_n(root, p->FI, 6);
    cv->PS = alloc_n(root, p->PS, 6);
    cv->IS = alloc_n(root, p->IS, 6);
    cv->FS = alloc_n(root, p->FS, 6);
    cv->IA = alloc_n(root, p->IA, 5);
    cv->IN = alloc_n(root, p->IN, 5);
    free(root);

    return cv;
}

static void seek_deep(const char *what, char **where, char *tempo, int n, char f, char *b)
{
    char *pron5[5] =       {"tu", "ele", "nós", "vós", "eles"};
    char *pron6[6] = {"eu", "tu", "ele", "nós", "vós", "eles"};
    char **pron;
    char msg[1024];
    if(n == 5)
        pron = pron5;
    else
        pron = pron6;
    for(int i = 0; i < n; i++){
        if(where[i] && strcmp(where[i], what) == 0){
            if(f == 'g')
                snprintf(msg, 1023, "%s: \2%s\6 %s\n", tempo, pron[i], what);
            else if(f == 'p')
                snprintf(msg, 1023, "%s: %s \2%s\6\n", tempo, what, pron[i]);
            else
                snprintf(msg, 1023, "%s: não %s \2%s\6\n", tempo, what, pron[i]);
            strncat(b, msg, 2047);
        }
    }
}

static void seek_inside(ConjugatedVerb *v, const char *s, char *b)
{
    if(strcmp(v->FN[1], s) == 0){
        strcat(b, "Gerúndio: ");
        strcat(b, s);
        strcat(b, "\n");
    }
    if(strcmp(v->FN[2], s) == 0 || (v->a && strcmp(v->a, s) == 0)){
        strcat(b, "Particípio: ");
        strcat(b, s);
        strcat(b, "\n");
    }

    seek_deep(s, v->IP, "Infinitivo pessoal",              6, 'g', b);
    seek_deep(s, v->PI, "Presente do indicativo",          6, 'g', b);
    seek_deep(s, v->II, "Imperfeito do indicativo",        6, 'g', b);
    seek_deep(s, v->EI, "Perfeito do indicativo",          6, 'g', b);
    seek_deep(s, v->MI, "Mais-que-perfeito do indicativo", 6, 'g', b);
    seek_deep(s, v->TI, "Futuro do pretérito",             6, 'g', b);
    seek_deep(s, v->FI, "Futuro do presente",              6, 'g', b);
    seek_deep(s, v->PS, "Presente do subjuntivo",          6, 'g', b);
    seek_deep(s, v->IS, "Imperfeito do subjuntivo",        6, 'g', b);
    seek_deep(s, v->FS, "Futuro do subjuntivo",            6, 'g', b);
    seek_deep(s, v->IA, "Imperativo afirmativo",           5, 'p', b);
    seek_deep(s, v->IN, "Imperativo negativo",             5, 'n', b);

}

static void add_to_buffer(char *b1, const char *fmt, ...)
{
    va_list argptr;
    char msg[255];
    char msg2[255];
    va_start(argptr, fmt);
    strncpy(msg, fmt, 254);
    vsnprintf(msg2, 254, msg, argptr);
    strncat(b1, msg2, 19998);
}

static void seek_conjugation(const char *s, char *buffer)
{
    int i;
    ConjugatedVerb *vv;
    char b[2048];
    char b1[2048];
    char b2[2048] = {0};
    int found = 0;
    for(i = 0; i < NV; i++)
        if(Vrb[i].v[0] == s[0] || strcmp(Vrb[i].v, "ser") == 0 ||
                strcmp(Vrb[i].v, "ir") == 0 || strcmp(Vrb[i].v, "aguar") == 0){
            if(Vrb[i].p)
                vv = conjugate_one(Vrb[i].v, Vrb[i].p, Vrb[i].a);
            else
                vv = conjugate_one(Vrb[i].v, deduce_paradigm(Vrb[i].v), Vrb[i].a);

            memset(b, 0, 1024);
            seek_inside(vv, s, b);
            if(strlen(b) > 0){
                found++;
                snprintf(b1, 2047, "\4%s\6:\n%s\n", Vrb[i].v, b);
                strncat(b2, b1, 2047);
            }
            free_conjugated_verb(vv);
        }
    if(found){
        if(found == 1)
            add_to_buffer(buffer, _("\3“%s” was found among conjugated forms of 1 verb:\6\n\n"), s);
        else
            add_to_buffer(buffer, _("\3“%s” was found conjugated in %d verbs:\6\n\n"), s, found);
        add_to_buffer(buffer, "%s", b2);
    } else {
        add_to_buffer(buffer, _("\1“%s” was not found among the conjugated forms of any verb.\6\n\n"), s);
    }
}

static void add_verb(const char *b, Paradigm *P, char *abndnt)
{
    Vrb[NV].v = (char*)calloc((strlen(b) + 1), sizeof(char));
    strcpy(Vrb[NV].v, b);
    if(abndnt){
        Vrb[NV].a = (char*)calloc((strlen(abndnt) + 1), sizeof(char));
        strcpy(Vrb[NV].a, abndnt);
    }
    Vrb[NV].p = P;
    NV++;

    if(NV >= MAXVRBS){
        fprintf(stderr, _("Maximo number of verbs surpassed!\n"));
        exit(1);
    }
}

static int get_verb_idx(const char *v)
{
    // There is no need of quick sort and binary search because sequential
    // search is alread quick enough.
    int i;
    for(i = 0; i < NV; i++)
        if(strcmp(Vrb[i].v, v) == 0)
            return i;
    return -1;

}

static void add_tempo(char *buffer, char *tempo, char **piece, char t, char **fn, const char *conj)
{
    add_to_buffer(buffer, "\n\4");
    add_to_buffer(buffer, tempo);
    add_to_buffer(buffer, "\6\n");

    if(Normative){
        if(t == 'a'){
            if(piece[0])
                add_to_buffer(buffer, "   %s \2tu\6\n", piece[0]);
            if(piece[1])
                add_to_buffer(buffer, "   %s \2ele\6\n", piece[1]);
            if(piece[2])
                add_to_buffer(buffer, "   %s \2nós\6\n", piece[2]);
            if(piece[3])
                add_to_buffer(buffer, "   %s \2vós\6\n", piece[3]);
            if(piece[4])
                add_to_buffer(buffer, "   %s \2eles\6\n", piece[4]);
        } else if(t == 'n'){
            if(piece[0])
                add_to_buffer(buffer, "   não %s \2tu\6\n", piece[0]);
            if(piece[1])
                add_to_buffer(buffer, "   não %s \2ele\6\n", piece[1]);
            if(piece[2])
                add_to_buffer(buffer, "   não %s \2nós\6\n", piece[2]);
            if(piece[3])
                add_to_buffer(buffer, "   não %s \2vós\6\n", piece[3]);
            if(piece[4])
                add_to_buffer(buffer, "   não %s \2eles\6\n", piece[4]);
        } else if(t == 's'){
            if(piece[0])
                add_to_buffer(buffer, "   %s \2eu\6 %s\n", conj, piece[0]);
            if(piece[1])
                add_to_buffer(buffer, "   %s \2tu\6 %s\n", conj, piece[1]);
            if(piece[2])
                add_to_buffer(buffer, "   %s \2ele\6 %s\n", conj, piece[2]);
            if(piece[3])
                add_to_buffer(buffer, "   %s \2nós\6 %s\n", conj, piece[3]);
            if(piece[4])
                add_to_buffer(buffer, "   %s \2vós\6 %s\n", conj, piece[4]);
            if(piece[5])
                add_to_buffer(buffer, "   %s \2eles\6 %s\n", conj, piece[5]);
        } else {
            if(piece[0])
                add_to_buffer(buffer, "   \2eu\6 %s\n", piece[0]);
            if(piece[1])
                add_to_buffer(buffer, "   \2tu\6 %s\n", piece[1]);
            if(piece[2])
                add_to_buffer(buffer, "   \2ele\6 %s\n", piece[2]);
            if(piece[3])
                add_to_buffer(buffer, "   \2nós\6 %s\n", piece[3]);
            if(piece[4])
                add_to_buffer(buffer, "   \2vós\6 %s\n", piece[4]);
            if(piece[5])
                add_to_buffer(buffer, "   \2eles\6 %s\n", piece[5]);
        }
    } else {
        if(t == 'a'){
            if(piece[1])
                add_to_buffer(buffer, "   %s \2você\6\n", piece[1]);
            if(piece[1])
                add_to_buffer(buffer, "   %s \2ele\6\n", piece[1]);
            if(piece[1])
                add_to_buffer(buffer, "   %s \2a gente\6\n", piece[1]);
            if(piece[4])
                add_to_buffer(buffer, "   %s \2vocês\6\n", piece[4]);
            if(piece[4])
                add_to_buffer(buffer, "   %s \2eles\6\n", piece[4]);
        } else if(t == 'n'){
            if(piece[1])
                add_to_buffer(buffer, "   não %s \2você\6\n", piece[1]);
            if(piece[1])
                add_to_buffer(buffer, "   não %s \2ele\6\n", piece[1]);
            if(piece[1])
                add_to_buffer(buffer, "   não %s \2a gente\6\n", piece[1]);
            if(piece[4])
                add_to_buffer(buffer, "   não %s \2vocês\6\n", piece[4]);
            if(piece[4])
                add_to_buffer(buffer, "   não %s \2eles\6\n", piece[4]);
        } else if(t == 'm'){
            if(piece[0])
                add_to_buffer(buffer, "   \2eu\6 tinha %s\n", fn[2]);
            if(piece[1])
                add_to_buffer(buffer, "   \2você\6 tinha %s\n", fn[2]);
            if(piece[2])
                add_to_buffer(buffer, "   \2ele\6 tinha %s\n", fn[2]);
            if(piece[3])
                add_to_buffer(buffer, "   \2a gente\6 tinha %s\n", fn[2]);
            if(piece[4])
                add_to_buffer(buffer, "   \2vocês\6 tinham %s\n", fn[2]);
            if(piece[5])
                add_to_buffer(buffer, "   \2eles\6 tinham %s\n", fn[2]);
        } else if(t == 'i'){
            if(piece[0])
                add_to_buffer(buffer, "   \2eu\6 vou %s\n", fn[0]);
            if(piece[1])
                add_to_buffer(buffer, "   \2você\6 vai %s\n", fn[0]);
            if(piece[2])
                add_to_buffer(buffer, "   \2ele\6 vai %s\n", fn[0]);
            if(piece[3])
                add_to_buffer(buffer, "   \2a gente\6 vai %s\n", fn[0]);
            if(piece[4])
                add_to_buffer(buffer, "   \2vocês\6 vão %s\n", fn[0]);
            if(piece[5])
                add_to_buffer(buffer, "   \2eles\6 vão %s\n", fn[0]);
        } else if(t == 's'){
            if(piece[0])
                add_to_buffer(buffer, "   %s \2eu\6 %s\n", conj, piece[0]);
            if(piece[2])
                add_to_buffer(buffer, "   %s \2você\6 %s\n", conj, piece[2]);
            if(piece[2])
                add_to_buffer(buffer, "   %s \2ele\6 %s\n", conj, piece[2]);
            if(piece[2])
                add_to_buffer(buffer, "   %s \2a gente\6 %s\n", conj, piece[2]);
            if(piece[5])
                add_to_buffer(buffer, "   %s \2vocês\6 %s\n", conj, piece[5]);
            if(piece[5])
                add_to_buffer(buffer, "   %s \2eles\6 %s\n", conj, piece[5]);
        } else {
            if(piece[0])
                add_to_buffer(buffer, "   \2eu\6 %s\n", piece[0]);
            if(piece[2])
                add_to_buffer(buffer, "   \2você\6 %s\n", piece[2]);
            if(piece[2])
                add_to_buffer(buffer, "   \2ele\6 %s\n", piece[2]);
            if(piece[2])
                add_to_buffer(buffer, "   \2a gente\6 %s\n", piece[2]);
            if(piece[5])
                add_to_buffer(buffer, "   \2vocês\6 %s\n", piece[5]);
            if(piece[5])
                add_to_buffer(buffer, "   \2eles\6 %s\n", piece[5]);
        }
    }
}

void fix_entry(char *dest, const char *src, char *msg)
{
    int i = 0;
    int l = strlen(src);
    msg[0] = 0;
    if(l > 40){
        strcpy(msg, _("\1The text you entered is too long.\6\n"));
        return;
    } else if(l < 2){
        strcpy(msg, _("\1The text you entered is too short.\6\n"));
        return;
    }

    while(i < l){
        if((src[i] >= 'a' && src[i] <= 'z') || src[i] == '-'){
            dest[i] = src[i];
        } else if(src[i] >= 'A' && src[i] <= 'Z'){
            dest[i] = src[i] + 32;
        } else if(src[i] == '\xc3'){ // Latin 1 subset of UTF-8
            dest[i] = '\xc3';
            i++;
            if(src[i] == '\x81' || src[i] == '\xa1')      // á
                dest[i] = '\xa1';
            else if(src[i] == '\x82' || src[i] == '\xa2') // â
                dest[i] = '\xa2';
            else if(src[i] == '\x83' || src[i] == '\xa3') // ã
                dest[i] = '\xa3';
            else if(src[i] == '\x89' || src[i] == '\xa9') // é
                dest[i] = '\xa9';
            else if(src[i] == '\x8a' || src[i] == '\xaa') // ê
                dest[i] = '\xaa';
            else if(src[i] == '\x8d' || src[i] == '\xad') // í
                dest[i] = '\xad';
            else if(src[i] == '\x93' || src[i] == '\xb3') // ó
                dest[i] = '\xb3';
            else if(src[i] == '\x94' || src[i] == '\xb4') // ô
                dest[i] = '\xb4';
            else if(src[i] == '\x95' || src[i] == '\xb5') // õ
                dest[i] = '\xb5';
            else if(src[i] == '\x9a' || src[i] == '\xba') // ú
                dest[i] = '\xba';
            else if(src[i] == '\x87' || src[i] == '\xa7') // ç
                dest[i] = '\xa7';
            else {
                strcpy(msg, _("\1The text you entered has invalid characters.\6\n"));
                break;
            }
        } else {
            strcpy(msg, _("\1The text you entered has invalid characters.\6\n"));
            break;
        }
        i++;
    }
    dest[i] = 0;
}

void conjugue(char *verb, char *buffer)
{
    Paradigm *p = NULL;
    char *a = NULL;
    int i;
    buffer[0] = 0;

    char v[64];
    char m[128];
    fix_entry(v, verb, m);
    if(*m){
        strcpy(buffer, m);
        return;
    }

    add_to_buffer(buffer, "\5%s\6\n\n", v);

    int isverb = 0;
    i = strlen(v);
    if(i > 1 && v[i-1] == 'r'){
        if(v[i-2] == 'a' || v[i-2] == 'e' || v[i-2] == 'i')
            isverb = 1;
        else if(i > 2 && v[i-2] == 'o' && v[i-3] == 'p')
            isverb = 1; // All verbs ending in "or" end in "por", except pôr.
        else if(i > 3 && v[i-2] == '\xb4' && v[i-3] == '\xc3' && v[i-4] == 'p')
            isverb = 1; // Verb "pôr".
    }
    if(!isverb){
        add_to_buffer(buffer,
                _("\1“%s” is not a verb or is not in the infinitive form.\6\n"), v);
        seek_conjugation(v, buffer);
        return;
    }

    i = get_verb_idx(v);
    if(i >= 0){
        p = Vrb[i].p;
        a = Vrb[i].a;
    } else {
        add_to_buffer(buffer, _("\1“%s” is not in the verbs dataset.\6\n"), v);
    }

    if(p){
        add_to_buffer(buffer, _("\3Paradigm: %s\6\n\n"), p->noun);
    } else {
        p = deduce_paradigm(v);
        if(p){
            add_to_buffer(buffer, _("\3Deduced paradigm: %s\6\n\n"), p->noun);
        } else {
            add_to_buffer(buffer, _("\1I do not know how to conjugate “%s”.\6\n"), v);
            return;
        }
    }

    if(strcmp(p->noun, "doer") == 0)
        add_to_buffer(buffer, _("\1Note: “%s” is irregular and defective, being "
                    "conjugated only in the third persons (singular and "
                    "plural). However, the complete conjugation is being "
                    "outputted here because\6 \3“%s-se”\6 \1is conjugated in "
                    "all persons.\6\n\n"), v, v);

    ConjugatedVerb *vv = conjugate_one(v, p, a);

    add_to_buffer(buffer, "\4Formas Nominais\6\n");
    add_to_buffer(buffer, "   infinitivo: %s\n", vv->FN[0]);
    add_to_buffer(buffer, "   gerúndio: %s\n", vv->FN[1]);
    add_to_buffer(buffer, "   particípio: %s", vv->FN[2]);

    if(vv->a)
        add_to_buffer(buffer, ", %s\n", vv->a);
    else
        add_to_buffer(buffer, "\n");

    add_tempo(buffer, "Presente do Indicativo",            vv->PI,   0,   NULL, NULL);
    add_tempo(buffer, "Imperfeito do Indicativo",          vv->II,   0,   NULL, NULL);
    add_tempo(buffer, "Perfeito do Indicativo",            vv->EI,   0,   NULL, NULL);
    add_tempo(buffer, "Mais-que-perfeito do Indicativo",   vv->MI, 'm', vv->FN, NULL);
    add_tempo(buffer, "Futuro do Pretérito do Indicativo", vv->TI,   0,   NULL, NULL);
    add_tempo(buffer, "Futuro do Presente do Indicativo",  vv->FI, 'i', vv->FN, NULL);
    add_tempo(buffer, "Presente do Subjuntivo",            vv->PS, 's',   NULL, "que");
    add_tempo(buffer, "Imperfeito do Subjuntivo",          vv->IS, 's',   NULL, "se");
    add_tempo(buffer, "Futuro do Subjuntivo",              vv->FS, 's',   NULL, "quando");
    add_tempo(buffer, "Imperativo Afirmativo",             vv->IA, 'a',   NULL, NULL);
    add_tempo(buffer, "Imperativo Negativo",               vv->IN, 'n',   NULL, NULL);
    add_tempo(buffer, "Infinitivo Pessoal",                vv->IP,   0,   NULL, NULL);

    free_conjugated_verb(vv);
}

static Paradigm *initialize_paradigm(Paradigm *P, const char *s)
{
    Paradigm *tmp = (Paradigm*)calloc(1, sizeof(Paradigm));
    if(P){
        tmp->FN = P->FN; // Each paradigm is a copy of the previous
        tmp->IP = P->IP; // one, unless redeclared.
        tmp->PI = P->PI;
        tmp->II = P->II;
        tmp->EI = P->EI;
        tmp->MI = P->MI;
        tmp->TI = P->TI;
        tmp->FI = P->FI;
        tmp->PS = P->PS;
        tmp->IS = P->IS;
        tmp->FS = P->FS;
        tmp->IA = P->IA;
        tmp->IN = P->IN;
    }
    Prdgm[NP] = tmp;
    NP++;
    if(NP >= MAXPRDGMS){
        fprintf(stderr, _("Maximum number of paradigms surpassed!\n"));
        exit(1);
    }

    // Get root
    int i = 10;
    int j = 0;
    char p[64];
    while(s[i] != ':' && s[i] != 0){
        p[j] = s[i];
        i++; j++;
    }
    p[j] = 0;
    i++;
    tmp->root = (char*)calloc(sizeof(char), (strlen(p) + 1));
    strcpy(tmp->root, p);

    // Get suffix
    j = 0;
    while(s[i] != '\n' && s[i] != '\r' && s[i] != ':' && s[i] != 0){
        p[j] = s[i];
        i++; j++;
    }
    p[j] = 0;
    tmp->suffix = (char*)calloc(sizeof(char), (strlen(p) + 1));
    strcpy(tmp->suffix, p);

    // Get "abundante" form, if any
    if(s[i] == ':'){
        i++;
        j = 0;
        while(s[i] != '\n' && s[i] != '\r' && s[i] != ':' && s[i] != 0){
            p[j] = s[i];
            i++; j++;
        }
        p[j] = 0;
    } else {
        p[0] = 0;
    }

    // Build noun
    tmp->noun = (char*)calloc(sizeof(char),
            (strlen(tmp->root) + strlen(tmp->suffix) + 1));
    sprintf(tmp->noun, "%s%s", tmp->root, tmp->suffix);

    // Add paradigm itself to the list of verbs
    if(p[0] == 0)
        add_verb(tmp->noun, tmp, NULL);
    else
        add_verb(tmp->noun, tmp, p);

    return(tmp);
}

static char **slice_str(const char *s, int n)
{
    int i = 0;
    int j, l;
    char b[32];
    char **r = (char**)calloc(sizeof(char*), n);

    // Skip the label
    while(s[i] != ':' && s[i] != '\n'){
        i++;
    }
    i++;
    for(int p = 0; p < n; p++){
        j = 0;
        while(s[i] != ':' && s[i] != '\n'){
            b[j] = s[i];
            i++; j++;
        }
        b[j] = 0;
        i++;
        l = strlen(b); // zero if defective
        if(l){
            r[p] = (char*)calloc(sizeof(char), (strlen(b)+1));
            strcpy(r[p], b);
            b[0] = 0;
        }
    }
    return r;
}

void read_verbs_file()
{
    int l = strlen(PACKAGE_LIB_DIR) + strlen("/paradigms_and_verbs") + 2;
    verbsFile = (char*)calloc(l, sizeof(char));
    snprintf(verbsFile, l - 1, "%s/paradigms_and_verbs", PACKAGE_LIB_DIR);

    FILE *F = fopen(verbsFile, "r");
    if(F == NULL){
        fprintf(stderr, _("Error: \"%s\" not found.\n"), verbsFile);
        exit(1);
    }

    int linha = 0;
    int get_conjugations = 0;
    int get_verbs = 1;
    if(F){
        char s[256];// linha
        Paradigm *P = NULL;
        Prdgm = (Paradigm**)calloc(MAXPRDGMS, sizeof(Paradigm*));
        Vrb = (Verb*)calloc(MAXVRBS, sizeof(Verb));
        while(fgets(s, 255, F)){
            linha++;
            if(s[0] == '#' || strlen(s) < 3)
                continue;

            if(s[0] == '0' && s[1] == '0' && s[2] == '0' && s[3] == '0')
                break; // Begin of list of non classified verbs

            if(get_conjugations){
                if(s[0] == 'F' && s[1] == 'N' && s[2] == ':'){
                    P->FN = slice_str(s, 3);
                } else if(s[0] == 'I' && s[1] == 'P' && s[2] == ':'){
                    P->IP = slice_str(s, 6);
                } else if(s[0] == 'P' && s[1] == 'I' && s[2] == ':'){
                    P->PI = slice_str(s, 6);
                } else if(s[0] == 'I' && s[1] == 'I' && s[2] == ':'){
                    P->II = slice_str(s, 6);
                } else if(s[0] == 'E' && s[1] == 'I' && s[2] == ':'){
                    P->EI = slice_str(s, 6);
                } else if(s[0] == 'M' && s[1] == 'I' && s[2] == ':'){
                    P->MI = slice_str(s, 6);
                } else if(s[0] == 'T' && s[1] == 'I' && s[2] == ':'){
                    P->TI = slice_str(s, 6);
                } else if(s[0] == 'F' && s[1] == 'I' && s[2] == ':'){
                    P->FI = slice_str(s, 6);
                } else if(s[0] == 'P' && s[1] == 'S' && s[2] == ':'){
                    P->PS = slice_str(s, 6);
                } else if(s[0] == 'I' && s[1] == 'S' && s[2] == ':'){
                    P->IS = slice_str(s, 6);
                } else if(s[0] == 'F' && s[1] == 'S' && s[2] == ':'){
                    P->FS = slice_str(s, 6);
                } else if(s[0] == 'I' && s[1] == 'A' && s[2] == ':'){
                    P->IA = slice_str(s, 6);
                } else if(s[0] == 'I' && s[1] == 'N' && s[2] == ':'){
                    P->IN = slice_str(s, 6);
                } else{
                    get_conjugations = 0;
                    get_verbs = 1;
                }
            }

            if(get_verbs){

                // Found a paradigm while collecting verbs
                if(s[0] == 'p' && s[1] == 'a' && s[2] == 'r' && s[3] == 'a'  &&
                        s[4] == 'd' && s[5] == 'i' && s[6] == 'g' && s[7] == 'm' &&
                        s[8] == 'a' && s[9] == ':'){
                    P = initialize_paradigm(P, s);
                    get_conjugations = 1;
                    get_verbs = 0;
                    continue;
                }

                // This line has a verb. Get it.
                Vrb[NV].p = P;
                int i = 0;
                char b[64];
                while(s[i] != ':' && s[i] != '\n' && s[i] != '\r'){
                    b[i] = s[i];
                    i++;
                }
                b[i] = 0;
                if(s[i] == ':'){
                    char a[32];
                    i++;
                    int j = 0;
                    while(s[i] != '\n' && s[i] != '\r'){
                        a[j] = s[i];
                        i++; j++;
                    }
                    a[j] = 0;
                    add_verb(b, P, a);
                } else {
                    add_verb(b, P, NULL);
                }
            }
        }
        NVC = NV; // Number of classified verbs.

        // Get verbs that are in the data base, but do not have
        // a defined paradigm yet
        while(fgets(s, 255, F) && NV < MAXVRBS){
            linha++;
            l = strlen(s);
            if(s[0] == '#' || l < 3)
                continue;
            s[l-1] = 0;
            Vrb[NV].p = NULL;
            Vrb[NV].v = (char*)calloc(l, (sizeof(char)));
            strcpy(Vrb[NV].v, s);
            NV++;
        }
        fclose(F);
    }
}

void clean_text_buffer(char *b2, char *b)
{
    // Remove tags included for GtkTextBuffer, --color and --xml
    while(*b != 0){
        if(*b > 0 && *b < 8)
            b++;
        *b2 = *b;
        b++; b2++;
    }
    *b2 = 0;
}

static char *addTag(char *b2, char tag, char *lasttag)
{
    *b2 = '<'; b2++;
    if(tag == 0){
        *b2 = '/'; b2++;
    } else {
        *lasttag = tag;
    }
    *b2 = *lasttag; b2++;
    *b2 = '>'; b2++;
    return(b2);
}

void xml_text_buffer(char *b2, char *b)
{
    // Replace binary flags with xml tags
    char lasttag = 0;
    while(*b != 0){
        switch(*b){
            case 1:
                b2 = addTag(b2, 'r', &lasttag);
                break;
            case 2:
                b2 = addTag(b2, 'p', &lasttag);
                break;
            case 3:
                b2 = addTag(b2, 'b', &lasttag);
                break;
            case 4:
                b2 = addTag(b2, 's', &lasttag);
                break;
            case 5:
                b2 = addTag(b2, 'l', &lasttag);
                break;
            case 6:
                b2 = addTag(b2, 0, &lasttag);
                break;
            default:
                *b2 = *b;
                b2++;
                break;
        }
        b++;
    }
    *b2 = 0;
}

static char *addColor(char *b2, unsigned int color, int bold)
{
    *b2 = '\x1b'; b2++;
    *b2 = '['; b2++;
    if(color != '0'){
        *b2 = '3'; b2++;
    }
    *b2 = color; b2++;
    if(bold){
        *b2 = ';'; b2++;
        *b2 = '1'; b2++;
    }
    *b2 = 'm'; b2++;
    return(b2);
}

void color_text_buffer(char *b2, char *b)
{
    // Replace binary flags with ANSI escape codes
    while(*b != 0){
        switch(*b){
            case 1:
                b2 = addColor(b2, '1', 0);
                break;
            case 2:
                b2 = addColor(b2, '2', 0);
                break;
            case 3:
                b2 = addColor(b2, '6', 0);
                break;
            case 4:
                b2 = addColor(b2, '7', 1);
                break;
            case 5:
                b2 = addColor(b2, '3', 0);
                break;
            case 6:
                b2 = addColor(b2, '0', 0);
                break;
            default:
                *b2 = *b;
                b2++;
                break;
        }
        b++;
    }
    *b2 = 0;
}

// For debugging purposes: reproducing (almost exactly) the output of
// conjugue -v FORMATO=ll < listaDeVerbos > todosOsVerbosOficial
void conjugue_all()
{
    int i;
    char b[20000];
    char b2[20000];

    FILE *P = fopen(_("list_of_paradigms"), "w");
    for(i = 0; i < NP; i++)
        fprintf(P, "%s\n", Prdgm[i]->noun);
    fclose(P);

    FILE *F = fopen(_("list_of_verbs"), "w");
    FILE *C = fopen(_("all_verbs"), "w");
    for(i = 0; i < NV; i++){
        conjugue(Vrb[i].v, b);
        clean_text_buffer(b2, b);
        fprintf(C, "%s", b2);
        fprintf(F, "%s\n", Vrb[i].v);
    }
    fclose(F);
    fclose(C);

    fprintf(stderr, "%s = %d\n%s = %d\n", _("paradigms"), NP, _("verbs"), NV);
    fprintf(stderr, _("See the files: “%s”, “%s” and “%s”.\n"), _("list_of_verbs"),
            _("list_of_paradigms"), _("all_verbs"));
}

static int compare_verbs(const void *a, const void *b)
{
    const Verb *c = (const Verb*)a;
    const Verb *d = (const Verb*)b;
    return strcmp(c->v, d->v);
}

static int compare_str(const void *a, const void *b)
{
    const char **c = (const char**)a;
    const char **d = (const char**)b;
    return strcmp(*c, *d);
}

void list_verbs(char *buffer)
{
    char str[128];
    char *lastP = (char*)calloc(128, sizeof(char));
    int i = 0, j = 0, k;
    Paradigm *P;
    Verb *V = Vrb;
    char **v = (char**)calloc(NV, sizeof(char*));

    strncat(buffer, "\n\5", 1511999);
    strncat(buffer, _("Paradigmatic verbs and their followers"), 1511999);
    strncat(buffer, "\6\n\n", 1511999);

    while(i < NV && Vrb[i].p){
        if(Vrb[i].p->noun == NULL){
            fprintf(stderr, "ERRRRRRR\n");
            exit(1);
        }
        if(strcmp(lastP, Vrb[i].p->noun) != 0){
            if(strcmp(Vrb[i].v, Vrb[i].p->noun) != 0)
                // Should never happen
                strncat(str, "\1ERROR: verb != paradigm\6\n", 127);
            if(j > 1)
                qsort(v, j, sizeof(char*), compare_str);
            for(k = 0; k < j; k++){
                snprintf(str, 127, "   %s\n", v[k]);
                strncat(buffer, str, 1511999);
            }
            j = 0;
            snprintf(str, 127, "\n\4%s\6\n", Vrb[i].v);
            strncpy(lastP, Vrb[i].p->noun, 127);
            strncat(buffer, str, 1511999);
        } else{
            v[j] = Vrb[i].v;
            j++;
        }
        i++;
        V++;
    }
    free(v);
    free(lastP);

    strncat(buffer, "\n\5", 1511999);
    strncat(buffer, _("Verbs with deduced paradigms"), 1511999);
    strncat(buffer, "\6\n\n", 1511999);

    if(sorted == 0){
        qsort(V, (NV - i), sizeof(Verb), compare_verbs);
        sorted = 1;
    }

    while(i < NV){
        if(Vrb[i].p){
            // Should never happen
            snprintf(str, 127, "\n\1ERROR in the verbs dataset: [%s %s]\6\n\n",
                    Vrb[i].v, Vrb[i].p->noun);
        } else{
            P = deduce_paradigm(Vrb[i].v);
            if(P == NULL)
                // Should never happen
                snprintf(str, 127,
                        "\1ERROR trying to deduce the paradigm of verb “%s”.\6\n",
                        Vrb[i].v);
            else
                snprintf(str, 127, "%s (%s)\n", Vrb[i].v, P->noun);
        }
        strncat(buffer, str, 1511999);
        i++;
    }
}

void list_prdgms(char *buffer)
{
    char str[128];
    int i;

    strncat(buffer, "\n\5", 1511999);
    strncat(buffer, _("Verbs used as paradigms"), 1511999);
    strncat(buffer, "\6\n\n", 1511999);

    char **p = (char**)calloc(NP, sizeof(char*));
    for(i = 0; i < NP; i++)
        p[i] = Prdgm[i]->noun;
    qsort(p, NP, sizeof(char*), compare_str);

    i = 0;
    while(i < NP){
        snprintf(str, 127, "%s\n", p[i]);
        strncat(buffer, str, 1511999);
        i++;
    }
    free(p);
}
