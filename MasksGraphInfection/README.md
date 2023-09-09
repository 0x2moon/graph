# Masks graph infection

## Descrição
Este é um projeto para verificar a possibilidade de infecção da COVID-19 em indivíduos sem e com máscara de acordo com o contato/relação entre eles, para tal foi utilizado como estrutura de analize o grafo, desenvolvido com lista de adjacência. Neste README, você encontrará todas as informações básicas necessárias para compreender este projeto.

## Funções presentes no arquivo main.c (Em ordem)
- Criação do Grafo e suas estruturas
- Funções de criação para cada estrutura
- Desalocar grafo
- Funções de funcionalidade do grafo
- Funções de analize do grafo
- Imprime a estrutura do grafo

## Estrutura do projeto
- Pasta: (MasksGraphInfection)
    - Arquivo:
        - README.md
        - main.c
        - Makefile
    - Pasta: (csv)
        - Arquivo:
            - small.csv  
            - big.csv

## Estrutura do arquivo csv para o codigo
- Obrigatóriamente prescisa do '\n' ao final da linha sendo de 6 em 5 caracteres por linha como o exemplo:
    - csv exemplo
    -[A1,B2
    A1,B3]
    - O colchetes [] demonstram a quantidade de \n no inicio e final;

## Execução
Para executar o projeto, siga estas etapas:

1. dentro da pasta MasksGraphInfection;
2. digite make no TTY e coloque o caminho do arquivo csv, será executado e gerado um arquivo TXT;
3. no projeto tem dois arquivos teste sendo o path 
    - /csv/small.csv 
    - /csv/big.csv
4. Respeitando a estrutura do arquivo csv descrita pode se utilizar outro arquivo;
5. para esxutar digite: 
    - ### make big
    - ### make small
6. make clean apaga o executável e o TXT, cada execução sobreescreve o TXT