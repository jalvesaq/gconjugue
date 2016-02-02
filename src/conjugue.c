/* This file is part of gconjugue
 **
 ** It is distributed under the GNU General Public License.
 ** See the file COPYING for details.
 ** 
 ** (c) 2005-2011 Jakson Aquino: jalvesaq@gmail.com
 **
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <glib.h>

#include "conjugue.h"

#include <libintl.h>
#include <locale.h>

#define _(string) gettext(string)

typedef struct {
    char *paradigma;
    char *FN; // Formas nominais
    char *IP; // Infinitivo pessoal
    char *PI; // Presente do indicativo
    char *II; // Imperfeito do indicativo
    char *EI; // Perfeito do indicativo
    char *MI; // Mais-que-perfeito do indicativo
    char *TI; // Futuro do pretérito
    char *FI; // Futuro do presente
    char *PS; // Presente do subjuntivo
    char *IS; // Imperfeito do subjuntivo
    char *FS; // Futuro do subjuntivo
    char *IA; // Imperativo afirmativo
    char *IN; // Imperativo negativo
    char *obs;
} Paradigma;

typedef struct {
    Paradigma *p;
    char * v; // verb
    char * a; // abundante
} Verbo;

int np, nv, nvc; // number of paradigms and number of verbs
int sorted = 0;
Paradigma **prdgm;
Verbo *vrb;
char *verbsFile;

#define MAXPRDGMS 200
#define MAXVRBS 20000

void formatPiece(char *pverb, char *sufix, char *verb, char *piece)
{
    int ls, lv, lp, lpv, i, j;
    lv = strlen(verb);
    lp = strlen(piece);
    lpv = strlen(pverb);
    ls = strlen(sufix);
    char root[64];
    strncpy(root, verb, 63);
    i = lv - ls;
    j = lpv - ls;
    while(j < lp && piece[j] != 0){
        root[i] = piece[j];
        i++; j++;
    }
    root[i] = 0;

    strncpy(piece, root, 63);
}

void breakLine(char *line, char **piece, char *verb)
{
    int i, j;
    char *ln = line;
    char suf[16];
    char pverb[64];
    for(i = 0; i < 6; i++)
        piece[i][0] = 0;

    // get root
    i = 0;
    while(*ln != ':' && *ln != '\n' && i < 64){
        pverb[i] = *ln;
        ln++;
        i++;
    }
    pverb[i] = 0;
    ln++;
    if(*ln == '\n'){
        fprintf(stderr, "error: %s %d\n", __FILE__, __LINE__);
        exit(1);
    }


    // get suffix
    i = 0;
    while(*ln != ':' && *ln != '\n' && i < 16){
        suf[i] = *ln;
        ln++;
        i++;
    }
    suf[i] = 0;
    ln++;
    if(*ln == '\n'){
        fprintf(stderr, "error: %s %d\n", __FILE__, __LINE__);
        exit(1);
    }

    // skip type of conjugation
    while(*ln != ':' && *ln != '\n')
        ln++;
    ln++;
    if(*ln == '\n'){
        fprintf(stderr, "error: %s %d\n", __FILE__, __LINE__);
        exit(1);
    }

    i = 0;
    j = 0;
    while(1){
        if(*ln == ':' || *ln == '\n'){ // verbo defectivo
            i++;
            ln++;
            if(*ln == '\n' || *ln == 0)
                break;
            continue;
        }
        piece[i][j] = *ln;
        j++;
        ln++;
        if(*ln == ':'){
            piece[i][j] = 0;
            formatPiece(pverb, suf, verb, piece[i]);
            ln++;
            j = 0;
            i++;
        } else
            if(*ln == '\n' || *ln == 0){
                piece[i][j] = 0;
                formatPiece(pverb, suf, verb, piece[i]);
                break;
            }
        if(i == 6)
            break;
    }
}

Paradigma *pegarParadigma(const char *v)
{
    int i;
    for(i = 0; i < nv; i++)
        if(strcmp(vrb[i].v, v) == 0)
            return(vrb[i].p);
    return NULL;
}

Paradigma *deduzirParadigma(char *v)
{
    Paradigma *p01 = pegarParadigma("abraçar");
    /*Paradigma *p02 = pegarParadigma("apoiar");*/
    Paradigma *p03 = pegarParadigma("chegar");
    Paradigma *p04 = pegarParadigma("comunicar");
    Paradigma *p05 = pegarParadigma("magoar");
    Paradigma *p06 = pegarParadigma("passear");
    Paradigma *p07 = pegarParadigma("cantar");

    Paradigma *p08 = pegarParadigma("conhecer");
    Paradigma *p09 = pegarParadigma("erguer");
    Paradigma *p10 = pegarParadigma("proteger");
    Paradigma *p11 = pegarParadigma("vender");

    Paradigma *p12 = pegarParadigma("ruir");
    Paradigma *p13 = pegarParadigma("extinguir");
    Paradigma *p14 = pegarParadigma("atribuir");
    Paradigma *p15 = pegarParadigma("cair");
    Paradigma *p16 = pegarParadigma("afligir");
    Paradigma *p17 = pegarParadigma("traduzir");
    Paradigma *p18 = pegarParadigma("partir");

    Paradigma *p19 = pegarParadigma("propor");

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

