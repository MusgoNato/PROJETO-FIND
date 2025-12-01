/*Bibliotecas*/
# include <dirent.h> /*closedir(), opendir(), readdir(), DIR, struct dirent*/
# include <stdio.h> /*fclose(), fgets(), fopen(), printf(), snprintf(),  FILENAME_MAX, NULL*/
# include <stdlib.h> /*_MAX_ENV*/
# include <string.h> /*strcat(), strcmp(), strcpy(), strlen(), strstr() strlwr()*/
# include "conio_v3.2.4.h" /*clreol(), gotoxy()*/
# include "funcoes.h" /*Busque_Diretorios(), Remove_asterisco(), Varre_arquivo(), Verifica_entrada() */

/*Funcao responsavel pela busca dos diretorios*/
void Busque_diretorios(char *nome_caminho, GERAIS *gerais, int tem_sub)
{
    char novo_caminho[_MAX_ENV];
    char caminho_completo[_MAX_ENV];
    char caminho_modificado[_MAX_ENV];
    struct dirent *id_nome_pasta;
    DIR *p_fluxo_da_pasta;

    /*Abro o fluxo da pasta*/
    p_fluxo_da_pasta = opendir(nome_caminho);

    /*Se caso o caminho nao existir, sai da recursao*/  
    if(p_fluxo_da_pasta == NULL)
    {
        printf("ERRO: Caminho inexistente [%s]!\n", nome_caminho);
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
                /*Se caso for uma pasta, ou seja um subdiretorio dentro da outra pasta que foi passado pelo fluxo, faco uma nova busca dentro do subdiretorio ou ignoro para nao entrar em busca recursiva*/
                if((p_fluxo_da_pasta->dd_dta.attrib & _A_SUBDIR))
                {
                    if(tem_sub)
                    {                        
                        snprintf(novo_caminho, sizeof(novo_caminho), "%s\\%s", nome_caminho, id_nome_pasta->d_name);

                        /*Chamada recursiva*/
                        Busque_diretorios(novo_caminho, gerais, tem_sub);    
                    }
                    else
                    {
                        /*Ignora a pasta, pois existe o comando sub-dir-included passado via linha de comando*/
                        continue;
                    }
                }
                else
                {   
                    snprintf(caminho_completo, sizeof(caminho_completo), "%s", p_fluxo_da_pasta->dd_name);
                    
                    /*Chama a funcao responsavel por retirar os asteriscos ao final de cada caminho, assim posso passar para a funcao fopen sem
                    problemas*/
                    strcpy(caminho_modificado, Remove_asterisco(caminho_completo));

                    /*Concateno com o nome do arquivo atual*/
                    snprintf(caminho_completo, sizeof(caminho_completo), "%s\\%s", nome_caminho, id_nome_pasta->d_name);
                    
                    /*Passo o caminho completo com o nome do arquivo ao final, o caminho modificado sendo somente o caminho atual da pasta a ser varrida
                    e o nome do arquivo em si, para concatenar dentro da funcao*/
                    Varre_arquivo(caminho_completo, caminho_modificado, id_nome_pasta->d_name);                    
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
    int tam = 0;

    tam = strlen(caminho);
    
    if(tam > 0 && caminho[tam - 1] == '*')
    {
        caminho[tam - 1] = '\0';
    }

    return caminho;
}

/*Funcao responsavel pela conversao de arquivos ANSI (Windows-1252) para OEM 850*/
void Varre_arquivo(char *caminho_completo,  char *caminho_modificado, char *nome_arquivo)
{
    FILE *abre_arquivo, *saida;
    char caminho_saida[_MAX_ENV];
    char buffer_ansi[1024];
	wchar_t buffer_unicode[1024];
    char buffer_oem[1024];
    int num_unicode;
	int num_oem;

    /*Monta caminho para o arquivo temporario*/
    snprintf(caminho_saida, sizeof(caminho_saida), "%s\\temp_%s", caminho_modificado, nome_arquivo);

    abre_arquivo = fopen(caminho_completo, "r");
    if(abre_arquivo == NULL)
    {
        printf("Nao foi possivel abrir para leitura o arquivo : %s\n", nome_arquivo);
        return;
    } 

    saida = fopen(caminho_saida, "wb");
    if(saida == NULL)
    {
        printf("Nao foi possivel abrir o arquivo para escrita em : %s\n", caminho_completo);
        fclose(abre_arquivo);
        return;
    }

    /*Verifica caso o arquivo exista*/
    if(abre_arquivo != NULL)
    {
        /*printf("Fazendo conversao de arquivo : %s\n", nome_arquivo);*/
        while(fgets(buffer_ansi, sizeof(buffer_ansi), abre_arquivo))
        {
            num_unicode =  MultiByteToWideChar(
                1252, /*Pagina de codigo de origem (ANSI Latin 1)*/
												0, /*Para converter para UTF-8*/
												buffer_ansi, /* String de entrada a ser convertida*/
												-1, /*ou o tamanho da string de entrada, ou -1 se a string de entrada for terminada em
                                                    nulo*/
												buffer_unicode, /*Buffer que receber a cadeia convertida*/
												1024 /*tamanho do buffer de saida*/
											  );
            if(num_unicode == 0)
            {
                printf("ERRO : Ao converter para Unicode!\n");
                break;
            }

            /*Converter Unicode OEM 850*/
			num_oem = WideCharToMultiByte(
											850, /*Pagina de codigo destino da conversao ( OEM850 )*/
											0,   /*Converter para UTF-8*/ 
											buffer_unicode, /* String de entrada a ser convertida*/
											-1, /*indicar que a string de entrada deve ser terminada pelo caracter NULL */
											buffer_oem,	/* Buffer que receber a cadeia convertida*/ 
											1024, /*tamanho do buffer que receber a cadeia convertida*/
											NULL, 
											NULL
										  );
			if (num_oem == 0)
			{
				printf("ERRO : Ao converter para OEM 850!\n");
				break;
			}

            /*Escreve no arquivo de saida*/
            fputs(buffer_oem, saida);
        }
    }

    /*Fecha os arquivos*/
    fclose(abre_arquivo);
    fclose(saida);
    
    /*Remove e renomeia o arquivo para evitar arquivos temporarios*/
    if(remove(caminho_completo) != 0)
    {
        printf("Erro em tentar remover o arquivo %s\n", caminho_completo);
    }
    else
    {
        if(rename(caminho_saida, caminho_completo) != 0)
        {
            printf("Erro em tentar renomear o arquivo convertido para original: %s\n", caminho_completo);
        }
        else
        {
            printf("Arquivo %s convertido com sucesso!\n", nome_arquivo);
        }
    }
}

/*Funcao responsavel por fazer as comparacoes da entrada via linha de comando*/
int Verifica_entrada(int argc, char *argv[])
{
    int tem_all = 0;
    int tem_sub = 0;
    char arg_lower[64];
    int i = 0;

    /*Passado no cmd somente 'FileConverter'*/
    if(argc == NOME_PROGRAMA)
    {
        return 1;
    }

    /*Passado no cmd 'FileConverter /ALL' ou 'FileConverter /ALL /SUB-DIR-INCLUDED', somente como exemplo mas pode ser passado com qualquer ordem*/
    if(argc == COMANDO1 || argc == COMANDO2)
    {
        /*Comparacao das entradas*/
        for(i = 1; i < argc; i++)
        {
            strncpy(arg_lower, argv[i], sizeof(arg_lower));
            strlwr(arg_lower);

            if(strcmp(arg_lower, "/all") == 0)
            {
                tem_all = 1;
            }
            else
            {
                if(strcmp(arg_lower, "/sub-dir-included") == 0) 
                {
                    tem_sub = 1;
                } 
            }
        }

        /*Retorno caso seja somente /ALL via linha de comando*/
        if(tem_all) 
        {
            return 1;
        }
        else 
        {
            /*Aqui caso o usuario passe 'FileConverter /SUB-DIR-INCLUDED'*/
            printf("\nErro: A op��ǜo /ALL Ǹ obrigat��ria.\n");
            return 0;
        }
    }

    /*Mensagens de erro e exemplos*/
    printf("\nUso incorreto. Exemplos vǭlidos:");
    printf("\n\tFileConverter");
    printf("\n\tFileConverter /ALL");
    printf("\n\tFileConverter /ALL /SUB-DIR-INCLUDED");
    printf("\n\tFileConverter /SUB-DIR-INCLUDED /ALL\n");
    printf("\nTem /ALL : %d, Tem /SUB-DIR-INCLUDED : %d", tem_all, tem_sub);
    return 0;
}