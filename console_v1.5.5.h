#ifndef _CONSOLE
#define _CONSOLE

#include <windows.h>
/* -> Estrutura COORD:
      typedef struct _COORD{
              SHORT X;   -> inteiro curto
              SHORT Y;   -> inteiro curto
              } COORD;
   -> Tipos WORD, DWORD e LPSTR
*/

/****************************************************************************************************************/
/*                                  IN÷CIO DAS DECLARAÄÂES DE DEFINES E CONSTANTES                              */
/****************************************************************************************************************/

/* Para manter retrocompatibilidade com c¢digos que usassem o nome de campo codigo_tecla presente nas vers‰es anteriores da console (v1.5.4 para tr†s) */ 
#define codigo_tecla key_code

/* key_codes */
	#define F1 112
	#define F2 113
	#define F3 114
	#define F4 115
	#define F5 116
	#define F6 117
	#define F7 118
	#define F8 119
	#define F9 120
	#define F10 121
	#define F11 122
	#define F12 123

	#define ESC 27
	#define ENTER 13
	#define BACKSPACE 8
	#define ESPACO 32
	#define TAB 9

	/* Enhanced keys */
		#define INSERT 45
		#define DEL 46
		#define PAGE_UP 33
		#define PAGE_DOWN 34
		#define END 35
		#define HOME 36
		#define SETA_PARA_ESQUERDA 37
		#define SETA_PARA_CIMA 38
		#define SETA_PARA_DIREITA 39
		#define SETA_PARA_BAIXO 40

	/* Teclas de status */
		#define SHIFT_ESQUERDO_PRESSIONADO 0x0200  /* (constante definida por mim = 0x200 = shift esquerdo pressionado) + (0x010 = shift pressionado) = 0x210. Valor definido com base em uma extens∆o dos valores contidos na tabela: http://msdn.microsoft.com/pt-br/library/windows/desktop/ms684166%28v=vs.85%29.aspx */
		#define SHIFT_DIREITO_PRESSIONADO 0x0400  /* (constante definida por mim = 0x400 = shift direito pressionado) + (0x010 = shift pressionado) = 0x410. Valor definido com base em uma extens∆o dos valores contidos na tabela: http://msdn.microsoft.com/pt-br/library/windows/desktop/ms684166%28v=vs.85%29.aspx */

/*--------------------*/


/* constantes definidas para identificar a liberaá∆o de um determinado bot∆o do mouse */
#define FROM_LEFT_1ST_BUTTON_RELEASED FROM_LEFT_1ST_BUTTON_PRESSED
#define FROM_LEFT_2ND_BUTTON_RELEASED FROM_LEFT_2ND_BUTTON_PRESSED
#define FROM_LEFT_3RD_BUTTON_RELEASED FROM_LEFT_3RD_BUTTON_PRESSED
#define FROM_LEFT_4TH_BUTTON_RELEASED FROM_LEFT_4TH_BUTTON_PRESSED
#define RIGHTMOST_BUTTON_RELEASED RIGHTMOST_BUTTON_PRESSED

/* dar a opá∆o ao programador de usar constantes em portuguàs, caso queira */
#define BOTAO_ESQUERDO_PRESSIONADO FROM_LEFT_1ST_BUTTON_PRESSED
#define BOTAO_ESQUERDO_LIBERADO FROM_LEFT_1ST_BUTTON_RELEASED
#define BOTAO_DIREITO_PRESSIONADO RIGHTMOST_BUTTON_RELEASED
#define BOTAO_DIREITO_LIBERADO RIGHTMOST_BUTTON_RELEASED

/* constantes utilizadas pela funá∆o IdentificarEvento() para definir o nivel
   de detalhamento das informaá‰es a serem coletadas de um evento */
#define MINIMO 1
#define MAXIMO 2

#define BIT_SHORT_MAIS_SIGNIFICATIVO 0x80  /* (0x80) na base hexadecimal = (128) na base 10 = (1000 0000) na base 2 */
#define TECLA_PRESSIONADA 0x80
/****************************************************************************************************************/
/*                                  FIM DAS DECLARAÄÂES DE DEFINES E CONSTANTES                              */
/****************************************************************************************************************/




