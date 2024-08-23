# include <stdio.h>
# include <string.h>
# include <windows.h>
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
void Busque_diretorios(DADO_ENTRADA *dado_entrada, struct dirent *id_nome_pasta)
{
    /*Abro o fluxo da pasta*/
    dado_entrada->p_fluxo_da_pasta = opendir(dado_entrada->nome_caminho);

    /*Se a pasta existir*/  
    if(dado_entrada->p_fluxo_da_pasta != NULL)
    {
        do
        {
            /*Leio o fluxo que foi passado*/
            id_nome_pasta = readdir(dado_entrada->p_fluxo_da_pasta);

            /*Verificacao caso atinja toda a varredura*/
            if(id_nome_pasta != NULL)
            {
                /*Se caso for uma pasta, ou seja um subdiretorio dentro da outra pasta que foi passado pelo fluxo, imprimo*/
                if(dado_entrada->p_fluxo_da_pasta->dd_dta.attrib & _A_SUBDIR)
                {
                    /*Comparo se eh diferente das 2 entradas padroes que nao sao necessarias*/
                    if(strcmp(id_nome_pasta->d_name, ".") != 0 && strcmp(id_nome_pasta->d_name, "..") != 0)
                    {
                        /*Imprime diretorio*/
                        printf("\t%s <DIR>\n", id_nome_pasta->d_name);
                        
                    }
                }
                else
                {
                    /*Imprime arquivo*/
                    printf("%s\n", id_nome_pasta->d_name);
                }
            }

            Sleep(350);
        }while(id_nome_pasta != NULL);            
    }
    else
    {
        printf("PASTA INEXISTENTE!\n");
    }

    closedir(dado_entrada->p_fluxo_da_pasta);
}