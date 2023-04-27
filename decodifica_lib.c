#include "lista_lib.h"
#include "files_lib.h"
#include "cifrasBeale_lib.h"
#include <stdio.h>
#include <locale.h>
#include <wchar.h>

/* Retorna a letra correspondente ao numero como base no sistema de cifras.
 * Caso nao exista retorna o caractere '?'.*/
wchar_t buscaCifra(struct cifrasBeale *cb, int num)
{
    int i = 0;
    while (i < cb->tam) {
        if (buscaElemento(cb->cifras[i], num))
            return cb->cifras[i]->chave;
        i++;
    }

    return L'?';
}

/* Decodifica para @txtOut o texto em @txtCod com base em @textoBase.*/
int decodComTxt(FILE *txtCod, FILE *txtOut, FILE *textoBase)
{
    int num, status;
    wchar_t chave;
    struct cifrasBeale *cb = montaChavesTxt(textoBase);
    if (cb == NULL)
        return 1;

    while (fscanf(txtCod, "%d", &num) != -1){
        if (num == -1) {
            fputc(L' ', txtOut);
        } else {
        chave = buscaCifra(cb, num);
        fputc(chave, txtOut);
        }
    }
    fputc(L'\n', txtOut);
    destroiCifras(cb);

    return 0;
}

int main()
{
    setlocale(LC_ALL, "");
    FILE *txtCod = fopen("txtCod.txt", "r");
    FILE *txtOut = fopen("saida.txt", "w");
    FILE *textoBase = fopen("livroTeste.txt", "r");

    decodComTxt(txtCod, txtOut, textoBase);

    /* fclose(txtCod); */
    fclose(txtOut);
    /* fclose(textoBase); */

    return 0;
}