/****************************************************************************************************************/
/*                                   DECLARAÄÂES DE ESTRUTURAS E ENUMERAÄÂES                                    */
/****************************************************************************************************************/

 /* estrutura para o armazenamento das cores da janela de console */
    typedef struct{
                  int CorTexto;      /* cor do texto da janela de prompt atual */
		          int CorFundo;      /* cor de fundo da janela de prompt atual */
                  }CORES;


 /* tipo STATUS contendo os valores para ligar e desligar o cursor do mouse da tela */
    typedef enum{DESLIGAR, LIGAR} STATUS;


 /* tipo VISIBILIDADE */
    typedef enum{INVISIVEL, VISIVEL} VISIBILIDADE;


 /* tipo que permite identificar que tipo de evento deve ser verificada a existància no buffer de eventos */
    typedef enum{KEYBOARD_HIT, MOUSE_HIT, ALL} TYPE_HIT;


 /* Detalhes desta estrutura, ver link:
    http://msdn.microsoft.com/en-us/library/windows/desktop/ms684166%28v=vs.85%29.aspx */
    enum T_STATUS_TECLA{LIBERADA, PRESSIONADA};
    typedef struct T_TECLADO{
                            enum T_STATUS_TECLA status_tecla; /* LIBERADA ou PRESSIONADA */
		 				    WORD key_code; /* c¢digo numÇrico que identifica uma tecla independente do tipo do teclado */
							WORD scan_code; /* c¢digo numÇrico que identifica uma tecla de acordo com o valor gerado pelo hardware de teclado (Ç dependente do tipo do teclado) */
							CHAR ascii_code; /* traduá∆o do valor key_code para o caracter correspondente, considerando o estado do teclado (shift, caps-lock, etc., pressionadas). Faz a traduá∆o considerando a linguagem atual e o layout do teclado f°sico */
							WORD repeat_count; /* N£mero que indica que uma tecla est† sendo segurada pressionada */
                            DWORD status_teclas_controle; /* CAPSLOCK_ON, ENHANCED_KEY (insert, delete, home, end, pg up, pg downl,
						                                   setas de direá∆o, etc), LEFT_ALT_PRESSED, LEFT_CTRL_PRESSED,
						                                   NUMLOCK_ON, RIGHT_ALT_PRESSED, RIGHT_CTRL_PRESSED, SCROLLLOCK_ON,
								 						   SHIFT_PRESSED */
                            } TECLADO;

 /* Detalhes desta estrutura, ver link:
    http://msdn.microsoft.com/en-us/library/windows/desktop/ms684239%28v=vs.85%29.aspx */
    typedef struct T_MOUSE{
                          DWORD botao_pressionado; /* FROM_LEFT_1ST_BUTTON_PRESSED, FROM_LEFT_2ND_BUTTON_PRESSED, FROM_LEFT_3RD_BUTTON_PRESSED,
                                                      FROM_LEFT_4TH_BUTTON_PRESSED, RIGHTMOST_BUTTON_PRESSED */
		 				  DWORD botao_clicou;      /* se o bot∆o tiver sido liberado, ap¢s ter sido pressionado */
                          COORD posicao; /* coordenadas (em forma de cÇlulas de caracteres e n∆o de pixels) do cursor do
						                    mouse em termos do tamanho (em linhas e colunas) do buffer
							 			    de console que estiver definido para a janela */
                          DWORD status_teclas_controle; /* CAPSLOCK_ON, ENHANCED_KEY (insert, delete, home, end, pg up, pg downl,
						                                   setas de direá∆o, etc), LEFT_ALT_PRESSED, LEFT_CTRL_PRESSED,
						                                   NUMLOCK_ON, RIGHT_ALT_PRESSED, RIGHT_CTRL_PRESSED, SCROLLLOCK_ON,
							 							   SHIFT_PRESSED */
						  DWORD flags_qual_evento_mouse; /* DOUBLE_CLICK, MOUSE_HWHEELED, MOUSE_MOVED, MOUSE_WHEELED */
                          } MOUSE;

 /* Evento que pode ter acontecido e que Ç identificado pela funá∆o Evento() */
    typedef struct T_EVENTO{
                           WORD tipo_evento; /* pode ser MOUSE_EVENT ou KEY_EVENT */
		  				   TECLADO teclado; /* caso tenha ocorrido um KEY_EVENT, ent∆o esta estrutura ser† prenchida
						                    com os dados correspondentes */
						   MOUSE mouse;    /* caso tenha ocorrido um MOUSE_EVENT, ent∆o esta estrutura ser† prenchida
						                    com os dados correspondentes */
                           }EVENTO;


/****************************************************************************************************************/
/*                                  FIM DAS DECLARAÄÂES DE ESTRUTURAS E ENUMERAÄÂES                             */
/****************************************************************************************************************/





