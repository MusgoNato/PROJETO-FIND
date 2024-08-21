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