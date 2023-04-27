#include "cifrasBeale_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <wchar.h>

/* Codifica para @txtOut o texto em @txtCod com base no sistema passado em
 * @cb */
void codifica(struct cifrasBeale *cb, FILE *txtCod, FILE *txtOut);

/* Codifica para @txtOut o texto em @txtCod com base em @textoBase.
 * Salva o arquivo de cifras gerado caso @arqOutCifras nao seja NULL.*/
int codificaComTxt(FILE *txtCod, FILE *txtOut, FILE *textoBase, FILE *arqOutCifras)
{
    wchar_t letra;
    struct cifrasBeale *cb = montaChavesTxt(textoBase);
    if (cb == NULL)
        return 1;

    imprimeTodasCifras(cb);

    letra = getwc(txtCod);
    while(!feof(txtCod)){
        if (letra != L' ' && letra != L'\n')
            printf ("%d %lc\n", aleatNumCifra(cb, letra), letra);
    letra = getwc(txtCod);
    }

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

    codificaComTxt(txtCod, txtOut, txtBase, NULL);

    fclose(txtCod);
    fclose(txtOut);
    fclose(txtBase);

    return 0;
}
