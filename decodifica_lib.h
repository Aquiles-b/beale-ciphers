#ifndef CIFRASBEALE_H
#define CIFRASBEALE_H
#include "cifrasBeale_lib.h"
#include <wchar.h>
#endif 

/* Decodifica para @txtOut o texto em @txtCod com base no sistema passado em
 * @cb */
void decodifica(struct cifrasBeale *cb, FILE *txtCod, FILE *txtOut);

/* Decodifica para @txtOut o texto em @txtCod com base em @textoBase.*/
int decodComTxt(FILE *txtCod, FILE *txtOut, FILE *textoBase);

/* Decodifica para o stream @txtOut o texto em @txtCod com o sistema de cifras 
 * em @arqCifras.*/
int decodComCifras(FILE *txtCod, FILE *txtOut, FILE *arqCifras);
