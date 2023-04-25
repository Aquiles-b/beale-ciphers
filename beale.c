#include <stdio.h>
#include "lista_lib.h"

int main()
{
    struct chaveLista *cl = criaChaveLista('a');
    int valor;
    scanf("%d", &valor);
    while (valor != 0) {
        addItemLista(cl, valor);
        scanf("%d", &valor);
    }

    imprimeLista(cl);

    cl = destroiChaveLista(cl);

    return 0;
}
