#include <stdio.h>
#include <wchar.h>
#define TAM_CIFRAS 10

struct cifrasBeale {
    int tam;
    int tamTotal;
    struct chaveLista **cifras;
};

/* Cria o sistema de cifras e retorna ponteiro para struct cifrasBeale.*/
struct cifrasBeale *criaCifras();

/* Coloca a primeira letra da proxima palavra no texto em @*letra, retorna
 * 1 caso tenha sucesso e 0 caso contrario.*/
int letraProxPalavra(FILE *texto, wchar_t *letra);

/* Aumenta a quantidade de cifras.
 * Retorn 0 se tudo deu certo e 1 caso contrario.*/
int aumentaSistemaCifras(struct cifrasBeale *cb);

/* Troca os valores de dois enderecos.*/
void trocaCifras(struct chaveLista **a, struct chaveLista **b);

/* Retorna a posição de inserção de um elemento @x
 * num vetor de inicio @a e fim @b */
int buscaBinariaCifra(wchar_t x, struct chaveLista **listas, int a, int b, int *sts);

/* Retorna 1 se o elemento existir na lista e 0 caso contrario.*/
int letraExisteCifra(struct cifrasBeale *cb, wchar_t letra);

/* Coloca o ultimo elemento do sistema de cifras na posicao correta.*/
void ordenaUltimoItemCifra(struct cifrasBeale *cb);

/* Adiciona uma letra para o sistema de cifras. A adicao pode ser
 * so sobre uma cifra ja existente ou sobre a criacao de uma nova cifra.
 * Retorna 0 caso tudo de certo e 1 caso contrario.*/
int adicionaLetra(struct cifrasBeale *cb, wchar_t letra, int posi);

/* Monta o sistema de cifras a partir de um texto no stream @texto.
 * Retorna um ponteiro para struct cifrasBeale.*/
struct cifrasBeale *montaChavesTxt(FILE *texto);

/* Cria a linha da cifra com seus respectivos codigos de acordo
 * com o stream. Retorna 0 se deu tudo certo e 1 caso contrario.*/
int montaLinhaCifra(FILE *arqCifras, struct cifrasBeale *cb, wchar_t letra);

/* Le um arquivo de cifras e o transcreve para uma struct do 
 * tipo cifrasBeale, a qual tem seu ponteiro retornado.*/
struct cifrasBeale *leArqCifras(FILE *arqCifras);

/* Imprime as cifras no stdout.*/
void imprimeTodasCifras(struct cifrasBeale *cb);

/* Desaloca toda memoria de uma struct cifrasBeale.*/;
struct cifrasBeale **destroiCifras(struct cifrasBeale *cb);

/* Retorna a chave da cifra passada.*/
wchar_t chaveCifra(struct chaveLista *cl);

/* Passa o proximo elemento da cifra em @valor.
 * Retorna 1 se deu certo e 0 caso contrario.*/
int iteraListaCifra(struct chaveLista *cl, int *valor);