int pegarVerboIdx(char *v)
{
    // TODO: qsort and binary search or verbs in a tree.
    int i;
    for(i = 0; i < nv; i++)
        if(strcmp(vrb[i].v, v) == 0)
            return i;
    return -1;

}

void adicionar(char *b1, const char *fmt, ...)
{
    va_list argptr;
    char msg[255];
    char msg2[255];
    va_start(argptr, fmt);
    strncpy(msg, fmt, 254);
    vsnprintf(msg2, 254, msg, argptr);
    strncat(b1, msg2, 19998);
}

void adicionarSeis(char *buffer, char **piece)
{
    if(piece[0][0])
        adicionar(buffer, "   eu %s\n", piece[0]);
    if(piece[1][0])
        adicionar(buffer, "   tu %s\n", piece[1]);
    if(piece[2][0])
        adicionar(buffer, "   ele %s\n", piece[2]);
    if(piece[3][0])
        adicionar(buffer, "   nós %s\n", piece[3]);
    if(piece[4][0])
        adicionar(buffer, "   vós %s\n", piece[4]);
    if(piece[5][0])
        adicionar(buffer, "   eles %s\n", piece[5]);
}

int conjugue(char *v, char *buffer){
    Paradigma *P = NULL;
    Verbo *V = NULL;
    char *piece[6];
    int i;
    buffer[0] = 0;
    adicionar(buffer, "\1%s\5\n\n", v);

    i = pegarVerboIdx(v);
    if(i == -1)
        adicionar(buffer, "\2Não consta do banco de verbos\5\n");
    else
        V = &(vrb[i]);

    if(V && V->p){
        P = V->p;
        adicionar(buffer, "\3Paradigma: %s\5\n\n", P->paradigma);
        if(strcmp(V->p->paradigma, "doer") == 0)
            adicionar(buffer, "\2Observação: Doer e condoer são irregulares e "
                    "defectivos, só se conjugando nas terceiras pessoas. Por outro "
                    "lado,\5 \3doer-se\5 \2e\5 \3condoer-se\5 \2conjugam-se em todas "
                    "as pessoas, por isso estamos indicando aqui a conjugação "
                    "completa.\5\n\n");
    } else{
        i = strlen(v);
        if(v[i-1] != 'r'){
            adicionar(buffer, "\2“%s” não é verbo ou não está no infinitivo.\n\5", v);
            return 0;
        }
        P = deduzirParadigma(v);
        if(P)
            adicionar(buffer, "\3Paradigma deduzido: %s\5\n\n", P->paradigma);
        else {
            adicionar(buffer, "\2Não sei conjugar “%s”\n\5", v);
            return 0;
        }
    }

    for(i = 0; i < 6; i++)
        piece[i] = (char*)malloc(64 * sizeof(char));

    adicionar(buffer, "\4Formas Nominais\5\n");
    breakLine(P->FN, piece, v);
    adicionar(buffer, "   infinitivo: %s\n", piece[0]);
    adicionar(buffer, "   gerúndio: %s\n", piece[1]);
    adicionar(buffer, "   particípio: %s", piece[2]);
    if(V && V->a)
        adicionar(buffer, ",%s\n", V->a);
    else
        adicionar(buffer, "\n");

    adicionar(buffer, "\n\4Presente do Indicativo\5\n");
    breakLine(P->PI, piece, v);
    adicionarSeis(buffer, piece);

    adicionar(buffer, "\n\4Imperfeito do Indicativo\5\n");
    breakLine(P->II, piece, v);
    adicionarSeis(buffer, piece);

    adicionar(buffer, "\n\4Perfeito do Indicativo\5\n");
    breakLine(P->EI, piece, v);
    adicionarSeis(buffer, piece);

    adicionar(buffer, "\n\4Mais-que-perfeito do Indicativo\5\n");
    breakLine(P->MI, piece, v);
    adicionarSeis(buffer, piece);

    adicionar(buffer, "\n\4Futuro do Pretérito do Indicativo\5\n");
    breakLine(P->TI, piece, v);
    adicionarSeis(buffer, piece);

    adicionar(buffer, "\n\4Futuro do Presente do Indicativo\5\n");
    breakLine(P->FI, piece, v);
    adicionarSeis(buffer, piece);

    adicionar(buffer, "\n\4Presente do Subjuntivo\5\n");
    breakLine(P->PS, piece, v);
    adicionarSeis(buffer, piece);

    adicionar(buffer, "\n\4Imperfeito do Subjuntivo\5\n");
    breakLine(P->IS, piece, v);
    adicionarSeis(buffer, piece);

    adicionar(buffer, "\n\4Futuro do Subjuntivo\5\n");
    breakLine(P->FS, piece, v);
    adicionarSeis(buffer, piece);

    adicionar(buffer, "\n\4Imperativo Afirmativo\5\n");
    breakLine(P->IA, piece, v);
    if(piece[0][0])
        adicionar(buffer, "   %s tu\n", piece[0]);
    if(piece[1][0])
        adicionar(buffer, "   %s ele\n", piece[1]);
    if(piece[2][0])
        adicionar(buffer, "   %s nós\n", piece[2]);
    if(piece[3][0])
        adicionar(buffer, "   %s vós\n", piece[3]);
    if(piece[4][0])
        adicionar(buffer, "   %s eles\n", piece[4]);

    adicionar(buffer, "\n\4Imperativo Negativo\5\n");
    breakLine(P->IN, piece, v);
    if(piece[0][0])
        adicionar(buffer, "   não %s tu\n", piece[0]);
    if(piece[1][0])
        adicionar(buffer, "   não %s ele\n", piece[1]);
    if(piece[2][0])
        adicionar(buffer, "   não %s nós\n", piece[2]);
    if(piece[3][0])
        adicionar(buffer, "   não %s vós\n", piece[3]);
    if(piece[4][0])
        adicionar(buffer, "   não %s eles\n", piece[4]);

    adicionar(buffer, "\n\4Infinitivo Pessoal\5\n");
    breakLine(P->IP, piece, v);
    adicionarSeis(buffer, piece);

    for(i = 0; i < 6; i++)
        free(piece[i]);
    return 1;
}