/****************************************************************************************************************/
/*                                IN÷CIO DAS DECLARAÄÂES DOS PROT‡TIPOS DAS FUNÄÂES                             */
/****************************************************************************************************************/

 /*****************************************************************************************************************
  Descriá∆o: imprime a mensagem do tipo LPSTR (ponteiro para uma string) juntamente com o c¢digo do £ltimo erro
             ocorrido no programa obtido do fluxo de erro (stderr) e encerra o programa.
  ParÉmetros de entrada:
   -> Vari†vel do tipo LPSTR: uma mensagem a ser impressa na tela.
  Retorno da funá∆o:
   -> Nenhum.
 *****************************************************************************************************************/
 void ErrorExit (LPSTR);




 /*****************************************************************************************************************
  Descriá∆o: permitir e identificar com todos os detalhes, eventos origin†rios do teclado e/ou do mouse.
  ParÉmetros de entrada:
   -> Nenhum.
  Retorno da funá∆o:
   -> Estrutura EVENTO:
      - Campo "tipo_evento" que Ç do tipo WORD (inteiro sem sinal de 2 bytes):
	      -> Valor MOUSE_EVENT: significa que o evento lido do buffer da janela de console Ç um evento origin†rio do
		                       MOUSE;
		  -> Valor KEY_EVENT: significa que o evento lido do buffer da janela de console Ç um evento origin†rio do
		                     TECLADO;
		  -> Observaá∆o 1: esta funá∆o descarta os eventos FOCUS_EVENT, MENU_EVENT e WINDOW_BUFFER_SIZE_EVENT.
		                   Caso a identificaá∆o de algum desses eventos seja necess†rio, a funá∆o deve ser
			 			   estendida para que armazene neste campo o valor correspondente a um desses 3 eventos;
          -> Observaá∆o 2: o campo "tipo_evento" Ç um campo de bits. Isto Ç, cada um dos valores indicados
		                   est† associado a um bit do campo. Portanto, a identificaá∆o de qual valor est† armazenado
                           no campo deve ser feito por meio dos operadores bit-a-bit.
						   Exemplo: EVENTO e;
						            e = Evento();
						            if (e.tipo_evento & MOUSE_EVENT) printf("Foi gerado um evento pelo mouse");
						            if (e.tipo_evento & KEY_EVENT) printf("Foi gerado um evento pelo teclado");
	  - Campo "teclado" que Ç uma estrutura do tipo TECLADO: se o campo "tipo_evento" contiver um valor KEY_EVENT
	                                                         ent∆o esta estrutura conter† todos os dados relativos
															 a esse evento. Caso contr†rio, os valores contidos
															 nesta estrutura n∆o tem sentido e, portanto, n∆o devem
 															 ser utilizados.
	      -> Campo "status_tecla" do tipo enumeraá∆o: armazena se o evento do teclado foi o pressionamento
		                                              ou a liberaá∆o de uma tecla.
		     - Valor LIBERADA: evento corresponde Ö liberaá∆o do pressionamento de uma tecla;
			 - Valor PRESSIONADA: evento corresponde ao pressionamento de uma tecla.
		  -> Campo "key_code" do tipo WORD: contem um valor inteiro £nico independente do tipo do teclado para
		                                    cada uma das teclas do teclado.
		     - Observaá∆o:
			   Recomenda-se o uso das constantes definidas no in°cio deste arquivo (#defines) para
			   referenciar as teclas, ao invÇs da escrita no programa do pr¢prio c¢digo da tecla.
		  -> Campo "scan_code" do tipo WORD: c¢digo numÇrico que identifica uma tecla de acordo com o valor gerado 
		                                     pelo hardware de teclado (Ç dependente do tipo do teclado)
		  -> Campo "ascii_code": contÇm a convers∆o do valor key_code para o caracter correspondente na tabela ASCII,
								 considerando o estado do teclado (shift, caps-lock, etc., pressionadas). Faz a convers∆o considerando a linguagem atual e o layout do teclado f°sico presente.
		  -> Campo "repeat_count": contÇm um n£mero que indica que uma tecla est† sendo mantida pressionada. Por exemplo, 
								   quando uma tecla Ç mantida pressionada, vocà pode receber 5 eventos com este campo contendo o valor 1, ou um evento com este campo contendo o valor 5, ou m£ltiplos eventos com este campo contendo valores maiores ou iguais a 1. O valor que conter† essa vari†vel depender† da velocidade com que a ler†.
								   
								   Exemplo de um c¢digo:								   
								   EVENTO e;
		
								   do
								   {
										e = Evento();
										if (e.tipo_evento & KEY_EVENT)
										{
											printf("codigo: %c\n", e.teclado.ascii_code);
											printf("contagem: %d\n", e.teclado.repeat_count);
										}	
								   }
								   while(1);
								   Experimente executar o programa e segurar uma tecla pressionada. Ver† que "repeat_count" sempre ter† valor 1, pois est† sendo lido rapidamente o valor colocado no campo "repeat_count". Agora, se colocar a linha Sleep(1000), dentro do if, ver† que o valor armazenado em repeat_count mudar†, pois o Sleep() bloquear† a execuá∆o do programa e, quando for impresso o valor de "repeat_count", ele j† ter† valores maiores do que 1, indicando que a tecla foi segurada pressionada por um tempo.
		  
									Observaá∆o: pode configurar a velocidade do teclado se chamar a funá∆o SystemParametersInfoA com o parÉmetro SPI_SETKEYBOARDSPEED. Essa funá∆o permite definir a taxa de repetiá∆o do teclado. Pode ser especificado um valor no intervalo de 0 (aproximadamente 2.5 repetiá‰es por segundo) atÇ 31 (aproximadamente 30 repetiá‰es por segundo). A taxa de repetiá∆o de fato, depende do hardaware e pode vairar em uma escala linear de 20%. Com base nisso, ver† que, ao colocar Sleep(1000) no programa anterior, ver† que o valor de "repeat_count", n∆o ultrapassar† o valor de 30/31.
		  -> Campo "status_teclas_controle" do tipo DWORD (4 bytes): contem o status das diversas teclas de
		                                                             controle.
             - Valor CAPSLOCK_ON: a luz da tecla CAPSLOCK est† ligada;
             - Valor ENHANCED_KEY: a tecla pressionada Ç uma tecla estendida (INSERT, DELETE, HOME, END, PG UP,
			                       PG DOWN, SETAS DE DIREÄ«O, etc.);
             - Valor LEFT_ALT_PRESSED: a tecla ALT da esquerda est† pressionada;
             - Valor LEFT_CTRL_PRESSED: a tecla CTRL da esquerda est† pressionada;
             - Valor NUMLOCK_ON: a luz da tecla NUMLOCK est† ligada;
             - Valor RIGHT_ALT_PRESSED: a tecla ALT da direita est† pressionada;
             - Valor RIGHT_CTRL_PRESSED: a tecla CTRL da direita est† pressionada;
             - Valor SCROLLLOCK_ON: a luz da tecla SCROLLLOCK est† ligada;
             - Valor SHIFT_PRESSED: uma, ou mesmo ambas, as teclas SHIFT est∆o pressionadas.
			 - Valor SHIFT_ESQUERDO_PRESSIONADO: se foi pressionada a tecla de SHIFT ESQUERDA;
			 - Valor SHIFT_DIREITO_PRESSIONADO: se foi pressionada a tecla de SHIFT DIREITO;
             -> Observaá∆o:
			    Este campo "status_teclas_controle" Ç um campo de bits. Isto Ç, cada um dos valores indicados
		        est† associado a um bit do campo. Portanto, a identificaá∆o de qual valor est† armazenado
                no campo deve ser feito por meio dos operadores bit-a-bit.
				Exemplo: EVENTO e;
				         e = Evento();
				         if (e.teclado.status_teclas_controle & CAPSLOCK_ON) printf("A luz da tecla CAPSLOCK est† acessa");
	  - Campo "mouse" que Ç uma estrutura do tipo MOUSE:
          -> Campo "botao_pressionado" do tipo DWORD:
             - Valor FROM_LEFT_1ST_BUTTON_PRESSED: primeiro bot∆o da esquerda pressionado;
			 - Valor FROM_LEFT_2ND_BUTTON_PRESSED: segundo bot∆o da esquerda pressionado;
			 - Valor RIGHTMOST_BUTTON_PRESSED: bot∆o mais Ö direita pressionado.
             -> Observaá∆o 1:
			    Este campo "botao_pressionado" Ç um campo de bits. Isto Ç, cada um dos valores indicados est†
				associado a um bit do campo. Portanto, a identificaá∆o de qual valor est† armazenado no campo deve
				ser feito por meio dos operadores bit-a-bit.
			    Exemplo: EVENTO e;
				         e = Evento();
				         if (e.mouse.botao_pressionado & RIGHTMOST_BUTTON_PRESSED)
						     printf("O bot∆o da direita est† pressionado");
             -> Observaá∆o 2:
			    Foram definidas, na seá∆o "DEFINES e CONSTANTES", constantes em portuguàs, para os bot‰es esquerdo
                e direito do mouse, que podem ser utilizadas ao invÇs dos valores anteriores para aumentar
				a legibilidade do c¢digo:
				- BOTAO_ESQUERDO_PRESSIONADO
                - BOTAO_DIREITO_PRESSIONADO
             -> Observaá∆o 3:
			    Embora o "windows.h" colete e disponibilize informaá‰es para mais dois bot‰es que porventura o
				mouse tenha (constantes FROM_LEFT_3RD_BUTTON_PRESSED e FROM_LEFT_4TH_BUTTON_PRESSED, correspondentes
				ao terceiro e quarto bot‰es da esquerda, respectivamente), esta funá∆o ignora esses valores. Portanto,
				caso seja necess†rio essa identificaá∆o, a funá∆o deve ser estendida nesse aspecto.
		  -> Campo "botao_clicou" do tipo DWORD: contÇm se o evento foi a liberaá∆o de algum dos bot‰es do mouse
		                                         que previamente estavam pressionados, definindo um clique do mouse.
             - Valor FROM_LEFT_1ST_BUTTON_RELEASED: primeiro bot∆o da esquerda foi liberado (clicou);
			 - Valor FROM_LEFT_2ND_BUTTON_RELEASED: segundo bot∆o da esquerda foi liberado (clicou);
			 - Valor RIGHTMOST_BUTTON_RELEASED: bot∆o mais Ö direita foi liberado (clicou).
             -> Observaá∆o 1:
			    Este campo "botao_clicou" Ç um campo de bits. Isto Ç, cada um dos valores indicados est†
				associado a um bit do campo. Portanto, a identificaá∆o de qual valor est† armazenado no campo deve
				ser feito por meio dos operadores bit-a-bit.
			    Exemplo: EVENTO e;
				         e = Evento();
				         if (e.mouse.botao_clicou & RIGHTMOST_BUTTON_RELEASED)
						     printf("O bot∆o da direita clicou/foi liberado");
             -> Observaá∆o 2:
			    Foram definidas, na seá∆o "DEFINES e CONSTANTES", constantes em portuguàs, para os bot‰es esquerdo
                e direito do mouse, que podem ser utilizadas ao invÇs dos valores anteriores para aumentar
				a legibilidade do c¢digo:
				- BOTAO_ESQUERDO_LIBERADO
                - BOTAO_DIREITO_LIBERADO
          -> Campo "posicao" que Ç uma estrutura do tipo COORD: guarda as coordenadas (x,y) na janela de console em
                                                                que ocorreu o evento do mouse. As coordenadas s∆o
																dadas em posiá‰es de caracteres e n∆o de pixels.
			 - Campo X: coluna da janela de console em que ocorreu o evento do mouse;
             - Campo Y: linha da janela de console em que ocorreu o evento do mouse.

		  -> Campo "status_teclas_controle" do tipo DWORD: contem o status das diversas teclas de controle, quando
		                                                   ocorreu o evento do mouse.
             - Valor CAPSLOCK_ON: a luz da tecla CAPSLOCK est† ligada;
             - Valor ENHANCED_KEY: a tecla pressionada Ç uma tecla estendida (INSERT, DELETE, HOME, END, PG UP,
			                       PG DOWN, SETAS DE DIREÄ«O, etc.);
             - Valor LEFT_ALT_PRESSED: a tecla ALT da esquerda est† pressionada;
             - Valor LEFT_CTRL_PRESSED: a tecla CTRL da esquerda est† pressionada;
             - Valor NUMLOCK_ON: a luz da tecla NUMLOCK est† ligada;
             - Valor RIGHT_ALT_PRESSED: a tecla ALT da direita est† pressionada;
             - Valor RIGHT_CTRL_PRESSED: a tecla CTRL da direita est† pressionada;
             - Valor SCROLLLOCK_ON: a luz da tecla SCROLLLOCK est† ligada;
             - Valor SHIFT_PRESSED: uma, ou mesmo ambas, as teclas SHIFT est∆o pressionadas;
			 - Valor SHIFT_ESQUERDO_PRESSIONADO: se foi pressionada a tecla de SHIFT ESQUERDA;
			 - Valor SHIFT_DIREITO_PRESSIONADO: se foi pressionada a tecla de SHIFT DIREITO;
             -> Observaá∆o:
			    O campo "status_teclas_controle" Ç um campo de bits. Isto Ç, cada um dos valores indicados
		        est† associado a um bit do campo. Portanto, a identificaá∆o de qual valor est† armazenado
                no campo deve ser feito por meio dos operadores bit-a-bit.
				Exemplo: EVENTO e;
				         e = Evento();
				         if (e.teclado.status_teclas_controle & CAPSLOCK_ON) printf("A luz da tecla CAPSLOCK est† acessa");
		  -> Campo "flags_qual_evento_mouse" do tipo DWORD: identifica qual o tipo de evento do mouse que ocorreu.
             - Valor DOUBLE_CLICK: o segundo clique (pressionado de bot∆o de um duplo-clique ocorreu.
               * Observaá∆o: o primeiro clique Ç retornado como um evento normal de pressionamento de bot∆o.
             - Valor MOUSE_HWHEELED:  a roda de rolagem horizontal do mouse foi girada.
			   * Observaá∆o: se a HIGH WORD do campo "botao_pressionado" contiver um valor positivo, ent∆o a roda foi
			                 girada para a direita. Caso contr†rio, a roda foi girada para a esquerda.
			                 Exemplo de identificaá∆o: EVENTO e;
                                                       e = Evento();
                                                       if( (int)e.mouse.botao_pressionado > 0)
                                                          printf("A roda do mouse foi girada para a direita");
                                                       else
                                                          printf("A roda do mouse foi girada para a esquerda");
             - Valor MOUSE_MOVED: ocorreu uma mudanáa na posiá∆o do mouse;
             - Valor MOUSE_WHEELED: a roda de rolagem vertical do mouse foi girada.
			   * Observaá∆o: se a HIGH WORD do campo "botao_pressionado" contiver um valor positivo, ent∆o a roda foi
			                 girada para a frente. Caso contr†rio, a roda foi girada para tr†s.
			                 Exemplo de identificaá∆o: EVENTO e;
                                                       e = Evento();
                                                       if( (int)e.mouse.botao_pressionado > 0)
                                                          printf("A roda do mouse foi girada para frente");
                                                       else
                                                          printf("A roda do mouse foi girada para tr†s");
  Observaá‰es:
   a) Deve ser dada preferància ao uso desta funá∆o ao invÇs da funá∆o getch();
   b) Ver a declaraá∆o da estrutura EVENTO na seá∆o anterior denominada "DECLARAÄÂES DE ESTRUTURAS E ENUMERAÄÂES".
   c) Ver a declaraá∆o da estrutura COORD na seá∆o anterior denominada "DECLARAÄÂES DE ESTRUTURAS E ENUMERAÄÂES".
   d) Ver a declaraá∆o da estrutura TECLADO na seá∆o anterior denominada "DECLARAÄÂES DE ESTRUTURAS E ENUMERAÄÂES";
   e) Ver a declaraá∆o da estrutura MOUSE na seá∆o anterior denominada"DECLARAÄÂES DE ESTRUTURAS E ENUMERAÄÂES".
   f) O tipo WORD Ç um inteiro sem sinal longo de 2 bytes definido na "windows.h";
   g) O tipo DWORD Ç um inteiro sem sinal longo de 4 bytes definido na "windows.h";
   h) Os tipos comuns definidos na "windows.h" podem ser consultados em:
      http://msdn.microsoft.com/en-us/library/cc230309.aspx
 *****************************************************************************************************************/
 EVENTO Evento(void);





