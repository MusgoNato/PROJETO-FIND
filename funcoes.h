# include <dirent.h>

# define MAX_ARGUMENTOS 5
# define MIN_ARGUMENTOS MAX_ARGUMENTOS - 1
# define PASTA_INICIAL_VARREDURA 1
# define NOME_ARQUIVO_BUSCA 2

typedef struct _entrada_cmd
{   
    char *nome_da_pasta_inicial;
    char *nome_arquivo;
}DADO_ENTRADA;

/*Funcao responsavel pela verificacao da entrada via linha de comando*/
int Verifica_entrada(int);

/*Funcao responsavel por comecar a busca recursiva*/
void Busca_recursiva_diretorios(DIR *, DADO_ENTRADA *, struct dirent *);