int abundante(char *s)
{
    int i = 10, j = 0, k, x = -1;
    char a[64];
    while(s[i] != ':'){
        a[j] = s[i];
        i++; j++;
    }
    a[j] = 0;
    i++;

    for(k = 0; k < nv; k++)
        if(strcmp(vrb[k].v, a) == 0){
            x = k;
            break;
        }

    if(x == -1){
        return 1;
    }

    j = 0;
    while(s[i] != '\n'){
        a[j] = s[i];
        i++; j++;
    }
    a[j] = 0;
    j++;
    vrb[x].a = (char*)malloc(j * sizeof(char));
    strcpy(vrb[x].a, a);
    return 0;
}

Paradigma *restaurarParadigma(char *s)
{
    char verbo[64];
    while(*s != ':')
        s++;
    s++;
    int i = 0;
    while(*s != '\n'){
        verbo[i] = *s;
        s++; i++;
    }
    verbo[i] = 0;
    for(i = 0; i < np; i++)
        if(strcmp(prdgm[i]->paradigma, verbo) == 0){
            Paradigma *P = (Paradigma*)malloc(sizeof(Paradigma));
            memcpy(P, prdgm[i], sizeof(Paradigma));
            return(P);
        }
    if(i == np){
        fprintf(stderr, "Erro: paradigma “%s” não encontrado.\n", verbo);
        exit(1);
    }
    return NULL;
}

