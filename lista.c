#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#define TAM_LISTA 64

struct chaveLista {
    wchar_t chave;
    unsigned int *lista;
    unsigned int tamLista;
};

struct chaveLista *criaChaveLista(wchar_t chave)
{
    struct chaveLista *aux = malloc(sizeof(struct chaveLista));
    if (aux != NULL) {
        aux->tamLista = TAM_LISTA;
        aux->lista = malloc(sizeof(unsigned int) * TAM_LISTA);
        aux->chave = chave;
    } else {
    fprintf(stderr, "Memoria insuficiente pra alocar nova chaveLista.");
    }

    return aux;
}

struct chaveLista *destroiChaveLista(struct chaveLista *pt)
{
    free(pt->lista);
    free(pt);

    return NULL;
}

int main()
{

    return 0;
}
