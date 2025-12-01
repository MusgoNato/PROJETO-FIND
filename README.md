# PROJETO FIND

![GitHub repo size](https://img.shields.io/github/repo-size/iuricode/README-template?style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/iuricode/README-template?style=for-the-badge)
![GitHub forks](https://img.shields.io/github/forks/iuricode/README-template?style=for-the-badge)

<img src="/video-programa/video.gif" alt="Programa Rodando">

> Projeto de buscas recursivas em pastas e subpastas. O programa percorre todas as pastas dado um endere«ıo inicial para varredura. O programa ainda permite a busca de sequ«¶ncias de caracteres dentro de um arquivo, imprimindo em que linha foi encontrada a sequ«¶ncia.

## –Y'Ø Pr«∏-requisitos

Antes de come«ıar, verifique se voc«¶ atendeu aos seguintes requisitos:

- Voc«¶ instalou a vers«úo mais recente da linguagem `<C>`
- Voc«¶ instalou a vers«úo mais recente do `<GCC>`
- Voc«¶ tem uma m«≠quina `<Windows / Linux / Mac>`.

## –Ys? Veja o Projeto

Siga estas etapas:

- Baixe os arquivos do reposit«¸rio.
- Instale o gcc mais recente para compilar e executar o programa.
- Abra o CMD na pasta aonde foi baixado o reposit«¸rio e insira os seguintes comandos para compilar e executar o c«¸digo:

Compila«ı«úo:

``` 
gcc find.c -o find.exe funcoes.c conio_v3.2.4.c console_v1.5.5.c -Wall -pedantic -Wextra -Werror

```

Execu«ı«úo:

```
find "C:\Program Files"
```

## É"˚ã˜? Funcionamento do Programa

O programa na linha de execu«ı«úo aceita 3 argumentos al«∏m do execut«≠vel do programa. Caso seja passado menos argumentos o programa n«úo rodar«≠ imprimindo uma mensagem de erro.

```
[NOME] [DIRET«"RIO] [ARQUIVO] [SEQU«SNCIA].
```
* NOME: Referente ao nome do programa.
* DIRET«"RIO: Referente ao diret«¸rio inicial para a varredura.
* ARQUIVO: Referente ao arquivo a ser buscado dentro do diret«¸rio passado inicialmente.
* SEQU«SNCIA: Referente a sequ«¶ncia de caracteres a serem buscados dentro do arquivo informado.


Obs: Caso o diret«¸rio, arquivo a ser buscado ou a sequ«¶ncia a ser buscada possuam caracteres espa«ıos em branco, deve se passar entre "" a pasta, arquivo ou sequ«¶ncia.

Exemplo:

```
find "C:\Program Files" ex.txt "ola mundo!"
```


## –Yœ? Desenvolvedor
<table>
    <td align="center">
      <a href="https://github.com/MusgoNato" title="Perfil Github">
        <img src="https://avatars.githubusercontent.com/u/131496781?v=4" width="100px;" alt="Foto do Hugo"/><br>
        <sub>
          <b>Hugo Josu«∏ Lema Das Neves</b>
        </sub>
      </a>
    </td>
  </tr>
</table>

## Refer«¶ncias –Y"s
<table>
    <td align="center">
      <a href="https://www.comp.uems.br/~ricardo/PCII/" title="Link do Projeto">
        <sub>
          <b>A id«∏ia e bibliotecas utilizadas no projeto foram pegas da disciplina de Programa«ı«úo de Computadores II do Prof Dr Ricardo Luis Lachi</b>
        </sub>
      </a>
    </td>
  </tr>
</table>