/*****************************************************************************************************************
  Descriá∆o: obter as cores de fundo e do texto definidas para a janela de console
  ParÉmetros de entrada:
   -> Nenhum.
  Retorno da funá∆o:
   -> Estrutura CORES:
      - Campo CorTexto: cor definida para a escrita de na janela de console.
	  - Campo CorFundo: cor definida para o fundo de qualquer caracteres escrito na
	                    janela de console

  Observaá∆o:
   -> Ver a declaraá∆o da estrutura CORES na seá∆o anterior denominada
      "DECLARAÄÂES DE ESTRUTURAS E ENUMERAÄÂES".
 *****************************************************************************************************************/
 CORES getCoresJanela(void);




 /*****************************************************************************************************************
  Descriá∆o: obter as coordenadas atuais da janela de console na tela.
  ParÉmetros de entrada:
   -> Nenhum.
  Retorno da funá∆o:
   -> Estrutura COORD:
      - Campo X representa a linha do pixel da borda superior da janela de console.
      - Campo Y representa a coluna do pixel da borda esquerda da janela de console

  Observaá‰es:
   a) A estrutura COORD Ç inclu°da por meio do arquivo cabeáalho "windows.h". Contudo, a sua declaraá∆o
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que Ç inclu°do o arquivo
	  cabeáalho "windows.h".
   b) Em outras palavras, retorna as coodenadas (x,y) do pixel do canto superior
      esquerdo da janela de console.
 *****************************************************************************************************************/
 COORD getPosicaoJanela(void);
 


 
 /*****************************************************************************************************************
  Descriá∆o: obter a resoluá∆o do monitor em pixels:
  ParÉmetros de entrada:
   -> Nenhum.
  Retorno da funá∆o:
   -> Estrutura COORD:
      - Campo X representa o n£mero de pixels da largura
      - Campo Y representa o n£mero de pixels da altura

  Observaá∆o:
   -> A estrutura COORD Ç inclu°da por meio do arquivo cabeáalho "windows.h". Contudo, a sua declaraá∆o
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que Ç inclu°do o arquivo
	  cabeáalho "windows.h".
 *****************************************************************************************************************/
 COORD getResolucaoMonitor(void);




 /*****************************************************************************************************************
  Descriá∆o: obter, em n£mero de pixels, as dimens‰es horizontal e vertical da fonte da janela do console.
  ParÉmetros de entrada:
   -> Nenhum.
  Retorno da funá∆o:
   -> Estrutura COORD:
      - Campo X representa a quantidade de pixels na horizontal ocupada por um caractere na janela do console.
      - Campo Y representa a quantidade de pixels na vertical ocupada por um caractere na janela do console.

  Observaá∆o:
   -> A estrutura COORD Ç inclu°da por meio do arquivo cabeáalho "windows.h". Contudo, a sua declaraá∆o
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que Ç inclu°do o arquivo
	  cabeáalho "windows.h".
 *****************************************************************************************************************/
 COORD getTamanhoFonteConsole(void);




 /*****************************************************************************************************************
  Descriá∆o: obter o t°tulo da janela de console.
  ParÉmetros de entrada:
   -> Nenhum.
   Retorno da funá∆o:
   -> Um ponteiro ponteiro para o endereáo da string contendo o t°tulo da janela, ou NULL se a janela
      n∆o tiver um t°tulo
 *****************************************************************************************************************/
 char *getTituloConsole(void);




 /*****************************************************************************************************************
  Descriá∆o: obter se h† algum evento (teclado, mouse, ou redimensionamento da janela) no buffer de eventos
             da janela de console.
  ParÉmetros de entrada:
   -> Enumeraá∆o TYPE_HIT:
      - Valor KEYBOARD_HIT: identificar somente os eventos origin†rios do teclado;
	  - Valor MOUSE_HIT: identificar somente os eventos origin†rios do mouse;
	  - Valor ALL: identificar qualquer evento presente no buffer de eventos da janela de console, sejam
	               oriundos do teclado, do mouse, ou do redimensionamento da janela.
  Retorno da funá∆o:
   -> Um valor inteiro:
      - Valor 0: n∆o h† eventos do tipo solicitado no parÉmetro da funá∆o no buffer de eventos da janela de
	             console;
	  - Valor 1: h† um ou mais eventos do tipo solicitado no parÉmetro da funá∆o no buffer de eventos
	             da janela de console.

  Observaá∆o:
   -> Ver a declaraá∆o da enumeraá∆o TYPE_HIT na seá∆o anterior denominada
      "DECLARAÄÂES DE ESTRUTURAS E ENUMERAÄÂES".
 *****************************************************************************************************************/
 int hit(TYPE_HIT);




