#include "lista_lib.h"
#include "files_lib.h"
#include "cifrasBeale_lib.h"
#include <wchar.h>

/* Retorna a letra correspondente ao numero como base no sistema de cifras.
 * Caso nao exista retorna o caractere '?'.*/
wchar_t buscaCifra(struct cifrasBeale *cb, int num);

/* Decodifica para @txtOut o texto em @txtCod com base no sistema passado em
 * @cb */
void decodifica(struct cifrasBeale *cb, FILE *txtCod, FILE *txtOut);

/* Escreve as cifras no arquivo @arq.*/
void escreveCifras(struct cifrasBeale *cb, FILE *arq);

/* Decodifica para @txtOut o texto em @txtCod com base em @textoBase.
 * Salva o arquivo de cifras gerado caso @arqOutCifras nao seja NULL.*/
int decodComTxt(FILE *txtCod, FILE *txtOut, FILE *textoBase, FILE *arqOutCifras);

/* Decodifica para o stream @txtOut o texto em @txtCod com o sistema de cifras 
 * em @arqCifras.*/
int decodComCifras(FILE *txtCod, FILE *txtOut, FILE *arqCifras);
