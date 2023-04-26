#include "cifrasBeale_lib.h"
#include <locale.h>
#include "lista_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

/* Cria o sistema de cifras e retorna ponteiro para struct cifrasBeale.*/
struct cifrasBeale *criaCifras()
{
    struct cifrasBeale *pt = malloc(sizeof(struct cifrasBeale));
    if (pt == NULL) {
        printf ("Nao foi possivel criar sistema de cifras.\n");
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

/* Aumenta a quantidade de cifras.*/
int aumentaSistemaCifras(struct cifrasBeale *cb)
{
    cb->tamTotal += TAM_CIFRAS;
    cb->cifras = realloc(cb->cifras, sizeof(struct chaveLista) * cb->tamTotal);
    if (cb->cifras != NULL)
        return 1;

    return 0;
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

int adicionaLetra(struct cifrasBeale *cb, wchar_t letra, int posi)
{
    int sts, p;
    if (cb->tam == cb->tamTotal){
        if(!aumentaSistemaCifras(cb))
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

struct cifrasBeale *montaChavesTxt(FILE *texto)
{
    wchar_t letra;
    int i;

    struct cifrasBeale *cifras = criaCifras();
    if (cifras == NULL)
        return NULL;

    i = 0;
    while(letraProxPalavra(texto, &letra)){
        adicionaLetra(cifras, letra, i);
        i++;
    }

    fclose(texto);

    return cifras;
}

void imprimeCifras(struct cifrasBeale *cb)
{
    for (int i = 0; i < cb->tam; i++) {
        printf ("%lc: ", cb->cifras[i]->chave);
        imprimeLista(cb->cifras[i]);
    }
}

int main()
{
    setlocale(LC_ALL, "");
    FILE *texto = fopen("livroTeste.txt", "r");
    struct cifrasBeale *cifras = montaChavesTxt(texto);
    imprimeCifras(cifras);

    return 0;
}
