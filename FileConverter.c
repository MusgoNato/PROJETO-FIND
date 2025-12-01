# include <stdio.h>      
# include <stdlib.h>    
# include <string.h>     
# include <windows.h>   
# include <winbase.h>
# include "conio_v3.2.4.h"
# include "funcoes.h"  

/*Main principal*/
int main(int argc, char *argv[])
{
    GERAIS gerais;
    char nome_arquivo[_MAX_ENV] = "";
    char entrada_pasta_inicial[_MAX_ENV];
    int retorno = 0;
    int tem_sub = 0;
    int i = 0;
    char temp[_MAX_ENV];
    FILE *teste;

    if(argc == 1)
    {
        printf("Insira o nome do arquivo: ");
        scanf("%s", nome_arquivo);

        teste = fopen(nome_arquivo, "r");
        if(!teste)
        {
            printf("Arquivo nao encontrado!\n");
            return 1;
        }
        fclose(teste);

        /*Retorna o caminho atual*/
        GetCurrentDirectory(_MAX_ENV, entrada_pasta_inicial);
    
        Varre_arquivo(nome_arquivo, entrada_pasta_inicial, nome_arquivo);

        printf("\nArquivo convertido com sucesso!\n");
        return 0;
    }

    /*MODO 2 e 3: com argumentos /ALL ou /ALL /SUB-DIR-INCLUDED*/
    retorno = Verifica_entrada(argc, argv);
    if(!retorno)
    {
        return 1;
    }

    /*Atribui o diretorio atual para pasta inicial de varredura*/
    GetCurrentDirectory(_MAX_ENV, entrada_pasta_inicial);
    
    /*Verificacao da entrada*/
    for(i= 1; i < argc; i++)
    {
        strncpy(temp, argv[i], sizeof(temp));
        strlwr(temp);

        if(strcmp(temp, "/sub-dir-included") == 0)
        {
            tem_sub = 1;
            break;
        }
    }
    
    clrscr();

    if(tem_sub)
    {
        /*MODO 3: Conversão recursiva (pastas e subpastas)*/
        Busque_diretorios(entrada_pasta_inicial, &gerais, tem_sub);
    }
    else
    {
        /*MODO 2: Conversao de todos os arquivos no diretorio*/
        Busque_diretorios(entrada_pasta_inicial, &gerais, tem_sub);
    }
    return 0;
}
