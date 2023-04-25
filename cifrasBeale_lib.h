#define TAM_CIFRAS 10

struct cifrasBeale {
    int tam;
    int tamTotal;
    struct chaveLista **cifras;
};

/* Cria o sistema de cifras e retorna ponteiro para struct cifrasBeale.*/
struct cifrasBeale *criaCifras();