/*****************************************************************************************************************
  Descriá∆o: apresentaá∆o detalhada de todas as informaá‰es poss°veis de serem coletadas sobre um determinado evento
             ocorrido, cuja origem seja, ou o teclado, ou o mouse.
  ParÉmetros de entrada:
   -> Vari†vel do tipo da estrutura EVENTO:
      - Essa vari†vel deve conter os dados do evento lido anteriormente sobre o qual ser∆o coletadas as informaá‰es;
	  - Ver descriá∆o do conte£do dos campos da estrutura EVENTO na funá∆o Evento();
	  - Exemplo de c¢digo: EVENTO e;
	                       e = Evento();
						   IdentificarEvento(e, MAXIMO);
   -> N£mero inteiro que pode ser dois valores:
      - Valor 0: apresentar na tela o m°nimo de informaá‰es sobre o evento passado como parÉmetro;
	  - Valor 1: apresentar na tela o m†ximo de informaá‰es (todas as poss°veis) sobre o evento passado como parÉmetro;
	  -> Observaá∆o:
	     Foram definidas duas constantes do tipo DEFINE para este parÉmetro, em substituiá∆o ao valores numÇricos 0 e 1.
		 Constantes MINIMO e MAXIMO, correspondente aos valores 0 e 1, respectivamente.
  Retorno da funá∆o:
   -> Nenhum.

  Observaá∆o:
   -> Ver a declaraá∆o da estrutura EVENTO na seá∆o anterior denominada "DECLARAÄÂES DE ESTRUTURAS E ENUMERAÄÂES".
 *****************************************************************************************************************/
 void IdentificarEvento(EVENTO, int);




 /*****************************************************************************************************************
  Descriá∆o: obter as dimens‰es m†ximas poss°veis de uma janela na resoluá∆o atual
             do monitor em pixels.
  ParÉmetros de entrada:
   -> Nenhum.
  Retorno da funá∆o:
   -> Estrutura COORD:
     - Campo X representa o n£mero de caracteres da largura
     - Campo Y representa o n£mero de caracteres da altura

  Observaá‰es:
   a) A estrutura COORD Ç inclu°da por meio do arquivo cabeáalho "windows.h". Contudo, a sua declaraá∆o
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que Ç inclu°do o arquivo
	  cabeáalho "windows.h".
   b) Para poder utilizar esta funá∆o Ç necess†rio fazer uma correá∆o no arquivo WINCON.H do gcc.
      Isso porque esta funá∆o MaxDimensaoJanela(void) utiliza a funá∆o da API do Windows
	  denominada GetCurrentConsoleFont() que somente est† dispon°vel no Windows XP em diante e
 	  por isso o gcc n∆o incluiu esse cabeáalho (embora exista sua implementaá∆o no ".lib" do gcc).
      - CORREÄ«O A SER FEITA:
	    Caso n∆o exista, deve adicionar a seguinte linha no arquivo "wincon.h":
	         BOOL WINAPI GetCurrentConsoleFont(HANDLE, BOOL, PCONSOLE_FONT_INFO);
	  - ONDE DEVE SER ACRESCENTADA ESSA LINHA NO ARQUIVO "wincon.h":
        1) No arquivo "wincon.h" que est† localizado dentro do diret¢rio "include" da sua instalaá∆o do gcc for Windows
	    2) A linha indicada deve ser adicionada dentro do define (caso n∆o exista, crie ele)
		     #if (_WIN32_WINNT >= 0x0500)
		          BOOL WINAPI GetCurrentConsoleFont(HANDLE, BOOL, PCONSOLE_FONT_INFO);
		          ... -> mantenha tudo o que j† existir anteriormente definido dentro do define
		     #endif
 *****************************************************************************************************************/
 COORD MaxDimensaoJanela(void);




 /*****************************************************************************************************************
  Descriá∆o: ligar ou desligar o cursor piscante na janela de console.
  ParÉmetros de entrada:
   -> Uma string contendo o novo t°tulo da janela de console.
  Retorno da funá∆o:
   -> Enumeraá∆o STATUS:
      - Valor DESLIGAR: desligar o cursor piscante na janela de console;
	  - Valor LIGAR: ligar o cursos piscante na janela de console.

  Observaá∆o:
   -> Ver a declaraá∆o da enumeraá∆o STATUS na seá∆o anterior denominada
      "DECLARAÄÂES DE ESTRUTURAS E ENUMERAÄÂES".
 *****************************************************************************************************************/
 void setCursorStatus(STATUS);




 /*****************************************************************************************************************
  Descriá∆o: funá∆o que permite redimensionar a janela de console.
  ParÉmetros de entrada:
   -> Estrutura COORD:
      - Campo X representa o n£mero de caracteres da nova largura da janela
      - Campo Y representa o n£mero de caracteres da nova altura da janela
  Retorno da funá∆o:
   -> Nenhum.

  Observaá∆o:
   - Recomenda-se que obtenha os valores m†ximos poss°veis para o redimensionamento
     da janela do console por meio de uma chamada Ö funá∆o MaxDimensaoJanela(). Desse
     modo, conseguir† garantir que os valores passados como parÉmetros para esta funá∆o
     n∆o ultrapassar† os valores m†ximos poss°veis de redimensionamento da janela do
     console.
 *****************************************************************************************************************/
 void setDimensaoJanela(int largura, int altura);




 /*****************************************************************************************************************
  Descriá∆o: esconder ou tornar vis°vel a Barra de Tarefas da †rea de trabalho do Windows.
  ParÉmetros de entrada:
   -> Enumeraá∆o VISIBILIDADE:
      - Valor VISIVEL: tornar vis°vel a Barra de Tarefas;
      - Valor INVISIVEL: esconder a Barra de Tarefas.
  Retorno da funá∆o:
   -> Nenhum.

  Observaá∆o:
   -> Ver a declaraá∆o da enumeraá∆o VISIBILIDADE na seá∆o anterior denominada
      "DECLARAÄÂES DE ESTRUTURAS E ENUMERAÄÂES".
 *****************************************************************************************************************/
 void setEstadoBarraTarefas(VISIBILIDADE);




