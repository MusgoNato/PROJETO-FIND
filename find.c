/*Programa: Projeto FIND.
Descrição: O programa será capaz de buscar um arquivo passado como argumento por qualquer pasta passada como argumento via terminal de comando,
o usuario podera procurar tambem por uma sequencia de caracteres dentro dos arquivos, onde o programa mostrara em quais linhas foram encontradas essa respectiva sequencia.
Programador: Hugo Josué Lema Das Neves 
RGM: 47159 
Data da última modificação: 06/09/2024*/


/*Instruções para compilação

Copie e cole no terminal a linha abaixo
gcc find.c -o find.exe funcoes.c conio_v3.2.4.c console_v1.5.5.c -Wall -pedantic -Wextra -Werror

Instruções para execução

1° Caso sua pasta possua espacos em branco ou seja um caminho direto, insira o nome entre aspas duplas. Caso contrario somente inserir o nome da pasta.

Ex: find "MINHA PASTA" abc.txt


Linha de execucao

find PASTA_INICIAL ARQUIVO_A_SER_PROCURADO SEQUENCIA_PROCURADA

Copie e cole apos terminado de executar a compilacao a linha abaixo como exemplo
find "C:\Program Files" abc.txt Ola 
*/

# include <stdio.h> /*printf()*/
# include "conio_v3.2.4.h" /*clrscr(), gotoxy()*/
# include "funcoes.h" /*Busque_diretorios(), Verifica_entrada(), NOME_ARQUIVO_BUSCA, NOME_SEQUENCIA, PASTA_INICIAL_VARREDURA*/

int main(int argc, char *argv[])
{
    GERAIS gerais;
    char *entrada_pasta_inicial;
    char *entrada_arquivo_procurado;
    char *entrada_sequencia_procurada;
    int retorno;

    argc++;

    /*Verifica entrada via linha de comando*/
    retorno = Verifica_entrada(argc);

    /*Alocacao dos argumentos que foram passados via linha de comando*/
    entrada_pasta_inicial = argv[PASTA_INICIAL_VARREDURA];
    entrada_arquivo_procurado = argv[NOME_ARQUIVO_BUSCA];
    entrada_sequencia_procurada = argv[NOME_SEQUENCIA];
    
    gerais.linha_de_impressao.X = 1;
    gerais.linha_de_impressao.Y = 1;
    gerais.conta_arquivos = 0;
    gerais.conta_pastas = 0;

    /*Caso o retorno seja verdadeiro, comeca o programa*/
    if(retorno)
    {
        /*Limpa tela*/
        clrscr();

        /*Chamada da minha funcao recursiva para busca dos diretorios*/
        Busque_diretorios(entrada_pasta_inicial, entrada_arquivo_procurado, &gerais, entrada_sequencia_procurada);

        /*Impressao dos dados analisados*/
        gotoxy(gerais.linha_de_impressao.X, gerais.linha_de_impressao.Y + 1);
        printf("Fim da analise\nForam analisadas %d pastas e %d arquivos!\n", gerais.conta_pastas, gerais.conta_arquivos);
    }

    return 0;
}