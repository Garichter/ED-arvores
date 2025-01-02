typedef char* TipoInfo;


struct TNodoA
{
    TipoInfo info;
    TipoInfo sub;
    int FB;
    struct TNodoA *esq;
    struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;

extern int comp;

extern int rotacao;

pNodoA* rotacao_direita(pNodoA* p);

pNodoA* rotacao_esquerda(pNodoA *p);

pNodoA* rotacao_dupla_direita (pNodoA* p);

pNodoA* rotacao_dupla_esquerda (pNodoA *p);

pNodoA* InsereAVL (pNodoA *a, TipoInfo x, TipoInfo y, int *ok);

pNodoA* Caso1 (pNodoA *a, int *ok);

pNodoA* Caso2 (pNodoA *a, int *ok);

int altura(pNodoA *raiz);

TipoInfo encontraPalavra(TipoInfo str1, pNodoA *raiz);

pNodoA* consulta(pNodoA *a, char *chave);

void escreveArquivo(pNodoA* raiz, FILE *arqlei, FILE* arqesc);
