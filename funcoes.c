# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include "funcoes.h"

/*Funcao responsavel por fazer as comparacoes da entrada via linha de comando*/
int Verifica_entrada(int argc)
{
    if(argc <= MAX_ARGUMENTOS)
    {
        if(argc >= MIN_ARGUMENTOS)
        {
            return 1;
        }
        else
        {
            printf("ERRO! DEVEM SER DIGITADOS NO MÍNIMO 2 PARAMETROS!");
            return 0;
        }
    }
    else
    {
        printf("ERRO! DEVEM SER DIGITADOS NO MÁXIMO 3 PARÂMETROS\n");
        return 0;
    }
}

/*Funcao responsavel pela busca dos diretorios*/
void Busca_recursiva_diretorios(DIR *p_fluxo_da_pasta, DADO_ENTRADA *dado_entrada, struct dirent *id_nome_pasta)
{
    p_fluxo_da_pasta = opendir(dado_entrada->nome_da_pasta_inicial);

    /*Se a pasta existir*/  
    if(p_fluxo_da_pasta != NULL)
    {
        do
        {
            id_nome_pasta = readdir(p_fluxo_da_pasta);

            /*Verificacao caso atinja toda a varredura*/
            if(id_nome_pasta != NULL)
            {
                /*Se caso for uma pasta, ou seja um subdiretorio dentro da outra pasta que foi passado pelo fluxo, imprimo*/
                if(p_fluxo_da_pasta->dd_dta.attrib & _A_SUBDIR)
                {
                    /*Comparo se eh diferente das 2 entradas padroes que nao sao necessarias*/
                    if(strcmp(id_nome_pasta->d_name, ".") != 0 && strcmp(id_nome_pasta->d_name, "..") != 0)
                    {
                        /*Imprime diretorio*/
                        printf("%s <DIR>\n", id_nome_pasta->d_name);

                        /*Pego o nome da pasta atual, que sera um outro diretorio, apos isso abro outro fluxo para um outro caminho, que sera o caminho atual
                        dado_entrada->nome_da_pasta_inicial = strcat(p_fluxo_da_pasta->dd_name, id_nome_pasta->d_name);*/
                    }
                }
                else
                {
                    /*Imprime arquivo*/
                    printf("%s\n", id_nome_pasta->d_name);
                }
            }

        }while(id_nome_pasta != NULL);            
    }
    else
    {
        printf("PASTA INEXISTENTE!\n");
    }

    closedir(p_fluxo_da_pasta);
}