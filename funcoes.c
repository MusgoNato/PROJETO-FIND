/*Bibliotecas*/
# include <stdio.h> /*fclose(), fgets(), fopen(), printf(), snprintf(), FILENAME_MAX, NULL*/
# include <stdlib.h> /*_MAX_ENV*/
# include <string.h> /*strcat(), strcmp(), strcpy(), strlen(), strstr()*/
# include <dirent.h> /*closedir(), opendir(), readdir(), DIR, struct dirent*/
# include "conio_v3.2.4.h" /*clreol(), gotoxy()*/
# include "funcoes.h" /*Busque_Diretorios(), Remove_asterisco(), Varre_arquivo(), Verifica_entrada() */

/*Funcao responsavel pela busca dos diretorios*/
void Busque_diretorios(char *nome_caminho, char *nome_arquivo, GERAIS *gerais, char *nome_sequencia)
{
    char novo_caminho[_MAX_ENV];
    char arquivo_buscado[FILENAME_MAX];
    char caminho_completo[_MAX_ENV];
    char *caminho_modificado;
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
                /*Imprime pastas*/
                gotoxy(gerais->linha_de_impressao.X, gerais->linha_de_impressao.Y);
                clreol();
                printf("Analisando caminho: %s\n", p_fluxo_da_pasta->dd_name);

                /*Se caso for uma pasta, ou seja um subdiretorio dentro da outra pasta que foi passado pelo fluxo, imprimo*/
                if(p_fluxo_da_pasta->dd_dta.attrib & _A_SUBDIR)
                {
                    gerais->conta_pastas++;
                    
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
                        printf("Arquivo %s encontrado em -> %s\n", id_nome_pasta->d_name, p_fluxo_da_pasta->dd_name);
                        
                        snprintf(caminho_completo, sizeof(caminho_completo), "%s", p_fluxo_da_pasta->dd_name);

                        /*Chama a funcao responsavel por retirar os asteriscos ao final de cada caminho, assim posso passar para a funcao fopen sem
                        problemas*/
                        caminho_modificado = Remove_asterisco(caminho_completo);

                        /*Concateno com o nome do arquivo atual*/
                        strcat(caminho_completo, "\\");
                        strcat(caminho_completo, id_nome_pasta->d_name);

                        /*Verificacao caso exista sequencia a ser buscada*/
                        if(nome_sequencia != NULL)
                        {
                            /*Chama a funcao responsavel por abrir meu arquivo*/
                            Varre_arquivo(nome_sequencia, caminho_modificado, gerais);
                        }

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

/*Funcao responsavel por retirar os asteriscos do caminho completo atual sendo percorrido*/
char * Remove_asterisco(char *caminho)
{
    int i;
    int tam = 0;
    char aux[_MAX_ENV];

    tam = strlen(caminho);
    
    /*Coloca-se cada letra dentro do vetor auxiliar, exceto o "*", por isso tam - 1*/
    for(i = 0; i < tam - 1; i++)
    {
        aux[i] = caminho[i];
    }

    /*Copia-se o caminho modificado (aux) para o caminho original*/
    strcpy(caminho, aux);

    return caminho;
}

/*Funcao respoansavel por varrer o arquivo aberto pela funcao recursiva*/
void Varre_arquivo(char *sequencia_buscada, char *caminho_modificado, GERAIS *gerais)
{
    char linha[TAM_LINHA];
    char *retorno;
    char *substring_encontrada;
    int i = 0;
    FILE *abre_arquivo;

    abre_arquivo = fopen(caminho_modificado, "r");

    /*Verifica caso o arquivo exista*/
    if(abre_arquivo != NULL)
    {
        do
        {       
            /*Pega-se cada linha do arquivo, armazenando em um vetor de caracteres*/
            retorno = fgets(linha, TAM_LINHA, abre_arquivo);

            if(retorno == NULL)
            {
                break;
            }
            else
            {
                i++;
                
                /*Busco minha substring atraves da funcao strstr, retornando a primeira ocorrencia da substring dentro da linha lida do arquivo encontrado*/
                substring_encontrada = strstr(linha, sequencia_buscada);
                
                /*Impressao da linha do arquivo somente caso seja encontrado a sequencia*/
                if(substring_encontrada != NULL)
                {
                    /*Imprime linha do arquivo*/
                    gotoxy(gerais->linha_de_impressao.X, gerais->linha_de_impressao.Y++);
                    printf("Linha %d -> %s", i, linha);
                } 
            }

        }while(retorno != NULL);

        fclose(abre_arquivo);
    }
    
}

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