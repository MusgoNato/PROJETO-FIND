#include <stdlib.h> /* exit() */
#include <stdio.h>  /* printf() */
#include <io.h>     /* _findfirst(), _findnext(), estrutura _finddata  */

/*gcc prog_v1.c -o prog_v1.exe -Wall -pedantic -Wextra -Werror*/


int main (int argc, char *argv[])
{

    long int id; /* identificador do resultado retornado pela busca por um nome de arquivo */
    char *lista_nomes_de_um_diretorio = ".\\*.*"; /* outro exemplo: 
                                                    "C:\\Arquivos de programas\\*.*"
                                                    */   
    struct _finddata_t dados_diretorio; /* estrutura que armazenará o resultado retornado pela função _findfirst */ 

    /* Silenciar o warning dos parâmetros da main() que não são utilizados neste programa */
    argc = argc;
    argv = argv;
    
    /* buscar por todos os nomes existentes no diretório indicado e armazenar o resultado dessa busca na variavel dados_diretorio */  
    id = _findfirst (lista_nomes_de_um_diretorio, &dados_diretorio); 

    if (id == -1)
    {
        exit(1);
    } 
    
    do
    {
        
        if(dados_diretorio.attrib & _A_SUBDIR)
        {
            printf("%s\n", dados_diretorio.name); /* caso o nome atual, seja o nome de um diretório, imprimir também a string <DIR> conjuntamente */
        } 
        else
        {
            printf("%s\n", dados_diretorio.name); /* imprimir cada um dos nomes encontrados na busca */
        }

    }while(!_findnext(id, &dados_diretorio)); /* ir para o próximo nome localizado no diretório */

    _findclose(id);  /* liberar os recursos alocados vinculados ao identificador da busca realizada */	

  return 0;
}