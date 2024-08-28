/*Bibliotecas*/
# include <dirent.h>

/*Definicoes de constantes*/
# define MAX_ARGUMENTOS 5
# define MIN_ARGUMENTOS MAX_ARGUMENTOS - 1
# define PASTA_INICIAL_VARREDURA 1
# define NOME_ARQUIVO_BUSCA 2

/*Registros*/
typedef struct _entrada_cmd
{   
    char *nome_caminho;
    char *nome_arquivo;
    DIR *p_fluxo_da_pasta;
}DADO_ENTRADA;


/*Funcao responsavel pela verificacao da entrada via linha de comando*/
int Verifica_entrada(int);

/*Funcao responsavel por comecar a busca recursiva*/
void Busque_diretorios(char  *, char *);