/*****************************************************************************************************************
  Descriá∆o: posicionar a janela em uma determinada posiá∆o na tela.
  ParÉmetros de entrada:
   -> Estrutura COORD:
      - Campo X representa a linha do pixel da borda superior da janela de console.
      - Campo Y representa a coluna do pixel da borda esquerda da janela de console
  Retorno da funá∆o:
   -> Nenhum.
 *****************************************************************************************************************/
 void setPosicaoJanela(int top, int left);




 /*****************************************************************************************************************
  Descriá∆o: definir um titulo para a janela de console.
  ParÉmetros de entrada:
   -> Uma string contendo o novo t°tulo da janela de console.
  Retorno da funá∆o:
   -> Nenhum.
 *****************************************************************************************************************/
 void setTituloConsole(char *);




 /*****************************************************************************************************************
  Descriá∆o: obter o tamanho da janela de console atual em quantidade de caracteres.
  ParÉmetros de entrada:
   -> Nenhum.
  Retorno da funá∆o:
   -> Estrutura COORD:
      - Campo X representa a largura da janela de console em n£mero de caracteres
      - Campo Y representa a altura da janela de console em n£mero de caracteres

  Observaá∆o:
   -> A estrutura COORD Ç inclu°da por meio do arquivo cabeáalho "windows.h". Contudo, a sua declaraá∆o
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que Ç inclu°do o arquivo
	  cabeáalho "windows.h".
 *****************************************************************************************************************/
 COORD tamanhoJanelaConsole(void);




/****************************************************************************************************************/
/*                                  FIM DAS DECLARAÄÂES DOS PROT‡TIPOS DAS FUNÄÂES                              */
/****************************************************************************************************************/

#endif
