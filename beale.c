#include <stdio.h>
#include <getopt.h>
#include <locale.h>
#include <stdlib.h>
#include "decodifica_lib.h"
#include "codifica_lib.h"
#define OP_ENCODE 0
#define OP_DECODE 1

/* Struct para facilitar a manipulacao das entradas do usuario.*/
struct entrada {
    short operacao;
    short input;
    char *entrada;
    short book;
    char *livro;
    short out;
    char *saida;
    short cipher;
    char *cifra;
};

/* Aloca e inicia as variaveis da struct com valores basicos.*/
struct entrada *criaEntradas()
{
    struct entrada *opts = malloc(sizeof(struct entrada));
    if (opts == NULL){
        fprintf(stderr, "Erro ao alocar entradas.");
        return NULL;
    }
    opts->operacao = -1;
    opts->input = 0;
    opts->entrada = NULL;
    opts->book = 0;
    opts->livro = NULL;
    opts->out = 0;
    opts->saida = NULL;
    opts->cipher = 0;
    opts->cifra = NULL;

    return opts;
}

/* Passa os dados da entrada para uma struct entrada e retorna um ponteiro
 * para ela.*/
struct entrada *trataOpts(int argc, char **argv)
{
    struct entrada *opts = criaEntradas();
    int option;

    while((option = getopt(argc, argv, "edb:m:o:c:i:")) != -1) {
        switch (option) {
            case 'd':
                opts->operacao = OP_DECODE;
                break;
            case 'e':
                opts->operacao = OP_ENCODE;
                break;
            case 'm':
                opts->input = 1;
                opts->entrada = optarg;
                break;
            case 'i':
                opts->input = 1;
                opts->entrada = optarg;
                break;
            case 'o':
                opts->out = 1;
                opts->saida = optarg;
                break;
            case 'c':
                opts->cipher = 1;
                opts->cifra = optarg;
                break;
            case 'b':
                opts->book = 1;
                opts->livro = optarg;
                break;
            default:
                return NULL;
                break;
        }
    }

    return opts;
}

/* Mosta toda a struct de opcoes.*/
void mostraOpts(struct entrada *opts)
{
    if (opts == NULL)
        return;
    printf ("Operacao: %d\n", opts->operacao);
    printf ("Input: %d\n", opts->input);
    printf ("Entrada: %s\n", opts->entrada);
    printf ("Book: %d\n", opts->book);
    printf ("Livro: %s\n", opts->livro);
    printf ("Out: %d\n", opts->out);
    printf ("Saida: %s\n", opts->saida);
    printf ("Cipher: %d\n", opts->cipher);
    printf ("Cifra: %s\n", opts->cifra);
}

/* Retorna 1 se o arquivo e valido e 0 caso contrario.*/
int arqValido(char *arq, char *op)
{
    if (arq == NULL)
        return 0;
    int sts = 1;
    FILE *pt = fopen(arq, op);
    if (pt == NULL)
        sts = 0;
    fclose(pt);

    return sts;
}

/* Verifica as opcoes especificas para o decode.
 * Retorna 1 se deu tudo certo e 0 caso contrario.*/
int verificaOptsDecode(struct entrada *opts)
{
    if (opts->input == 0 || opts->entrada == NULL) {
        fprintf(stderr, "Especifique a entrada para decode[-i]\n");
        return 0;
    }
    if (!arqValido(opts->entrada, "r")) {
        fprintf(stderr, "Arquivo de entrada invalido[-i]\n");
        return 0;
    }
    if (opts->book == opts->cipher) {
        fprintf(stderr, "Escolha arquivo base para decode[-c/-b]\n");
        return 0;
    }
    if (opts->book == 1 && !arqValido(opts->livro, "r")) {
        fprintf(stderr, "Livro para decode invalido[-b]\n");
        return 0;
    }
    if (opts->cipher == 1 && !arqValido(opts->cifra, "r")) {
        fprintf(stderr, "Arquivo de cifras invalido[-c]\n");
        return 0;
    }
    if (opts->out == 0 && !arqValido(opts->saida, "w")) {
        fprintf(stderr, "Arquivo de saida invalido[-o]\n");
        return 0;
    }

    return 1;
}

/* Verifica as opcoes especificas para o encode.
 * Retorna 1 se deu tudo certo e 0 caso contrario.*/
int verificaOptsEncode(struct entrada *opts)
{
    if (opts->book == 0 || !arqValido(opts->livro, "r")) {
        fprintf(stderr, "Livro para encode invalido[-b]\n");
        return 0;
    }
    if (opts->input == 0 || !arqValido(opts->entrada, "r")) {
        fprintf(stderr, "Entrada para encode invalida[-m]\n");
        return 0;
    }
    if (opts->out == 0 || !arqValido(opts->saida, "w")) {
        fprintf(stderr, "Arquivo de saida invalido[-o]\n");
        return 0;
    }
    if (opts->cipher == 1 && !arqValido(opts->cifra, "w")) {
        fprintf(stderr, "Nome do arquivo de chaves invalido[-c]\n");
        return 0;
    }

    return 1;
}

/* Retorna 1 se as opcoes estao sendo usadas corretamente e 0 caso contrario.*/
int validaOpts(struct entrada *opts)
{
    int sts = 1;
    if (opts->operacao == -1) {
        fprintf(stderr, "Faltando operação [decode(-d)/encode(-e)]\n");
        return 0;
    }
    if (opts->operacao == OP_DECODE)
        sts = verificaOptsDecode(opts);
    else 
        sts = verificaOptsEncode(opts);

    return sts;
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    struct entrada *opts = trataOpts(argc, argv);
    if (!validaOpts(opts)) {
        free(opts);
        return 1;
    }
    FILE *entrada, *saida, *livro, *cifra = NULL;

    entrada = fopen(opts->entrada, "r");
    saida = fopen(opts->saida, "w");

    if (opts->book == 1) {
        livro = fopen(opts->livro, "r");
        cifra = fopen(opts->cifra, "w");
    } else {
        cifra = fopen(opts->cifra, "r");
    }

    if (opts->operacao == OP_ENCODE) {
        codificaComTxt(entrada, saida, livro, cifra);
    } else {
        if (opts->book == 1)
            decodComTxt(entrada, saida, livro);
        else
            decodComCifras(entrada, saida, cifra);
    }
    free(opts);
    /* fclose(entrada); */
    /* fclose(saida); */
    /* fclose(livro); */
    /* fclose(cifra); */

    return 0;
}
