# Trabalho2-ED

Guia de utilização Git e GitHub: [Notion - Git e GitHub](https://cerulean-papaya-41b.notion.site/Git-e-GitHub-872aa24d4e724846a2bf74b12f2975d0?pvs=4)

Pasta de fotos: [Google Fotos](https://drive.google.com/drive/folders/1yDnofym7c58yfE7_7hulKpd_RbGvPCDZ)

## Visão Geral
### Estruturação dos arquivos
<img src="https://github.com/laraguilar/Trabalho2-ED/assets/72893552/87494093-03c5-473b-aa5f-ed6d4d110e3f" height="300px"/>


**base:** Contém a base das imagem dentro da pasta 'img', separando-as por pastas de cada localidade. Também possui uma pasta para cada localidade contendo arquivos de cada imagem sobre suas respectivas informações fornecidas pelo extrator.

**extrator:** Contém programas em python que quando executados pelo programa principal de extrator em C, usa o algoritmo SIFT para extrair as características de cada imagem.

**query:** Contém informações sobre a imagem sendo consultada, após passar pelo extrator.

**results:** Contém informações dos endereços das 5 imagens definidas como mais similares à imagem consultada.

### Fluxograma básico
<img src="https://github.com/laraguilar/Trabalho2-ED/assets/72893552/61dc0e4d-ac87-4387-8e20-f1c74329ea89" height="100px"/>

Nosso sistema funciona em duas partes, sendo elas a indexação e a extração. Primeiro, temos a indexação das imagens que são realizadas para extrair e salvar as características da imagem de forma que no momento da busca, elas sejam utilizados como base para identificar as localidades mais parecidas. Essa indexação é armazenada dentro das pastas de extração (base/extractor_<NOME_DA_LOCALIDADE>).

Nosso programa de busca deve primeiro extrair as características da imagem selecionada, após isso, fará uma comparação com os índices do banco. Ele deverá salvar as **n** localidades mais parecidas e imprimir na tela. 

## Estrutura do Código

### Indexação
  Para a indexação, compilamos e executamos o arquivo index.c. Ele é responsável por percorrer todas as imagens do banco e realizar a extração dos descritores, que serão utilizados para futura busca. Essa etapa do projeto gera um arquivo .txt que será utilizado para mapear o caminho das imagens, seus respectivos descritores e a localidade referente.
  
  Os descritores são extraídos através de um código em python, executado através da chamada de sistema em C, que gera os descritores utilizando o método SIFT, através da biblioteca **OpenCV**. Para saber mais sobre ele [clique aqui](https://docs.opencv.org/4.x/da/df5/tutorial_py_sift_intro.html).

### Busca (query)



## Execução do programa

### Requisitos
  Utilizamos ambiente linux para o desenvolvimento do projeto. Caso deseje rodar o código, sugerimos que utilize o Sistema Operacional Linux ou utilize WSL2.
  
  [Guia de Instalação e Configuração WSL2](https://drive.google.com/drive/folders/1yDnofym7c58yfE7_7hulKpd_RbGvPCDZ)
  
  ***Não é necessário instalar o Docker***

  Certifique-se de que o compilador está instalado na sua máquina.

#### Execução:

##### 1º compila o arquivo list.c (será chamado pelo cabeçalho):
gcc -c list.c -o list.o

##### 2º compila o programa principal
gcc -c main.c -o main.o

##### 3º compila os dois juntos
gcc list.o main.o -o programa

##### 4º executa o programa
./programa


## Referências: 

https://medium.com/@akarshzingade/image-similarity-using-deep-ranking-c1bd83855978

https://www.cin.ufpe.br/~in1152/aulas/rec-imagem-por-conteudo.pdf

https://courses.cs.washington.edu/courses/cse576/07sp/notes/CBIR_white.pdf

https://en.wikipedia.org/wiki/Content-based_image_retrieval



