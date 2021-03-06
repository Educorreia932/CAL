# Projecto de CAL - TourMateApp 2019/2020**  
**Autores:** Alexandre Abreu, Eduardo Correia, Juliane Marubayashi 

## Descrição  
Projeto baseado em grafos, [Traveling Salesman Problem](https://en.wikipedia.org/wiki/Travelling_salesman_problem) e visualização de grafos.  
Pode ser utilizado em Windows e Linux com as devidas configurações feitas. 

## Conteúdo
```
~ data/
    edges_PORTO.csv					:Arquivos contendo os edges da cidade do Porto. edges_<CIDADE>.csv
    map.png						:Imagem de background da cidade do Porto
    nodes_PORTO.csv					:Matriz contendo os nodes da cidade do Porto. nodes_<CIDADE>.csv
    matrix_PORTO_pred					:Arquivo em que a matriz de paths do floyd Warshall será armazenada.
    matrix_PORTO_dest					:Arquivo em que a matrix das distancias do floydWarshall será armazenada
    POI_PORTO.txt					:Arquivo contendo informações sobre pontos turisticos
+ lib/							:Library GraphViewer
+ docs/							:Documentação e relatório sobre o programa
~ src/
  ~ Graph/						:Classes relacionadas ao grafo
      Edge.cpp
      Edge.h
      Graph.cpp
      Graph.h
      GraphFactory.cpp
      GraphFactory.h
      Vertex.cpp
      Vertex.h
  ~ Storage/						:Classes relacionadas ao armazenamento de dados 
      FloydStorage.cpp					:Armazena em arquivos as matrizes do FloydWarshall
      FloydStorage.h
      PoiStorage.cpp					:Representa e lê pontos de interesses a partir de arquivos
      PoiStorage.h
  ~ UserInterface/					:Classe responsável por criar e gerenciar interface do usuario 
      UserInterface.cpp
      UserInterface.h
    CMakeLists.txt
    Errors.h						:Classe que contem erros
    main.cpp
    README.cpp
    Utils.cpp						:Arquivo com utilidades extra 
    Utils.h
~ utils/map_extraction/
  + cache/
  + images/
    getGraph.py						:Extração de Mapas do openStreetMap já formatados para uso do programa
```

Para compilar em windows:   
Dependências: mingw32 
Dirija-se ao diretório TourMateApp\src e digite em seu terminal. 

```shell
cmake -G "MinGW Makefiles"
mingw32-make.exe all
```

E então basta executar o arquivo src.exe


## Notas e instruções de uso
-  Caso não seja inserido o tempo maximo do usuário [opção 4 do menu principal], o tempo será considerado infinito e o output de tempo gerado pelo greedy algorithm deve ser ignorado, pois o algoritmo deixa de considerá-lo para calcular rotas.
- O tempo é exibido em minutos
- O algoritmo de FloydWarshall será apenas executado casos os ficheiros matrix_<cidade>_dest ou matrix_<cidade_pred não existam. Caso contrário o programa irá reler o conteúdo destes. 
	
![Preview](https://cdn.discordapp.com/attachments/679664591675850762/713512039271759912/1.gif)

