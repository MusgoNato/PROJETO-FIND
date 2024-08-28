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
    char *entrada_pasta_inicial;
    char *entrada_arquivo_procurado;
    int retorno;

    argc++;

    /*Verifica entrada via linha de comando*/
    retorno = Verifica_entrada(argc);

    /*Alocacao dos argumentos que foram passados via linha de comando*/
    entrada_pasta_inicial = argv[PASTA_INICIAL_VARREDURA];
    entrada_arquivo_procurado = argv[NOME_ARQUIVO_BUSCA];
    printf("%s", entrada_arquivo_procurado);

    /*Caso o retorno seja verdadeiro, comeca o programa*/
    if(retorno)
    {
        system("cls");

        /*Chamda da minha funcao recursiva para busca dos diretorios*/
        Busque_diretorios(entrada_pasta_inicial, entrada_arquivo_procurado);
    }

    return 0;
}