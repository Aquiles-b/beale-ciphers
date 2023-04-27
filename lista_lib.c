#include <stdio.h>
#include <stdlib.h>
#include "lista_lib.h"

/* Retorna um ponteiro para uma struct chaveLista contendo a chave passada.*/
struct chaveLista *criaChaveLista(wchar_t chave)
{
    struct chaveLista *aux = malloc(sizeof(struct chaveLista));
    if (aux != NULL) {
        aux->tamTotal = TAM_LISTA;
        aux->tam = 0;
        aux->posix = 0;
        aux->lista = malloc(sizeof(int) * TAM_LISTA);
        aux->chave = chave;
    } else {
        fprintf(stderr, "Memoria insuficiente pra alocar nova chaveLista.");
    }

    return aux;
}

/* Desaloca toda memoria de uma struct chaveLista e retorna NULL*/
struct chaveLista *destroiChaveLista(struct chaveLista *pt)
{
    free(pt->lista);
    free(pt);

    return NULL;
}

/* Troca os valores de dois enderecos.*/
void troca(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

/* Retorna a posição de inserção de um elemento @x
 * num vetor de inicio @a e fim @b */
int buscaBinariaLista(int x, int lista[], int a, int b, int *sts)
{
    if (a > b){
        *sts = 0;
        return b + 1;
    }
    int meio = (a + b) / 2;
    if (lista[meio] < x)
        return buscaBinariaLista(x, lista, a, meio - 1, sts);
    if (lista[meio] > x)
        return buscaBinariaLista(x, lista, meio + 1, b, sts);

    return meio;
}

/* Retorna 1 se o elemento existir na lista e 0 caso contrario.*/
int buscaElemento(struct chaveLista *cl, int valor)
{
    int status = 1;
    if (cl->tam == 0)
        return 0;
    buscaBinariaLista(valor, cl->lista, 0, cl->tam-1, &status);

    return status;
}

/* Coloca o elemento na posicao correta.*/
void ordenaUltimoItem(struct chaveLista *cl)
{
    int sts;
    int tam = cl->tam;
    int *lista = cl->lista;
    int p = buscaBinariaLista(lista[tam-1], lista, 0, tam-1, &sts);
    for (int i = tam-1; i > p; i--)
        troca(lista + i, lista + i - 1);
}

/* Aumenta o tamanho da lista somando TAM_LISTA com o valor atual total.
 * Retorna 0 se der certo e 1 caso contrario.*/
int aumentaTamLista(struct chaveLista *cl)
{
    cl->tamTotal += TAM_LISTA;
    cl->lista = realloc(cl->lista, sizeof(int) * cl->tamTotal);
    if (cl->lista != NULL)
        return 0;

    printf ("Erro: Impossivel aumentar tamanho da lista.\n");

    return 1;
}

/* Adiciona um item na lista de forma ordenada crescente.
* Retorna 0 se der certo e 1 caso contrario.*/
int addItemLista(struct chaveLista *cl, int valor)
{
    if (cl->tam == cl->tamTotal) {
        if(aumentaTamLista(cl))
            return 1;
    }
    cl->lista[cl->tam] = valor;
    cl->tam++;
    ordenaUltimoItem(cl);

    return 0;
}

/* Reseta o iterador.*/
void rstIteradorLista(struct chaveLista *cl)
{
    cl->posix = 0;
}

/* Passa o valor do proximo elemento da lista em @valorAtual.
 * Retorna 1 se deu certo e 0 caso contrario.*/
int iteraLista(struct chaveLista *cl, int *valorAtual)
{
    if (cl->posix == cl->tam)
        return 0;
    *valorAtual = cl->lista[cl->posix];
    cl->posix++;

    return 1;
}

/* Imprime a lista.*/
void imprimeLista(struct chaveLista *cl)
{
    int num;
    rstIteradorLista(cl);
    while (iteraLista(cl, &num))
        printf ("%d ", num);
    rstIteradorLista(cl);

    printf ("\n");
}
