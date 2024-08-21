# include <dirent.h>

# define MAX_ARGUMENTOS 5
# define MIN_ARGUMENTOS MAX_ARGUMENTOS - 1

typedef struct _dados_via_cmd
{
    char *argumento_nome_pasta;
    
}DADOS_ENTRADA;


/*Funcao responsavel pela verificacao da entrada via linha de comando*/
int Verifica_entrada(int);