# Estruturas De Dados

Repositório referente à diversas estruturas de dados.

# Estruturas criadas:
## Lista estática sequencial (LES)
Um tipo de vetor ordenado, o qual os números inseridos ficam em orderm crescente, e é estático pois conta com um número *__n__* máximo, não sendo possível inserir novos valores quando esse índice alcança seu limite.

## Lista dinâmica sequencial (LDS)
Uma variante da anterior, é um vetor ordenado, o qual os números inseridos ficam em ordem crescente, porém é dinâmico no sentido de expandir de tamanho quando necessário. Logo o vetor começa com __*n__* posições e caso necessário é realocado __*n x 2__* posições. Não havendo limites para novos valores.

## Lista dinâmica encadeada (LDE)
Um vetor no qual não há limites de valores, ordenado, o qual os números inseridos ficam em ordem crescente. A estruturação dessa lista é baseada em nós. Cada nó é composto de duas informações, um inteiro (que é o valor) e um ponteiro para o próximo nó.

## Lista dinâmica duplamente encadeada (LDDE)
Utilizando uma lista dinâmica encadeada (LDE), a qual possuía somente duas informaçoes por nó (valor e endereço do próximo nó), adicionar uma nova informação, referênciando o nó anterior ao atual. De acordo com o esquema:\
![ImagemLDDE](https://www.thecrazyprogrammer.com/wp-content/uploads/2015/09/Doubly-Linked-List-in-C-and-C-.gif)