void read_verbs_file()
{
    int l = strlen(PACKAGE_LIB_DIR) + strlen("/BancoDeVerbos") + 2;
    verbsFile = (char*)malloc(l * sizeof(char));
    snprintf(verbsFile, l - 1, "%s/BancoDeVerbos", PACKAGE_LIB_DIR);

    FILE *F = fopen(verbsFile, "r");
    if(F == NULL){
        fprintf(stderr, _("Error: \"%s\" not found.\n"), verbsFile);
        exit(1);
    }

    int linha = 0;
    if(F){
        char s[256];// linha
        char p[64]; // paradigma
        char x[64]; // sufixo
        char *str;
        int i = 0, pcopiado = 0, j;
        Paradigma *tmp;
        Paradigma *P = NULL;
        prdgm = (Paradigma**)calloc(MAXPRDGMS, sizeof(Paradigma*));
        vrb = (Verbo*)calloc(MAXVRBS, sizeof(Verbo));
        while(fgets(s, 255, F)){
            linha++;
            if(s[0] == '#' || strlen(s) < 3)
                continue;
            if(s[0] == 'p' && s[1] == 'a' && s[2] == 'r' && s[3] == 'a'  && 
                    s[4] == 'd' && s[5] == 'i' && s[6] == 'g' && s[7] == 'm' &&
                    s[8] == 'a' && s[9] == ':'){
                if(s[10] == '\n')
                    break; // início da lista de verbos não classificados
                tmp = (Paradigma*)calloc(1, sizeof(Paradigma));
                if(P){
                    tmp->FN = P->FN; // Cada paradigma é uma cópia do
                    tmp->IP = P->IP; // seu antecessor, com exceção das
                    tmp->PI = P->PI; // das conjugações explicitamente
                    tmp->II = P->II; // indicadas.
                    tmp->EI = P->EI;
                    tmp->MI = P->MI;
                    tmp->TI = P->TI;
                    tmp->FI = P->FI;
                    tmp->PS = P->PS;
                    tmp->IS = P->IS;
                    tmp->FS = P->FS;
                    tmp->IA = P->IA;
                    tmp->IN = P->IN;
                    if(pcopiado){
                        pcopiado = 0;
                        free(P);
                    }
                }
                P = tmp;
                prdgm[np] = P;
                np++;
                if(np >= MAXPRDGMS){
                    fprintf(stderr, "Maximo numero de paradigmas superado!\n");
                    exit(1);
                }
                i = 10;
                j = 0;
                while(s[i] != ':' && s[i] != '\n' && s[i] != ' '){
                    p[j] = s[i];
                    i++; j++;
                }
                p[j] = 0;
                if(s[i] != '\n'){
                    i++;
                    j = 0;
                    while(!(s[i] == '\n' || s[i] == ' ')){
                        x[j] = s[i];
                        i++; j++;
                    }
                    x[j] = 0;
                } else{
                    x[0] = 0;
                }
                l = strlen(p) + 2;
                P->paradigma = (char*)malloc(l * sizeof(char));
                strcpy(P->paradigma, p);
                s[0] = 0;
                vrb[nv].p = P;
                l = strlen(P->paradigma) + 2;
                vrb[nv].v = (char*)malloc(l * sizeof(char));
                strcpy(vrb[nv].v, P->paradigma);
                nv++;
                if(nv >= MAXVRBS){
                    fprintf(stderr, "Maximo numero de verbos superado!\n");
                    exit(1);
                }
            } else
                if(s[0] == 'a' && s[1] == 'b' && s[2] == 'u' && s[3] == 'n'  && 
                        s[4] == 'd' && s[5] == 'a' && s[6] == 'n' && s[7] == 't' &&
                        s[8] == 'e' && s[9] == ':'){
                    if(abundante(s))
                        fprintf(stderr, "Aviso: verbo não declarado ainda (%s, linha %d) %s",
                                verbsFile, linha, s);
                } else
                    if(s[0] == 'r' && s[1] == 'e' && s[2] == 's' && s[3] == 't'  && 
                            s[4] == 'a' && s[5] == 'u' && s[6] == 'r' && s[7] == 'a' &&
                            s[8] == 'r' && s[9] == ':'){
                        P = restaurarParadigma(s);
                        pcopiado = 1;
                    } else {
                        l = strlen(P->paradigma) + strlen(s) + strlen(x) + 6;
                        str = (char*)malloc(l * sizeof(char));
                        snprintf(str, l - 1,  "%s:%s:%s", P->paradigma, x, s);
                        if(s[0] == 'F' && s[1] == 'N' && s[2] == ':'){
                            P->FN = str;
                        } else if(s[0] == 'I' && s[1] == 'P' && s[2] == ':'){
                            P->IP = str;
                        } else if(s[0] == 'P' && s[1] == 'I' && s[2] == ':'){
                            P->PI = str;
                        } else if(s[0] == 'I' && s[1] == 'I' && s[2] == ':'){
                            P->II = str;
                        } else if(s[0] == 'E' && s[1] == 'I' && s[2] == ':'){
                            P->EI = str;
                        } else if(s[0] == 'M' && s[1] == 'I' && s[2] == ':'){
                            P->MI = str;
                        } else if(s[0] == 'T' && s[1] == 'I' && s[2] == ':'){
                            P->TI = str;
                        } else if(s[0] == 'F' && s[1] == 'I' && s[2] == ':'){
                            P->FI = str;
                        } else if(s[0] == 'P' && s[1] == 'S' && s[2] == ':'){
                            P->PS = str;
                        } else if(s[0] == 'I' && s[1] == 'S' && s[2] == ':'){
                            P->IS = str;
                        } else if(s[0] == 'F' && s[1] == 'S' && s[2] == ':'){
                            P->FS = str;
                        } else if(s[0] == 'I' && s[1] == 'A' && s[2] == ':'){
                            P->IA = str;
                        } else if(s[0] == 'I' && s[1] == 'N' && s[2] == ':'){
                            P->IN = str;
                        } else{
                            vrb[nv].p = P;
                            l = strlen(s);
                            vrb[nv].v = (char*)malloc(l * (sizeof(char) + 1));
                            strcpy(vrb[nv].v, s);
                            vrb[nv].v[l-1] = 0;
                            nv++;
                            free(str);
                        }
                    }
        }
        nvc = nv; // Number of classified verbs.

        // Get verbs that are in the data base, but do not have
        // a defined paradigm yet
        while(fgets(s, 255, F) && nv < MAXVRBS){
            linha++;
            l = strlen(s);
            if(s[0] == '#' || l < 3)
                continue;
            s[l-1] = 0;
            vrb[nv].p = NULL;
            vrb[nv].v = (char*)malloc(l * (sizeof(char)));
            strcpy(vrb[nv].v, s);
            nv++;
        }
        fclose(F);
    }
}


