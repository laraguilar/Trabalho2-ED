# Trabalho2-ED

Este projeto implementa um sistema de indexação e busca de imagens em uma base de dados. Ele utiliza métodos de extração de características para indexar as imagens e permite realizar consultas para encontrar imagens semelhantes. O código-fonte está escrito em C e Python.

Guia de utilização Git e GitHub: [Notion - Git e GitHub](https://cerulean-papaya-41b.notion.site/Git-e-GitHub-872aa24d4e724846a2bf74b12f2975d0?pvs=4)

Pasta de fotos: [Google Fotos](https://drive.google.com/drive/folders/1yDnofym7c58yfE7_7hulKpd_RbGvPCDZ)

## Funcionalidades
  O sistema possui as seguintes funcionalidades:
  - Indexação de Imagens: O programa realiza a indexação das imagens da base de dados, extrai suas características e armazena os índices em pastas de extração. Ele utiliza uma lista encadeada para armazenar as informações das imagens, incluindo nome, localidade, descritor e caminho.


  - Busca de Imagens: O programa permite realizar consultas para encontrar imagens semelhantes com base em uma imagem de referência. Ele extrai as características da imagem consultada, compara com os índices armazenados e seleciona as 5 localidades mais parecidas. O resultado da busca é exibido na tela.


## Visão Geral
### Estruturação dos arquivos
<img src="https://github.com/laraguilar/Trabalho2-ED/assets/72893552/87494093-03c5-473b-aa5f-ed6d4d110e3f" height="300px"/>

### Fluxograma básico
<img src="https://github.com/laraguilar/Trabalho2-ED/assets/72893552/61dc0e4d-ac87-4387-8e20-f1c74329ea89" width="600px"/>

Primeiro, vamos realizar a indexação das imagens da nossa base através da indexação, utilizando métodos de extração de características.
Nosso programa deve conter uma lista encadeada contendo a estrutura da imagem. A princípio, fará parte da estrutura os atributos nome da imagem, localidade, descritor e caminho, sendo que estes podem sofrer alteração com o decorrer do projeto. Essa indexação é armazenada dentro das pastas de extração (base/extractor_n).
Nosso programa de busca deve primeiro extrair as características da imagem selecionada, após isso, fará uma comparação com os índices do banco. Ele deverá selecionar as 5 localidades mais parecidas e imprimir na tela. 

## Estrutura do Código
index.c:

  Arquivo é responsável pela indexação das imagens. Nele foram implentadas as funções:
  generateImagesList: lê o arquivo de índice e preenche uma lista de imagens com informações sobre as imagens, seus descritores e localidades.
  createDescriptor: gera o descritor para uma imagem usando um programa externo em Python.
  getDescriptorPath: retorna o caminho completo do descritor de uma imagem.
  No main, o arquivo abre o arquivo de índice, chama generateImagesList para preencher a lista de imagens, itera sobre a lista de imagens e chama createDescriptor para gerar o descritor de cada imagem.

query.c:

  Arquivo é responsável pela busca de imagens. Nele foi implementada a função query que será usada para realizar a busca comparando os descritores.
  No main, o arquivo lê os argumentos da linha de comando, cria uma lista de imagens, chama generateImagesList para preencher a lista de imagens, chama createDescriptor para gerar o descritor da imagem de consulta e chama a função match_images para realizar a correspondência entre os descritores.

list.c: Contém a implementação das funções relacionadas à lista encadeada das imagens.
list.h: Arquivo de cabeçalho com a definição das estruturas e declaração das funções da lista encadeada.
extractor/extractor_teste.py: Script Python para extração de características das imagens.
query/extractor: Diretório onde são armazenados os descritores das imagens consultadas.
location.c: Contém a implementação das funções relacionadas à lista encadeada das localizações
location.h: Arquivo de cabeçalho com a definição das estruturas e declaração das funções para a indexação e busca de imagens.


### Indexação
  Para a indexação, compilamos e executamos o arquivo index.c. Ele é responsável por percorrer todas as imagens do banco e realizar a extração dos descritores, que serão utilizados para futura busca. Essa etapa do projeto gera um arquivo .txt que será utilizado para mapear o caminho das imagens, seus respectivos descritores e a localidade referente.
  A indexação é feita através de um código em python, executado através da chamada de sistema em C, que gera os descritores utilizando o método Sift, através da biblioteca **OpenCV**. Para saber mais sobre ele [clique aqui](https://docs.opencv.org/4.x/da/df5/tutorial_py_sift_intro.html).

### Busca (query)
  A parte de busca do projeto é realizada pelo arquivo query.c. Ele é responsável por receber uma imagem de consulta, extrair o descritor correspondente e compará-lo com os descritores das imagens indexadas no banco de dados.

## Execução do programa
  Siga as etapas abaixo para utilizar o sistema:

  Clone o repositório do projeto em sua máquina local.
  Abra um terminal e navegue até o diretório do projeto.
  $ cd caminho/do/diretorio/do/projeto

  Compile o código C executando o seguinte comando:
  $ gcc -c location.c -o location.o
  $ gcc -c list.c -o list.o
  $ gcc -c query.c -o query.o
  $ gcc location.o list.o query.o -o programa


  Execute o programa fornecendo os argumentos necessários. Por exemplo: 
  $ ./programa img/aleatorias/foto.jpeg
  index_histogram-extractor.txt 5

    O primeiro argumento é o caminho da imagem de consulta.
    O segundo argumento é o caminho do arquivo de extração de histogramas.
    O terceiro argumento é o número de localidades a serem exibidas.
  Aguarde até que o sistema processe a consulta e exiba as localidades semelhantes na tela.

### Requisitos
  Utilizamos ambiente linux para o desenvolvimento do projeto. Caso deseje rodar o código, sugerimos que utilize o Sistema Operacional Linux ou utilize WSL2.
  Antes de executar o sistema, verifique se você possui os seguintes requisitos:
  Compilador C: É necessário ter um compilador C instalado no sistema para compilar e executar o código.
  Python 3: O sistema utiliza scripts Python para a extração de características das imagens.

  
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
