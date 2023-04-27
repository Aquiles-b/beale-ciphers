#include "cifrasBeale_lib.h"
#include "lista_lib.h"
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

/* Cria o sistema de cifras e retorna ponteiro para struct cifrasBeale.*/
struct cifrasBeale *criaCifras()
{
    struct cifrasBeale *pt = malloc(sizeof(struct cifrasBeale));
    if (pt == NULL) {
        printf ("Erro: Nao foi possivel criar sistema de cifras.\n");
    }
    else {
        pt->tam = 0;
        pt->tamTotal = TAM_CIFRAS;
        pt->cifras = malloc(sizeof(struct chaveLista*) * TAM_CIFRAS);
    }

    return pt;
}

/* Coloca a primeira letra da proxima palavra no texto em @*letra, retorna
 * 1 caso tenha sucesso e 0 caso contrario.*/
int letraProxPalavra(FILE *texto, wchar_t *letra)
{
    wchar_t aux[64];
    int status = fscanf(texto, "%ls", aux);
    if (status == -1)
        return 0;
    *letra = aux[0];

    return 1;
}

/* Aumenta a quantidade de cifras.
 * Retorn 0 se tudo deu certo e 1 caso contrario.*/
int aumentaSistemaCifras(struct cifrasBeale *cb)
{
    cb->tamTotal += TAM_CIFRAS;
    cb->cifras = realloc(cb->cifras, sizeof(struct chaveLista) * cb->tamTotal);
    if (cb->cifras != NULL){
        return 0;
    }
    printf ("Erro: Impossivel aumentar tamanho do sistema de cifras.\n");

    return 1;
}

/* Troca os valores de dois enderecos.*/
void trocaCifras(struct chaveLista **a, struct chaveLista **b)
{
    struct chaveLista *aux = *a;
    *a = *b;
    *b = aux;
}

/* Retorna a posição de inserção de um elemento @x
 * num vetor de inicio @a e fim @b */
int buscaBinariaCifra(wchar_t x, struct chaveLista **listas, int a, int b, int *sts)
{
    if (a > b){
        *sts = 0;
        return b + 1;
    }
    int meio = (a + b) / 2;
    if (listas[meio]->chave == x)
        return meio;
    if (listas[meio]->chave < x)
        return buscaBinariaCifra(x, listas, meio + 1, b, sts);

    return buscaBinariaCifra(x, listas, a, meio - 1, sts);

}

/* Retorna 1 se o elemento existir na lista e 0 caso contrario.*/
int letraExisteCifra(struct cifrasBeale *cb, wchar_t letra)
{
    if (cb->tam == 0)
        return 0;
    int sts = 1;
    buscaBinariaCifra(letra, cb->cifras, 0, cb->tam-1, &sts);

    return sts;
}

/* Coloca o ultimo elemento do sistema de cifras na posicao correta.*/
void ordenaUltimoItemCifra(struct cifrasBeale *cb)
{
    int sts = 0;
    int tam = cb->tam;
    struct chaveLista **listas = cb->cifras;
    int p = buscaBinariaCifra(listas[tam-1]->chave, listas, 0, tam-1, &sts);
    for (int i = tam-1; i > p; i--)
        trocaCifras(&listas[i], &listas[i - 1]);
}

/* Adiciona uma letra para o sistema de cifras. A adicao pode ser
 * so sobre uma cifra ja existente ou sobre a criacao de uma nova cifra.
 * Retorna 0 caso tudo de certo e 1 caso contrario.*/
int adicionaLetra(struct cifrasBeale *cb, wchar_t letra, int posi)
{
    int sts, p;
    if (cb->tam == cb->tamTotal){
        if(aumentaSistemaCifras(cb))
            return 1;
    }
    if (!letraExisteCifra(cb, letra)){
        cb->cifras[cb->tam] = criaChaveLista(letra);
        addItemLista(cb->cifras[cb->tam], posi);
        cb->tam++;
        ordenaUltimoItemCifra(cb);
    } else {
        p = buscaBinariaCifra(letra, cb->cifras, 0, cb->tam-1, &sts);
        addItemLista(cb->cifras[p], posi);
    }

    return 0;
}

/* Monta o sistema de cifras a partir de um texto no strem @texto.
 * Retorna um ponteiro para struct cifrasBeale.*/
struct cifrasBeale *montaChavesTxt(FILE *texto)
{
    wchar_t letra;
    int i, status = 0;

    struct cifrasBeale *cifras = criaCifras();
    if (cifras == NULL)
        return NULL;

    rewind(texto);
    i = 0;
    while(letraProxPalavra(texto, &letra) && status == 0){
        letra = towlower(letra);
        status = adicionaLetra(cifras, letra, i);
        i++;
    }
    if (status != 0){
        destroiCifras(cifras);
        return NULL;
    }

    return cifras;
}

/* Cria a linha da cifra com seus respectivos codigos de acordo
 * com o stream. Retorna 0 se deu tudo certo e 1 caso contrario.*/
int montaLinhaCifra(FILE *arqCifras, struct cifrasBeale *cb, wchar_t letra)
{
    int tam, posi, status = 0;
    tam = cb->tam;
    if (tam == cb->tamTotal){
        if(aumentaSistemaCifras(cb))
            return 1;
    }
    cb->cifras[tam] = criaChaveLista(letra);
    while(fscanf(arqCifras, "%d", &posi) == 1 && status == 0)
        status = addItemLista(cb->cifras[tam], posi);

    if (status != 0)
        return 1;

    cb->tam++;

    return 0;
}

/* Le um arquivo de cifras e o transcreve para uma struct do 
 * tipo cifrasBeale, a qual tem seu ponteiro retornado.*/
struct cifrasBeale *leArqCifras(FILE *arqCifras)
{
    rewind(arqCifras);
    wchar_t chave;
    int status = 0;
    struct cifrasBeale *cb = criaCifras();
    if (cb == NULL)
        return cb;

    fscanf(arqCifras, "%1lc", &chave);
    getc(arqCifras);
    while (!feof(arqCifras) && status == 0){
        status = montaLinhaCifra(arqCifras, cb, chave);
        fscanf(arqCifras, "%1lc", &chave);
        getc(arqCifras);
    }
    if (status != 0){
        destroiCifras(cb);
        return NULL;
    }

    return cb;
}

/* Imprime as cifras no stdout.*/
void imprimeTodasCifras(struct cifrasBeale *cb)
{
    for (int i = 0; i < cb->tam; i++) {
        printf ("%lc: ", cb->cifras[i]->chave);
        imprimeLista(cb->cifras[i]);
    }
}

/* Desaloca toda memoria de uma struct cifrasBeale.*/
struct cifrasBeale **destroiCifras(struct cifrasBeale *cb)
{
    for (int i = 0; i < cb->tam; i++)
        destroiChaveLista(cb->cifras[i]);
    free(cb->cifras);
    free(cb);

    return NULL;
}

/* Retorna a chave da cifra passada.*/
wchar_t chaveCifra(struct chaveLista *cl)
{
    return cl->chave;
}

/* Passa o proximo elemento da cifra em @valor.
 * Retorna 1 se deu certo e 0 caso contrario.*/
int iteraListaCifra(struct chaveLista *cl, int *valor)
{
    if (iteraLista(cl, valor)) {
        return 1;
    }

    return 0;
}
