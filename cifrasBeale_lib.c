#include "cifrasBeale_lib.h"
#include "lista_lib.h"
#include <stdio.h>
#include <stdlib.h>

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
