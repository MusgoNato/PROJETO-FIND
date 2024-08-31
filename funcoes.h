/*Bibliotecas*/
# include <dirent.h> /*DIR*/
# include "conio_v3.2.4.h"
# include "console_v1.5.5.h"

/*Definicoes de constantes*/
# define MAX_ARGUMENTOS 5
# define MIN_ARGUMENTOS MAX_ARGUMENTOS - 1
# define PASTA_INICIAL_VARREDURA 1
# define NOME_ARQUIVO_BUSCA 2
# define NOME_SEQUENCIA 3
# define TAM_LINHA 1024

/*Registros*/
typedef struct _entrada_cmd
{   
    char *nome_caminho;
    char *nome_arquivo;
    DIR *p_fluxo_da_pasta;
}DADO_ENTRADA;

typedef struct _cont
{
    int conta_pastas;
    int conta_arquivos;
    COORD linha_de_impressao;
}GERAIS;


/*Funcao responsavel pela verificacao da entrada via linha de comando*/
int Verifica_entrada(int);

/*Funcao responsavel por comecar a busca recursiva*/
void Busque_diretorios(char  *, char *, GERAIS *, char *);

/*Funcao responsavel por varrer o arquivo aberto*/
void Varre_arquivo(char *, char *, GERAIS *);

/*Funcao responsavel por remover o asterisco ao final de cada caminho percorrido pela funcao recursiva*/
char * Remove_asterisco(char *);