#include <wchar.h>
#define TAM_LISTA 16

struct chaveLista {
    wchar_t chave;
    int *lista;
    int tam;
    int tamTotal;
    int posix;
};

/* Retorna um ponteiro para uma struct chaveLista contendo a chave passada.*/
struct chaveLista *criaChaveLista(wchar_t chave);

/* Desaloca toda memoria de uma struct chaveLista e retorna NULL*/
struct chaveLista *destroiChaveLista(struct chaveLista *pt);

/* Retorna 1 se o elemento existir na lista e 0 caso contrario.*/
int buscaElemento(struct chaveLista *cl, int valor);

/* Adiciona um item na lista de forma ordenada crescente.*/
int addItemLista(struct chaveLista *cl, int valor);

/* Reseta o iterador.*/
void rstIteradorLista(struct chaveLista *cl);

/* Passa o valor do proximo elemento da lista em @valorAtual.
 * Retorna 1 se deu certo e 0 caso contrario.*/
int iteraLista(struct chaveLista *cl, int *valorAtual);

/* Imprime a lista.*/
void imprimeLista(struct chaveLista *cl);
