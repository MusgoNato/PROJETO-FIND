/*Bibliotecas*/
# include <stdio.h> /*printf(), snprintf(), FILENAME_MAX*/
# include <string.h> /*strcmp()*/
# include <dirent.h> /*closedir(), opendir(), readdir(), DIR, dirent*/
# include <windows.h> /*_MAX_ENV*/
# include "conio_v3.2.4.h"
# include "funcoes.h" /*Busque_Diretorios(), Verifica_entrada()*/


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
            printf("ERRO! DEVEM SER DIGITADOS NO MINIMO 2 PARAMETROS!");
            return 0;
        }
    }
    else
    {
        printf("ERRO! DEVEM SER DIGITADOS NO MAXIMO 3 PARÂMETROS\n");
        return 0;
    }
}

/*Funcao responsavel pela busca dos diretorios*/
void Busque_diretorios(char *nome_caminho, char *nome_arquivo, GERAIS *gerais, char *nome_sequencia)
{
    char novo_caminho[_MAX_ENV];
    char arquivo_buscado[FILENAME_MAX];
    struct dirent *id_nome_pasta;
    DIR *p_fluxo_da_pasta;


    /*Abro o fluxo da pasta*/
    p_fluxo_da_pasta = opendir(nome_caminho);

    /*Se caso o caminho nao existir, sai da recursao*/  
    if(p_fluxo_da_pasta == NULL)
    {
        printf("PASTA INEXISTENTE!\n");
        return;
    }

    do
    {
        /*Leio o fluxo que foi passado*/
        id_nome_pasta = readdir(p_fluxo_da_pasta);

        /*Verificacao caso atinja toda a varredura*/
        if(id_nome_pasta != NULL)
        {
            /*Comparo se eh diferente das 2 entradas padroes que nao sao necessarias*/
            if(strcmp(id_nome_pasta->d_name, ".") != 0 && strcmp(id_nome_pasta->d_name, "..") != 0)
            {
                /*Se caso for uma pasta, ou seja um subdiretorio dentro da outra pasta que foi passado pelo fluxo, imprimo*/
                if(p_fluxo_da_pasta->dd_dta.attrib & _A_SUBDIR)
                {
                    gerais->conta_pastas++;
                    delline();
                    gotoxy(gerais->linha_de_impressao.X, gerais->linha_de_impressao.Y);

                    /*Imprime pasta*/
                    printf("\tAnalisando caminho: %s\n", p_fluxo_da_pasta->dd_name);
                    
                    /*Aloco memoria suficiente para meu novo caminho, concatenando-o com a pasta atual encontrada*/
                    snprintf(novo_caminho, sizeof(novo_caminho), "%s\\%s", nome_caminho, id_nome_pasta->d_name);

                    /*Chamada recursiva passado o novo caminho encontrado*/
                    Busque_diretorios(novo_caminho, nome_arquivo, gerais, nome_sequencia);

                }
                else
                {
                    /*Atribuicao do arquivo pego da pasta atual para meu arquivo criado localmente, para fins de comparacao*/
                    snprintf(arquivo_buscado, sizeof(arquivo_buscado), "%s", id_nome_pasta->d_name);

                    /*Verificacao caso o arquivo seja igual ao passado via linha de comando*/
                    if(!strcmp(nome_arquivo, arquivo_buscado))
                    {
                        /*Imprime arquivo encontrado*/
                        gotoxy(gerais->linha_de_impressao.X, gerais->linha_de_impressao.Y++);
                        printf("\n\tArquivo %s encontrado em -> %s\n", id_nome_pasta->d_name, p_fluxo_da_pasta->dd_name);
                    }
                    else
                    {
                        /*Imprime arquivo
                        printf("%s\n", id_nome_pasta->d_name);*/
                    }

                    gerais->conta_arquivos++;
                    
                }
            }
        }
        else
        {
            break;
        }

    }while(id_nome_pasta != NULL); 

    /*Desaloca recursos da pasta que foi aberta*/         
    closedir(p_fluxo_da_pasta);
}