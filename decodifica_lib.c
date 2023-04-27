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

/* Decodifica para @txtOut o texto em @txtCod com base no sistema passado em
 * @cb */
void decodifica(struct cifrasBeale *cb, FILE *txtCod, FILE *txtOut)
{
    wchar_t chave;
    int num;

    while (fscanf(txtCod, "%d", &num) != -1){
        if (num == -1) {
            fputc(L' ', txtOut);
        } else {
            chave = buscaCifra(cb, num);
            fputc(chave, txtOut);
        }
    }
    fputc(L'\n', txtOut);
}

void escreveCifras(struct cifrasBeale *cb, FILE *arq)
{
    int i = 0, valor;
    while (i < cb->tam) {
        fprintf(arq ,"%lc: ", chaveCifra(cb->cifras[i]));
        while (iteraListaCifra(cb->cifras[i], &valor))
            fprintf(arq, "%d ", valor);
        fseek(arq, -sizeof(char), SEEK_CUR);
        fprintf(arq, "\n");
        i++;
    }

}

/* Decodifica para @txtOut o texto em @txtCod com base em @textoBase.
 * Salva o arquivo de cifras gerado caso @arqOutCifras nao seja NULL.*/
int decodComTxt(FILE *txtCod, FILE *txtOut, FILE *textoBase, FILE *arqOutCifras)
{
    struct cifrasBeale *cb = montaChavesTxt(textoBase);
    if (cb == NULL)
        return 1;

    decodifica(cb, txtCod, txtOut);
    if (arqOutCifras != NULL)
        escreveCifras(cb, arqOutCifras);

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

int main()
{
    setlocale(LC_ALL, "");
    FILE *txtCod = fopen("txtCod.txt", "r");
    FILE *txtOut = fopen("saida.txt", "w");
    FILE *textoBase = fopen("livroTeste.txt", "r");
    FILE *arqCifras = fopen("arqCifras.txt", "w");

    decodComTxt(txtCod, txtOut, textoBase, arqCifras);

    fclose(txtCod);
    fclose(txtOut);
    fclose(textoBase);

    return 0;
}
