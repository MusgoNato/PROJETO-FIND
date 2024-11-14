# PROJETO FIND

![GitHub repo size](https://img.shields.io/github/repo-size/iuricode/README-template?style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/iuricode/README-template?style=for-the-badge)
![GitHub forks](https://img.shields.io/github/forks/iuricode/README-template?style=for-the-badge)

<img src="/video-programa/video.gif" alt="Programa Rodando">

> Projeto de buscas recursivas em pastas e subpastas. O programa percorre todas as pastas dado um endereço inicial para varredura. O programa ainda permite a busca de sequências de caracteres dentro de um arquivo, imprimindo em que linha foi encontrada a sequência.

## 💻 Pré-requisitos

Antes de começar, verifique se você atendeu aos seguintes requisitos:

- Você instalou a versão mais recente da linguagem `<C>`
- Você instalou a versão mais recente do `<GCC>`
- Você tem uma máquina `<Windows / Linux / Mac>`.

## 🚀 Veja o Projeto

Siga estas etapas:

- Baixe os arquivos do repositório.
- Instale o gcc mais recente para compilar e executar o programa.
- Abra o CMD na pasta aonde foi baixado o repositório e insira os seguintes comandos para compilar e executar o código:

Compilação:

``` 
gcc find.c -o find.exe funcoes.c conio_v3.2.4.c console_v1.5.5.c -Wall -pedantic -Wextra -Werror

```

Execução:

```
find "C:\Program Files"
```

## ℹ️ Funcionamento do Programa

O programa na linha de execução aceita 3 argumentos além do executável do programa. Caso seja passado menos argumentos o programa não rodará imprimindo uma mensagem de erro.

```
[NOME] [DIRETÓRIO] [ARQUIVO] [SEQUÊNCIA].
```
* NOME: Referente ao nome do programa.
* DIRETÓRIO: Referente ao diretório inicial para a varredura.
* ARQUIVO: Referente ao arquivo a ser buscado dentro do diretório passado inicialmente.
* SEQUÊNCIA: Referente a sequência de caracteres a serem buscados dentro do arquivo informado.


Obs: Caso o diretório, arquivo a ser buscado ou a sequência a ser buscada possuam caracteres espaços em branco, deve se passar entre "" a pasta, arquivo ou sequência.

Exemplo:

```
find "C:\Program Files" ex.txt "ola mundo!"
```


## 🤝 Desenvolvedor
<table>
    <td align="center">
      <a href="https://github.com/MusgoNato" title="Perfil Github">
        <img src="https://avatars.githubusercontent.com/u/131496781?v=4" width="100px;" alt="Foto do Hugo"/><br>
        <sub>
          <b>Hugo Josué Lema Das Neves</b>
        </sub>
      </a>
    </td>
  </tr>
</table>