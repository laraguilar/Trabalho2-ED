# Trabalho2-ED

Guia de utilização Git e GitHub: [Notion - Git e GitHub](https://cerulean-papaya-41b.notion.site/Git-e-GitHub-872aa24d4e724846a2bf74b12f2975d0?pvs=4)

Pasta de fotos: [Google Fotos](https://drive.google.com/drive/folders/1yDnofym7c58yfE7_7hulKpd_RbGvPCDZ)

## Visão Geral
### Estruturação dos arquivos
<img src="https://github.com/laraguilar/Trabalho2-ED/assets/72893552/ba49368f-3cb7-442a-b7f0-50f1937fc1a7" width="300px"/>

### Fluxograma básico
<img src="https://github.com/laraguilar/Trabalho2-ED/assets/72893552/b015bfbd-1ec1-4114-8d00-414c257eda2b" width="200px"/>

Primeiro, vamos realizar a indexação das imagens da nossa base através da indexação, utilizando métodos de extração de características.
Nosso programa deve conter uma lista encadeada contendo a estrutura da imagem. A princípio, fará parte da estrutura os atributos nome da imagem, localidade, descritor e caminho, sendo que estes podem sofrer alteração com o decorrer do projeto. Essa indexação é armazenada dentro das pastas de extração (base/extractor_n).
Nosso programa de busca deve primeiro extrair as características da imagem selecionada, após isso, fará uma comparação com os índices do banco. Ele deverá selecionar as 5 localidades mais parecidas e imprimir na tela. 

## Executar o código

### Requisitos
  Utilizamos ambiente linux para o desenvolvimento do projeto. Caso deseje rodar o código, sugerimos que utilize o Sistema Operacional Linux ou utilize WSL2.
  
  [Guia de Instalação e Configuração WSL2](https://drive.google.com/drive/folders/1yDnofym7c58yfE7_7hulKpd_RbGvPCDZ)
  
  ***Não é necessário instalar o Docker***

  Certifique-se de que o compilador está instalado na sua máquina.

### Indexação
  Para a indexação, compilamos e executamos o arquivo index.c. Ele é responsável por percorrer todas as imagens do banco e realizar a extração dos descritores, que serão utilizados para futura busca. Essa etapa do projeto gera um arquivo .txt que será utilizado para mapear o caminho das imagens, seus respectivos descritores e a localidade referente.
  A indexação é feita através de um código em python, executado através da chamada de sistema em C, que gera os descritores utilizando o método Sift, através da biblioteca **OpenCV**. Para saber mais sobre ele [clique aqui](https://docs.opencv.org/4.x/da/df5/tutorial_py_sift_intro.html).

### Busca (query)


## Referências: 

https://medium.com/@akarshzingade/image-similarity-using-deep-ranking-c1bd83855978

https://www.cin.ufpe.br/~in1152/aulas/rec-imagem-por-conteudo.pdf

https://courses.cs.washington.edu/courses/cse576/07sp/notes/CBIR_white.pdf

https://en.wikipedia.org/wiki/Content-based_image_retrieval



