#include "cifrasBeale_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <wchar.h>

/* Codifica para @txtOut o texto em @txtCod com base no sistema passado em
 * @cb */
void codifica(struct cifrasBeale *cb, FILE *txtCod, FILE *txtOut)
{
    wchar_t letra;

    letra = getwc(txtCod);
    while(!feof(txtCod)){
        if (letra == L' ')
            fprintf(txtOut, "-1 ");
        else if (letra == L'\n')
            fprintf(txtOut, "-2\n");
        else
            fprintf(txtOut, "%d ", aleatNumCifra(cb, letra));
    letra = getwc(txtCod);
    }
}

/* Codifica para @txtOut o texto em @txtCod com base em @textoBase.
 * Salva o arquivo de cifras gerado caso @arqOutCifras nao seja NULL.*/
int codificaComTxt(FILE *txtCod, FILE *txtOut, FILE *textoBase, FILE *arqOutCifras)
{
    struct cifrasBeale *cb = montaChavesTxt(textoBase);
    if (cb == NULL)
        return 1;

    codifica(cb, txtCod, txtOut);
    if (arqOutCifras != NULL)
        escreveCifras(cb, arqOutCifras);

    return 0;
}

/* Codifica para o stream @txtOut o texto em @txtCod com o sistema de cifras 
 * em @arqCifras.*/
int codificaComCifras(FILE *txtCod, FILE *txtOut, FILE *arqCifras);

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));
    FILE *txtCod = fopen("txtCod.txt", "r");
    FILE *txtOut = fopen("txtOut.txt", "w");
    FILE *txtBase = fopen("livroTeste.txt", "r");
    FILE *cifras = fopen("cifras.txt", "w");

    codificaComTxt(txtCod, txtOut, txtBase, cifras);

    fclose(txtCod);
    fclose(txtOut);
    fclose(txtBase);

    return 0;
}
