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

/*Nome do diretorio completo o dado_entrada->p_fluxo_da_pasta me da caso eu abra com o opendir, porem caso eu imprima o dado_entrada->p_fluxo_da_pasta.dd_dir.d_name,
somente consigo imprimi-lo depois de ler a pasta atual, que sera o diretorio completo, assim eu consigo o nome da pasta atual, que no caso do argumento ser ".", será o mesmo, "."*/

/*Funcao responsavel pela busca dos diretorios*/
void Busque_diretorios(DADO_ENTRADA *dado_entrada, struct dirent *id_nome_pasta)
{
    char caminho_novo[1024];
    char path[1024];

    /*Abro o fluxo da pasta*/
    dado_entrada->p_fluxo_da_pasta = opendir(dado_entrada->nome_caminho);
    
    /*Se o caminho existe*/  
    if(dado_entrada->p_fluxo_da_pasta != NULL)
    {
        /*Copio o caminho inteiro atual onde estou percorrendo, assim posteriormente consigo voltar*/
        strcpy(path, dado_entrada->p_fluxo_da_pasta->dd_name);

        do
        {
            /*Leio o fluxo que foi passado*/
            id_nome_pasta = readdir(dado_entrada->p_fluxo_da_pasta);

            /*Verificacao caso atinja toda a varredura*/
            if(id_nome_pasta != NULL)
            {
                /*Comparo se eh diferente das 2 entradas padroes que nao sao necessarias*/
                if(strcmp(id_nome_pasta->d_name, ".") != 0 && strcmp(id_nome_pasta->d_name, "..") != 0)
                {
                    /*Se caso for uma pasta, ou seja um subdiretorio dentro da outra pasta que foi passado pelo fluxo, imprimo*/
                    if(dado_entrada->p_fluxo_da_pasta->dd_dta.attrib & _A_SUBDIR)
                    {
                        /*Crio meu caminho novo*/
                        snprintf(caminho_novo, sizeof(caminho_novo), "%s\\%s", dado_entrada->nome_caminho, id_nome_pasta->d_name);

                        /*Copio o caminho novo para meu caminho atual sendo percorrido*/
                        strcpy(dado_entrada->nome_caminho, caminho_novo);

                        printf("Caminho novo : %s\n", dado_entrada->nome_caminho);

                        /*Chamo a funcao com o caminho modificado*/
                        Busque_diretorios(dado_entrada, id_nome_pasta);

                        /*Apos a saida da recursao devolvo o valor original do path que foi pego antes para o nome do caminho que sera aberto no opendir()*/
                        strcpy(dado_entrada->nome_caminho, path);

                        printf("%s\n", dado_entrada->nome_caminho);

                    }
                    else
                    {
                        /*Imprime arquivo*/
                        printf("%s\n", id_nome_pasta->d_name);
                    }
                }
                
            }
            else
            {
                break;
            }

            Sleep(200);
        }while(id_nome_pasta != NULL); 

        closedir(dado_entrada->p_fluxo_da_pasta);
         
    }
    else
    {
        printf("PASTA INEXISTENTE!\n");
    }

    
}