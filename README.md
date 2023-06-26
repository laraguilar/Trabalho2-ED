# Trabalho2-ED

Este projeto implementa um sistema de indexação e busca de imagens em uma base de dados utilizando métodos de extração de características (CBIR) para indexar as imagens e permite realizar consultas para encontrar imagens semelhantes. O código-fonte está escrito em C e com algumas chamadas em Python.

Guia de utilização Git e GitHub: [Notion - Git e GitHub](https://cerulean-papaya-41b.notion.site/Git-e-GitHub-872aa24d4e724846a2bf74b12f2975d0?pvs=4)

Pasta de fotos: [Google Fotos](https://drive.google.com/drive/folders/1yDnofym7c58yfE7_7hulKpd_RbGvPCDZ)

## Visão Geral
### Estruturação dos arquivos
<img src="https://github.com/laraguilar/Trabalho2-ED/assets/72893552/87494093-03c5-473b-aa5f-ed6d4d110e3f" height="300px"/>

### Fluxograma básico
<img src="https://github.com/laraguilar/Trabalho2-ED/assets/72893552/b755f64a-2357-401b-8c4e-2a58e94d8a67" width="600px"/>


Para obtermos o resultado final (as **n** localidades mais próximas), primeiro devemos construir nossa base de dados através da indexação. Essa indexação é armazenada dentro das pastas de extração (base/extractor_<NOME_DA_LOCALIDADE>).
Já o nosso programa de busca deve primeiro extrair as características da imagem selecionada, após isso, fará uma comparação com os índices do banco. Ele deverá selecionar as 5 localidades mais parecidas e imprimir na tela. 


## Funcionalidades Principais
  O sistema possui as seguintes funcionalidades:
  - Indexação de Imagens: O programa realiza a indexação das imagens da base de dados, extrai suas características e armazena os índices em pastas de extração dentro das pastas de extração (base/extractor_<NOME_DA_LOCALIDADE>). Além disso, gera o arquivo index_histogram-extractor.txt que mapeia a quantidade de imagens e o caminho da imagem, caminho do extractor e localidade de cada uma delas. Ele serivirá como referência para a futura busca.

  - Busca de Imagens: O programa permite realizar consultas para encontrar imagens semelhantes com base em uma imagem de referência. Ele extrai as características da imagem consultada, compara com os índices armazenados e seleciona as 5 localidades mais parecidas. O resultado da busca é exibido na tela.


## Arquivos
### INDEXAÇÃO (index.c):
   Para a indexação, compilamos e executamos o arquivo index.c. Ele é responsável por percorrer todas as imagens do banco e realizar a extração dos descritores, que serão utilizados para futura busca. Essa etapa do projeto gera um arquivo .txt que será utilizado para mapear o caminho das imagens, seus respectivos descritores e a localidade referente.
  A indexação é feita através de um código em python, executado através da chamada de sistema em C, que gera os descritores utilizando o método Sift, através da biblioteca **OpenCV**. Para saber mais sobre ele [clique aqui](https://docs.opencv.org/4.x/da/df5/tutorial_py_sift_intro.html).
  
  #### Fluxograma 
  <img src="https://github.com/laraguilar/Trabalho2-ED/assets/72893552/e81caabd-b24d-4873-9894-da9412cd77d7" width="400px"/>

### BUSCA (query.c):
  O arquivo é responsável pela busca de imagens. Nele foi implementada a função query que será usada para realizar a busca comparando os descritores. Ele é responsável por receber uma imagem de consulta, extrair o descritor correspondente e compará-lo com os descritores das imagens indexadas na base de dados.

  #### Fluxograma 
  <img src="https://github.com/laraguilar/Trabalho2-ED/assets/72893552/a2cdf8d1-5286-4f4d-badb-331c20344c91" width="400px"/>

  O coração dessa funcionalidade é a função chamada **match_images**, dentro do arquivo list.c. Ela é responsável por comparar o descritor de cada imagem do banco com a imagem da lista. Esse é o cerne da solução. Essa função foi implementada dentro do arquivo list devido à necessidade de percorrer a lista com as imagens. 

  <img src="https://github.com/laraguilar/Trabalho2-ED/assets/72893552/6d1cfc49-f881-408d-a539-e65828ca70d5" width="600px"/>


### Principais estruturas utilizadas 

**list.c:** Contém a implementação das funções relacionadas à lista encadeada das imagens.
  
**list.h:** Arquivo de cabeçalho com a definição das estruturas e declaração das funções da lista encadeada.

**location.c:** Contém a implementação das funções relacionadas à lista encadeada das localizações
  
**location.h:** Arquivo de cabeçalho com a definição das estruturas e declaração das funções para a indexação e busca de imagens.

**functions.c:** Contém a implementação de funções utilizadas nos dois programas.
  
**functions.h:** Arquivo de cabeçalho com a declaração das funções.

  <img src="https://github.com/laraguilar/Trabalho2-ED/assets/72893552/0d81c6fe-93ef-4967-8804-c8a5e7082555" width="600px"/>

### Arquivos auxiliares

**extractor/extractor.py:** Script Python para extração de características das imagens.

**extractor/match.py:** Script Python para comparação de duas imagens e retorno da quantidade de correspondências.

**query/extractor:** Diretório onde são armazenados os descritores das imagens consultadas.

## Requisitos do sistema
  Utilizamos ambiente linux para o desenvolvimento do projeto. Caso deseje rodar o código, sugerimos que utilize o Sistema Operacional Linux ou utilize WSL2.
  Antes de executar o sistema, verifique se você possui os seguintes requisitos:
  
  - Compilador C: É necessário ter um compilador C instalado no sistema para compilar e executar o código.
  - Python 3: O sistema utiliza scripts Python para a extração de características das imagens.
        - Bibliotecas python: opencv, matplotlib, numpy

  [Guia de Instalação e Configuração WSL2](https://drive.google.com/drive/folders/1yDnofym7c58yfE7_7hulKpd_RbGvPCDZ) ***Não é necessário instalar o Docker***
  [Compilando e executando programas em C](https://www.alura.com.br/artigos/compilando-executando-programas-c-c-windows)


## Execução do programa

### index.c 

#### 1º compile os arquivos separadamente
        $ gcc -c functions.c -o functions.o
        $ gcc -c index.c -o index.o

#### 2º Compile os executáveis em conjunto
        $ gcc functions.o index.o -o index-images

#### 3º Execute o programa
        $ ./index-images

### query.c
#### 1º compile os arquivos separadamente
        $ gcc -c functions.c -o functions.o
        $ gcc -c location.c -o location.o
        $ gcc -c list.c -o list.o
        $ gcc -c query.c -o query.o
        
#### 2º compile os executáveis gerados em conjunto

        $ gcc functions.o location.o list.o main.o -o programa

#### 3º execute o programa passando os argumentos devidos

  Argumentos necessários: caminho da imagem de consulta, arquivo de index e a quantidade de localidades similares a serem encontradas.
  
  ***OBS: Os argumentos devem ser passados na ordem correta***
  
        $ ./programa query/img/foto.jpeg index_histogram-extractor.txt 5
        

## Referências: 

[Image Similarity using Deep Ranking](https://medium.com/@akarshzingade/image-similarity-using-deep-ranking-c1bd83855978)

[Indexação e Recuperação de Imagens por Conteúdo](https://www.cin.ufpe.br/~in1152/aulas/rec-imagem-por-conteudo.pdf)

[Content-based Image Retrieval (CBIR) - Slides](https://courses.cs.washington.edu/courses/cse576/07sp/notes/CBIR_white.pdf)

[Content-based image retrieval](https://en.wikipedia.org/wiki/Content-based_image_retrieval)

[Introduction to SIFT (Scale-Invariant Feature Transform)](https://docs.opencv.org/4.x/da/df5/tutorial_py_sift_intro.html)

[Most Popular Distance Metrics Used in KNN and When to Use Them](https://www.kdnuggets.com/2020/11/most-popular-distance-metrics-knn.html)

[https://docs.opencv.org/4.x/dc/dc3/tutorial_py_matcher.html](https://docs.opencv.org/4.x/da/df5/tutorial_py_sift_intro.html)
