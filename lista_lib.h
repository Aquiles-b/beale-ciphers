#include <wchar.h>
#define TAM_LISTA 16

struct chaveLista {
    wchar_t chave;
    int *lista;
    int tam;
    int tamTotal;
};

/* Retorna um ponteiro para uma struct chaveLista contendo a chave passada.*/
struct chaveLista *criaChaveLista(wchar_t chave);

/* Desaloca toda memoria de uma struct chaveLista e retorna NULL*/
struct chaveLista *destroiChaveLista(struct chaveLista *pt);

/* Troca os valores de dois enderecos.*/
void troca(int *a, int *b);

/* Retorna a posição de inserção de um elemento @x
 * num vetor de inicio @a e fim @b */
int buscaBinaria(int x, int lista[], int a, int b);

/* Retorna 1 se o elemento existir na lista e 0 caso contrario.*/
int buscaElemento(struct chaveLista *cl, int valor);

/* Coloca o elemento na posicao correta.*/
void ordenaUltimoItem(struct chaveLista *cl);

/* Aumenta o tamanho da lista somando TAM_LISTA com o valor atual total.*/
int aumentaTamLista(struct chaveLista *cl);

/* Adiciona um item na lista de forma ordenada crescente.*/
int addItemLista(struct chaveLista *cl, int valor);

/* Imprime a lista.*/
void imprimeLista(struct chaveLista *cl);