void cleanTextBuffer(char *b2, char *b)
{
    // skip the first line
    while(!(*b == '\n' || *b == 0))
        b++;

    // remove tags included for GtkTextBuffer
    while(*b != 0){
        if(*b > 0 && *b < 8)
            b++;
        *b2 = *b;
        b++; b2++;
    }
    *b2 = 0;
}

/* 
   For debugging purposes: reproducing (almost exactly) the output of
   conjugue -v FORMATO=ll < listaDeVerbos > todosOsVerbosOficial
   */
void compare(){
    int i;
    char b[20000];
    char b2[20000];

    FILE *P = fopen("listaDeParadigmas", "w");
    for(i = 0; i < np; i++)
        fprintf(P, "%s\n", prdgm[i]->paradigma);
    fclose(P);

    FILE *F = fopen("listaDeVerbos", "w");
    FILE *C = fopen("todosOsVerbos", "w");
    for(i = 0; i < nv; i++){
        conjugue(vrb[i].v, b);
        cleanTextBuffer(b2, b);
        fprintf(C, "%s", b2);
        fprintf(F, "%s\n", vrb[i].v);
    }
    fclose(F);
    fclose(C);

    fprintf(stderr, "%s = %d, %s = %d\n", _("paradigms"), np, _("verbs"), nv);
    fprintf(stderr, _("See the files %s, %s, and %s"), "“listaDeVerbos”",
            "“listaDeParadigmas”", "“todosOsVerbos”\n");
}

