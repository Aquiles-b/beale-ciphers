#include <stdio.h>
#include "decodifica_lib.h"

/* Decodifica para @txtOut o texto em @txtCod com base no sistema passado em
 * @cb */
void decodifica(struct cifrasBeale *cb, FILE *txtCod, FILE *txtOut)
{
    wchar_t chave;
    int num;

    while (fscanf(txtCod, "%d", &num) != -1){
        if (num == -1) {
            fputc(L' ', txtOut);
        } else if (num == -2){
            fputc(L'\n', txtOut);
        } else if (num == -3){
            fputc(L'?', txtOut);
        } else {
            chave = buscaCifra(cb, num);
            fputc(chave, txtOut);
        }
    }
}

/* Decodifica para @txtOut o texto em @txtCod com base em @textoBase.
 * Salva o arquivo de cifras gerado caso @arqOutCifras nao seja NULL.*/
int decodComTxt(FILE *txtCod, FILE *txtOut, FILE *textoBase)
{
    struct cifrasBeale *cb = montaChavesTxt(textoBase);
    if (cb == NULL)
        return 1;

    decodifica(cb, txtCod, txtOut);
    destroiCifras(cb);

    return 0;
}

/* Decodifica para o stream @txtOut o texto em @txtCod com o sistema de cifras 
 * em @arqCifras.*/
int decodComCifras(FILE *txtCod, FILE *txtOut, FILE *arqCifras)
{
    struct cifrasBeale *cb = leArqCifras(arqCifras);
    if (cb == NULL)
        return 1;

    decodifica(cb, txtCod, txtOut);
    destroiCifras(cb);

    return 0;
}
