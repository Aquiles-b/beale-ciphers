#include <stdio.h>
#include "lista_lib.h"
#include <wchar.h>
#define TAM_CIFRAS 10

struct cifrasBeale {
    int tam;
    int tamTotal;
    struct chaveLista **cifras;
};

/* Cria o sistema de cifras e retorna ponteiro para struct cifrasBeale.*/
struct cifrasBeale *criaCifras();

/* Adiciona uma letra para o sistema de cifras. A adicao pode ser
 * so sobre uma cifra ja existente ou sobre a criacao de uma nova cifra.
 * Retorna 0 caso tudo de certo e 1 caso contrario.*/
int adicionaLetra(struct cifrasBeale *cb, wchar_t letra, int posi);

/* Retorna a letra correspondente ao numero como base no sistema de cifras.
 * Caso nao exista retorna o caractere '?'.*/
wchar_t buscaCifra(struct cifrasBeale *cb, int num);

/* Monta o sistema de cifras a partir de um texto no stream @texto.
 * Retorna um ponteiro para struct cifrasBeale.*/
struct cifrasBeale *montaChavesTxt(FILE *texto);

/* Le um arquivo de cifras e o transcreve para uma struct do 
 * tipo cifrasBeale, a qual tem seu ponteiro retornado.*/
struct cifrasBeale *leArqCifras(FILE *arqCifras);

/* Imprime as cifras no stdout.*/
void imprimeTodasCifras(struct cifrasBeale *cb);

/* Desaloca toda memoria de uma struct cifrasBeale.*/;
struct cifrasBeale **destroiCifras(struct cifrasBeale *cb);

/* Retorna a chave da cifra passada.*/
wchar_t chaveCifra(struct chaveLista *cl);

/* Retorna um numero aleatorio da lista da cifra com a chave igual a @letra.*/
int aleatNumCifra(struct cifrasBeale *cb, wchar_t letra);

/* Passa o proximo elemento da cifra em @valor.
 * Retorna 1 se deu certo e 0 caso contrario.*/
int iteraListaCifra(struct chaveLista *cl, int *valor);

/* Escreve as cifras no arquivo @arq.*/
void escreveCifras(struct cifrasBeale *cb, FILE *arq);
