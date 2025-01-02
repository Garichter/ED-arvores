#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <ctype.h>

pNodoA* rotacao_direita(pNodoA* p)
{
    pNodoA *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
}

pNodoA* rotacao_esquerda(pNodoA *p)
{
    pNodoA *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}

pNodoA* rotacao_dupla_direita (pNodoA* p)
{
    pNodoA *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1) p->FB = -1;
    else p->FB = 0;
    if (v->FB == -1) u->FB = 1;
    else u->FB = 0;
    p = v;
    return p;
}

pNodoA* rotacao_dupla_esquerda (pNodoA *p)
{
    pNodoA *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1) p->FB = 1;
    else p->FB = 0;
    if (y->FB == 1) z->FB = -1;
    else z->FB = 0;
    p = y;
    return p;
}

//recebe a raiz, a char a ser colocada na árvore e sua substituta
pNodoA* InsereAVL (pNodoA *a, TipoInfo x, TipoInfo y, int *ok)
{
    if (a == NULL) //se a raiz for nula, cria a árvore
    {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        a->info = strdup(x);
        a->sub = strdup(y);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    //procura na árvore o nodo em que a char tem que ser inserida
    else if (strcmp(x, a->info)<0) //caso menor
    {
        a->esq = InsereAVL(a->esq,x,y,ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                a=Caso1(a,ok);
                break;
            }
        }
    }
    else //caso direita
    {
        a->dir = InsereAVL(a->dir,x,y,ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case 1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                a = Caso2(a,ok);
                break;
            }
        }
    }
    return a;
}

pNodoA* Caso1 (pNodoA *a, int *ok)
{
    pNodoA *z;
    z = a->esq;
    if (z->FB == 1){
        a = rotacao_direita(a);
        rotacao++;
    }
    else{
        a = rotacao_dupla_direita(a);
        rotacao++;
    }
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA* Caso2 (pNodoA *a, int *ok)
{
    pNodoA *z;
    z = a->dir;
    if (z->FB == -1){
        a = rotacao_esquerda(a);
        rotacao++;
    }
    else{
        a = rotacao_dupla_esquerda(a);
        rotacao++;
    }
    a->FB = 0;
    *ok = 0;
    return a;
}

int altura(pNodoA *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }
    int alturaEsq = altura(raiz->esq);
    int alturaDir = altura(raiz->dir);

    if(alturaDir>alturaEsq) return alturaDir + 1;
    else return alturaEsq + 1;
}

TipoInfo encontraPalavra(TipoInfo str1, pNodoA *raiz)
{
    while (raiz != NULL)
    {
        int var = strcmp(str1,raiz->info);
        if (var == 0)
            return raiz->sub;
        else if (var> 0)
            raiz = raiz->dir;
        else
            raiz = raiz->esq;
    }
    return str1;
}


pNodoA* consulta(pNodoA *a, char *chave)
{
    while (a!=NULL)
    {
        comp++;
        if (!strcmp(a->info,chave) )
        {
            comp++;
            return a;
        }
        else
        {
            comp++;
            if (strcmp(a->info,chave)>0)
                a = a->esq;
            else
                a = a->dir;
        }
    }
    return NULL;
}

void escreveArquivo(pNodoA* raiz, FILE *arqlei, FILE* arqesc)
{
    char str1[20];
    pNodoA *temp;
    int i =0;
    char c;
    while ((c = fgetc(arqlei)) != EOF) //lê caractere por caractere
    {
        if (c == ' ' || c == '\n' || c == '.' || c == ',' || c == ':' || c == '"' || c == ';') //se caractere for terminador
        {
            if (i > 0) // para o caso de terminadores seguidos
            {
                str1[i] = '\0'; //finaliza string
                temp = consulta(raiz, str1); //encontra o nodo da char, se existir
                if(temp == NULL)
                    fprintf(arqesc, "%s", str1); //se não encontrou, printa a mesma que anterior
                else
                    fprintf(arqesc,"%s", temp->sub); //printa o substituto, se econtrar
                i = 0; //reinicia a string
            }
            fputc(c, arqesc); //printa o terminador
        }
        else str1[i++] = tolower(c); //adiciona na string o minúsculo, se estiver
    }
    if (i > 0) //se no final do arquivo não houver terminador
    {
        str1[i] = '\0';
        temp = consulta(raiz, str1);
        if (temp == NULL)
            fprintf(arqesc, "%s", str1);
        else
            fprintf(arqesc, "%s", temp->sub);
    }
}
