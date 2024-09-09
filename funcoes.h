/*Bibliotecas*/
# include <dirent.h> /*DIR*/
# include "console_v1.5.5.h" /*COORD*/

/*Definicoes de constantes*/
# define MAX_ARGUMENTOS 5
# define MIN_ARGUMENTOS MAX_ARGUMENTOS - 1
# define PASTA_INICIAL_VARREDURA 1
# define NOME_ARQUIVO_BUSCA 2
# define NOME_SEQUENCIA 3
# define TAM_LINHA 1024 

/*Registros*/

/*Estrutura para armazenamento dos principais arquivos do programa*/
typedef struct _entrada_cmd
{   
    char *nome_caminho;
    char *nome_arquivo;
    DIR *p_fluxo_da_pasta;
}DADO_ENTRADA;


/*Para variaveis gerais durante o decorrer do programa*/
typedef struct _cont
{
    int conta_pastas;
    int conta_arquivos;
    int controle_sequencia;
    COORD linha_de_impressao;
}GERAIS;

/*Funcao responsavel por comecar a busca recursiva

Explicacao:
A funcao recebe parametros que sera necessario para realizar uma busca recursiva dentro do diretorio inicial passado,
ao recebe-lo a busca comeca chamando recursivamente a propria funcao caso encontre alguma subpasta. Entretanto caso algum arquivo seja encontrado
o programa realiza a impressao do nome do arquivo encontrado (passado via linha de comando) e seu respectivo diretorio aonde foi encontrado.

Parametros:
1 - char * : Nome da pasta inicial ou caminho para varredura 
2 - char * : Nome do arquivo a ser procurado
3 - GERAIS *: Estrutura que contera variaveis de controle, contadoras e estrutura para impressoes em coordenadas especificas do terminal
4 - char * : Nome da sequencia a ser procurada dentro do arquivo buscado

Retorno:
Nenhum
*/
void Busque_diretorios(char  *, char *, GERAIS *, char *);

/*Funcao responsavel por remover o asterisco ao final de cada caminho percorrido pela funcao recursiva

Explicacao:
A funcao remove o asterisco de cada caminho, isto deve acontecer pois caso o caminho seja passado como parametro na funcao fopen() a mesma nao 
encontrara o arquivo desejado para abertura. O caminho retornado pela funcao readdir() vem como padrao um "*" ao final do caminho, sendo retirado
pela funcao Remove_asterisco() para encontrar o arquivo desejado com a funcao fopen().

Parametros:
1 - char * : Caminho do diretorio que esta sendo percorrido no programa

Retorno:
char * : Caminho modificado, retirando o "*" ao final do caminho original
*/
char * Remove_asterisco(char *);

/*Funcao responsavel por varrer o arquivo aberto

Explicacao:
Caso algum arquivo seja encontrado, eh necessario varrer o arquivo por inteiro, tentando encontrar a sequencia desejada dentro do arquivo encontrado.
Lembrando que esta funcao somente eh chamada quando a sequencia a ser procurada dentro do arquivo eh diferente de NULL, ou seja, deve existir uma sequencia
a ser buscada.

Parametros:
1 - char * : Sequencia a ser buscada dentro do arquivo encontrado
2 - char * : Caminho modificado sem o "*" ao final
3 - GERAIS * : Estrutura que contera variaveis de controle, contadoras e estrutura para impressoes em coordenadas especificas do terminal

Retorno:
Nenhum
*/
void Varre_arquivo(char *, char *, GERAIS *);

/*Funcao responsavel pela verificacao da entrada via linha de comando

Explicacao:
Caso o usuario insira mais de 3 parametros, o programa encerrara apresentando uma mensagem de erro pelo ocorrido,
o mesmo acontecendo para caso ele insira menos de 2 argumentos.

Parametros:
1 - int : Contadora de parametros passados via linha de comando.

Retorno:
int : Caso a quantidade passada seja dentro do intervalo possivel retorna 1 ao programa, caso contrario 0. 
*/
int Verifica_entrada(int);