#include "lista_lib.h"
#include "files_lib.h"
#include "cifrasBeale_lib.h"
#include <stdio.h>
#include <wchar.h>

int decodComTxt(FILE *txtCod, FILE *txtOut, FILE *textoBase)
{
    int num, i, status;
    wchar_t chave;
    struct cifrasBeale *cb = montaChavesTxt(textoBase);
    if (cb == NULL)
        return 1;

    i = 0;
    fscanf(txtCod, "%d", &num);
    printf ("%d\n", num);
    while (i < cb->tam) {
        if (buscaElemento(cb->cifras[i], num))
            fwrite(&cb->cifras[i]->chave, sizeof(wchar_t), 1, txtOut);
        i++;
    }

    destroiCifras(cb);

    return 0;
}

int main()
{
    FILE *txtCod = fopen("txtCod.txt", "r");
    FILE *txtOut = fopen("saida.txt", "w");
    FILE *textoBase = fopen("livroTeste.txt", "r");

    decodComTxt(txtCod, txtOut, textoBase);

    /* fclose(txtCod); */
    fclose(txtOut);
    /* fclose(textoBase); */

    return 0;
}
