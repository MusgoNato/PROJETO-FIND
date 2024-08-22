# include <stdio.h>
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

void Busca_recursiva_diretorios(DIR *p_fluxo_da_pasta, DADO_ENTRADA *dado_entrada, struct dirent *id_nome_pasta)
{
    int saida_varredura = 1;

    p_fluxo_da_pasta = opendir(dado_entrada->nome_da_pasta_inicial);

    /*Se a pasta existir*/  
    if(p_fluxo_da_pasta != NULL)
    {
        do
        {
            id_nome_pasta = readdir(p_fluxo_da_pasta);

            /*Verificacao caso atinja toda a varredura*/
            if(id_nome_pasta == NULL)
            {
                saida_varredura = 0;
            }

            /*Se caso for uma pasta, ou seja um subdiretorio dentro da outra pasta que foi passado pelo fluxo, imprimo*/
            if(p_fluxo_da_pasta->dd_dta.attrib & _A_SUBDIR && saida_varredura != 0)
            {
                printf("%s\n", id_nome_pasta->d_name);
                
            }
        }while(saida_varredura);            
    }
    else
    {
        printf("PASTA INEXISTENTE!\n");
    }

    /*Fecha o fluxo da minha pasta*/
    closedir(p_fluxo_da_pasta);
}