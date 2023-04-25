#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* Retorna um ponteiro para uma struct chaveLista contendo a chave passada.*/
struct chaveLista *criaChaveLista(wchar_t chave)
{
    struct chaveLista *aux = malloc(sizeof(struct chaveLista));
    if (aux != NULL) {
        aux->tamTotal = TAM_LISTA;
        aux->tam = 0;
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
int buscaBinaria(int x, int lista[], int a, int b)
{
    if (a > b)
        return b + 1;
    int meio = (a + b) / 2;
    if (lista[meio] > x)
        return buscaBinaria(x, lista, a, meio - 1);
    if (lista[meio] < x)
        return buscaBinaria(x, lista, meio + 1, b);

    return meio;
}

/* Retorna 1 se o elemento existir na lista e 0 caso contrario.*/
int buscaElemento(struct chaveLista *cl, int valor)
{
    if (cl->tam == 0)
        return 0;
    int status = buscaBinaria(valor, cl->lista, 0, cl->tam-1);

    return status != cl->tam;
}

/* Coloca o elemento na posicao correta.*/
void ordenaUltimoItem(struct chaveLista *cl)
{
    int tam = cl->tam;
    int *lista = cl->lista;
    int p = buscaBinaria(lista[tam-1], lista, 0, tam-1);
    for (int i = tam-1; i > p; i--)
        troca(lista + i, lista + i - 1);
}

/* Aumenta o tamanho da lista somando TAM_LISTA com o valor atual total.*/
int aumentaTamLista(struct chaveLista *cl)
{
    cl->tamTotal += TAM_LISTA;
    cl->lista = realloc(cl->lista, sizeof(int) * cl->tamTotal);
    if (cl->lista != NULL)
        return 0;

    return 1;
}

/* Adiciona um item na lista de forma ordenada crescente.*/
int addItemLista(struct chaveLista *cl, int valor)
{
    int status;
    if (cl->tam == cl->tamTotal) {
        status = aumentaTamLista(cl);
        if (status == 1)
            return 1;
    }

    cl->lista[cl->tam] = valor;
    cl->tam++;
    ordenaUltimoItem(cl);

    return 0;
}

/* Imprime a lista.*/
void imprimeLista(struct chaveLista *cl)
{
    for (int i = 0; i < cl->tam; i++)
        printf("%d ", cl->lista[i]);

    printf("\n");
}