int compareVerbs(const void *a, const void *b)
{
    const Verbo *c = (const Verbo*)a;
    const Verbo *d = (const Verbo*)b;
    return g_utf8_collate(c->v, d->v);
}

int compareStr(const void *a, const void *b)
{
    const char **c = (const char**)a;
    const char **d = (const char**)b;
    return g_utf8_collate(*c, *d);
}

void listVerbs(char *buffer)
{
    char str[128];
    char *lastP = (char*)calloc(128, sizeof(char));
    int i = 0, j = 0, k;
    Paradigma *P;
    Verbo *V = vrb;
    char **v = (char**)malloc(nv * sizeof(char*));

    strncat(buffer, "\n\1Verbos paradigmáticos e seus seguidores\5\n\n", 1511999);

    while(i < nv && vrb[i].p){
        if(vrb[i].p->paradigma == NULL){
            fprintf(stderr, "ERRRRRRR\n");
            exit(1);
        }
        if(strcmp(lastP, vrb[i].p->paradigma) != 0){
            if(strcmp(vrb[i].v, vrb[i].p->paradigma) != 0)
                strncat(str, "\2ERRO: verbo != paradigma\5\n", 127);
            if(j > 1)
                qsort(v, j, sizeof(char*), compareStr);
            for(k = 0; k < j; k++){
                snprintf(str, 127, "   %s\n", v[k]);
                strncat(buffer, str, 1511999);
            }
            j = 0;
            snprintf(str, 127, "\n\4%s\5\n", vrb[i].v);
            strncpy(lastP, vrb[i].p->paradigma, 127);
            strncat(buffer, str, 1511999);
        } else{
            v[j] = vrb[i].v;
            j++;
        }
        i++;
        V++;
    }
    free(v);
    free(lastP);

    strncat(buffer, "\n\1Verbos com paradigmas deduzidos\5\n\n", 1511999);

    if(sorted == 0){
        qsort(V, (nv - i), sizeof(Verbo), compareVerbs);
        sorted = 1;
    }

    while(i < nv){
        if(vrb[i].p){
            snprintf(str, 127, "\n\2ERRO no Banco de Verbos: [%s %s]\5\n\n", vrb[i].v, vrb[i].p->paradigma);
        } else{
            P = deduzirParadigma(vrb[i].v);
            if(P == NULL)
                snprintf(str, 127, "\2ERRO tentando deduzir paradigma do verbo “%s”.\5\n", vrb[i].v);
            else
                snprintf(str, 127, "%s (%s)\n", vrb[i].v, P->paradigma);
        }
        strncat(buffer, str, 1511999);
        i++;
    }
}

void listPrdgms(char *buffer)
{
    char str[128];
    int i;

    strncat(buffer, "\n\1Verbos utilizados como paradigmas\5\n\n", 1511999);

    char **p = (char**)malloc(np * sizeof(char*));
    for(i = 0; i < np; i++)
        p[i] = prdgm[i]->paradigma;
    qsort(p, np, sizeof(char*), compareStr);

    i = 0;
    while(i < np){
        snprintf(str, 127, "%s\n", p[i]);
        strncat(buffer, str, 1511999);
        i++;
    }
    free(p);
}

