/*Programa: Projeto FIND.
Descrição: O programa será capaz de buscar um arquivo passado como argumento por qualquer pasta passada como argumento via terminal de comando
Programador: Hugo Josué Lema Das Neves 
RGM: 47159 
Data da última modificação: 19/08/2024 


Instruções para compilação
gcc find.c -o find.exe funcoes.c -Wall -pedantic -Wextra -Werror

Instruções para execução
find.exe nome_da_pasta nome_do_arquivo
*/


/*struct DIR, struct dirent 
						GCC 4.7.2:
						struct dirent
						{
							long		d_ino;		     Always zero. 
							unsigned short	d_reclen;	 Always zero. 
							unsigned short	d_namlen;	 Length of name in d_name. 
							char		d_name[260];     [FILENAME_MAX]  File name. 
						};
					*/ 

# include <direct.h>
# include <stdlib.h>
# include <stdio.h>
# include "funcoes.h"

/*Por entrada, as funcoes como opendir ja tratam a entrada, dando para colocar exemplos como:
    find "C:\\" a b ou find "C:\\ a" a b, nestes casos ele ja trata os espacos em branco pelo terminal*/


int main(int argc, char *argv[])
{
    /*Ponteiro para o fluxo da pasta que sera analisada*/
    DIR p_fluxo_da_pasta;

    DADO_ENTRADA dado_entrada;

    /*Ponteiro para um dos nomes da pasta*/
    struct dirent id_nome_pasta;

    int retorno;
    argv = argv;

    argc++;

    /*Verifica entrada via linha de comando*/
    retorno = Verifica_entrada(argc);

    /*Alocacao dos argumentos que foram passados via linha de comando*/
    dado_entrada.nome_da_pasta_inicial = argv[PASTA_INICIAL_VARREDURA];
    dado_entrada.nome_arquivo = argv[NOME_ARQUIVO_BUSCA];

    /*Caso o retorno seja verdadeiro, comeca o programa*/
    if(retorno)
    {
       Busca_recursiva_diretorios(&p_fluxo_da_pasta, &dado_entrada, &id_nome_pasta);
    }   

    return 0;
}