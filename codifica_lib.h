#ifndef CIFRASBEALE_H
#define CIFRASBEALE_H
#include "cifrasBeale_lib.h"
#include <wchar.h>
#endif 
/* Codifica para @txtOut o texto em @txtCod com base no sistema passado em
 * @cb */
void codifica(struct cifrasBeale *cb, FILE *txtCod, FILE *txtOut);

/* Codifica para @txtOut o texto em @txtCod com base em @textoBase.
 * Salva o arquivo de cifras gerado caso @arqOutCifras nao seja NULL.*/
int codificaComTxt(FILE *txtCod, FILE *txtOut, FILE *textoBase, FILE *arqOutCifras);

/* Codifica para o stream @txtOut o texto em @txtCod com o sistema de cifras 
 * em @arqCifras.*/
int codificaComCifras(FILE *txtCod, FILE *txtOut, FILE *arqCifras);
