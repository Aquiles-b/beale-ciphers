## Módulos usados: 

- lista_lib:
    Dicionário com a chave sendo uma letra. Os números na lista são ordenados 
    de forma decrescente.

- cifrasBeale_lib:
    Responsável pela maior parte do código. Esse módulo usa a lista_lib para guardar
    um determinado caractere e todas as posições das palavras que começam com ele,
    criando assim um sistema de cifras armazenado em uma struct, a qual contém
    um vetor de ponteiros para todas as letras do sistema.

- decodifica_lib:
    Usa o módulo cifrasBeale_lib para decodificar um arquivo. Oferece funções para
    decodificar usando um arquivo de cifras ou um livro/texto.

- codifica_lib:
    Usa o módulo cifrasBeale_lib para codificar um arquivo. Oferece funções para
    codificar usando um arquivo de cifras ou um livro/texto e também salvar o arquivo
    de cifras gerado quando se usa o livro.

- beale:
    É a parte principal onde junta tudo e faz a interface com o usuário, tratando
    as entradas e direcionando o fluxo do código.

## Algoritmos  
    Foi usado principalmente a Busca Binária e o Insertion-Sort. A escolha do 
    Insertion-Sort nesse caso é porque o vetor vai estar sempre com apenas o último
    elemento fora de posição, fazendo o custo desse algoritmo igual à nLg(n).
