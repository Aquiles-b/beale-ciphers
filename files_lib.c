#include "files_lib.h"
#include <stdlib.h>

/* Retorna ponteiro para o arquivo @arq somente para leitura.*/
FILE *leArquivo(char *arq)
{
    FILE *pt = fopen(arq, "r");
    if (pt == NULL){
        perror("Nao foi possivel ler o arquivo. ");
        printf ("%s\n", arq);
        exit(1);
    }

    return pt;
}
