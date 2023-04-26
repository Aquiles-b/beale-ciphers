#include "cifrasBeale_lib.h"
#include <locale.h>
#include "lista_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
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

struct cifrasBeale *montaChavesTxt(FILE *texto)
{
    struct cifrasBeale *cifras = criaCifras();
    if (cifras == NULL)
        return NULL;
    
    wchar_t letra;

    while(letraProxPalavra(texto, &letra))

    return cifras;
}

int main()
{
    setlocale(LC_ALL, "");
    FILE *texto = fopen("livroTeste.txt", "r");
    struct cifrasBeale *cifras = montaChavesTxt(texto);

    return 0;
}
