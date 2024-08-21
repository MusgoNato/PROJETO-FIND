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
# include <stdio.h>
# include "funcoes.h"

int main(int argc, char *argv[])
{
    DIR *nome_do_diretorio;
    struct dirent *id_nome_pasta;
    int retorno;
    argv = argv;

    argc++;

    /*Verifica entrada via linha de comando*/
    retorno = Verifica_entrada(argc);

    /*A partir do retorno, caso as entradas sejam validas atribuo minha estrutura*/
    if(retorno)
    {
        
    }   

    return 0;
}