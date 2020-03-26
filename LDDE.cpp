#include <iostream>
using namespace std;

/**
 * A classe nó é responsável por criar um novo valor e conectá-lo a lista
 * encadeada. Como a lista é duplamente encadeada, para cada novo nó é necessário
 * liga-lo ao nó anterior (se existir) e com o nó futuro (se existir).
 * Portanto, a classe contará com três variaveis, dois ponteiros
 * (um para o nó anterior e outro para o próximo) e um inteiro, que será de fato o valor.
 */
class No{
public:
    No(int valor){ //Método construtor
        this->valor = valor;
        this->proximo = NULL;
        this->anterior = NULL;
    }
    int valor;
    No* anterior; //Nó anterior ao atual
    No* proximo; //Nó próximo ao atual.
};


class LDDE{
public:
    No* primeiro;
    No* ultimo;
    int n;
    LDDE(){
        primeiro = NULL;
        ultimo = NULL;
        n = 0;
    }

    bool insere(int valor){
        No* novo = new No(valor);
        // Se não for possível alocar um novo nó, sai do método.
        if(!novo)
            return false;

        //O nó anterior inicialmente é NULO, e o nó atual será igual ao primeiro nó de toda a sequência.
        No* NoAnterior = NULL;
        No* NoAtual = primeiro;

        //Deslocamento entre os nós da lista.
        while(NoAtual != NULL && NoAtual->valor < valor){
            /**
             * Se o nó atual não for nulo (ainda há itens) e o valor desse nó for menor
             * que o valor que o usuário deseja inserir, entra-se nesse FOR.
             * O nó anterior será o nó atual (NoAnterior = NoAtual)
             * E o nó atual será igual ao próximo nó.
             */
            NoAnterior = NoAtual;
            NoAtual = NoAtual->proximo;
        }

        if(NoAnterior){
            /**
             * Se existe um nó anterior, entra no IF. (Faz a ligação do nó anterior com o atual)
             * O próximo nó será o novo (NoAnterior->proximo = novo)
             * E o nó anterior será ligado com o novo nó (novo->anterior = NoAnterior)
             */
            NoAnterior->proximo = novo;
            novo->anterior = NoAnterior;
        }
        else
            /**
             * Caso não exista um nó anterior (Verifica se esse novo nó é o primeiro)
             * então o primeiro nó será este novo nó.
             */
            primeiro = novo;

        if(NoAtual)
            /**
             * Se existe um nó atual (Faz a ligação do atual com o próximo nó)
             * o nó atual apontará como nó anterior o novo nó. (NoAtual->anterior = novo)
             */
            NoAtual->anterior = novo;
        else
            /**
             * Caso não exista um próximo nó, quer dizer que o novo nó será também o último.
             */
            ultimo = novo;

        /**
         * O próximo nó será ligado ao nó atual. (novo->proximo = NoAtual)
         * incrementa-se o n (tamanho da lista)
         * Retorna operação realizada com sucesso.
         */
        novo->proximo = NoAtual;
        n++;
        return true;
    }

    int busca(int valor){
        /**
         * Cria-se um ponteiro para o primeiro nó.
         */
        No* temp = primeiro;
        for(int i=0; i < n; i++) {
            /**
             * Se o valor desse nó for igual ao valor buscado, retorna o n deste nó.
             */
            if (temp->valor == valor)
                return i;
            /**
             * Incrementa o passo (o nó atual, será o próximo nó)
             */
            temp = temp->proximo;
        }
        /**
         * Se não encontra, retorna -1.
         */
        return -1;
    }
    bool remove(int valor){
        /**
         * Cria-se dois ponteiros, para o primeiro nó da lista
         * e um para o nó anterior.
         */
        No* atual = primeiro;
        No* anterior = NULL;

        for(int i=0; i < n && atual->valor != valor; i++) {
            /**
             * Se o i for menor que n e o valor do nó atual for diferente do valor
             * buscado para remover, entra no FOR.
             * O nó anterior será o nó atual. (anterior = proximo)
             * E o nó atual será o próximo nó. (atual = atual->proximo)
             */
            anterior = atual;
            atual = atual->proximo;
        }
        //Se não existe o valor procurado.
        if(!atual || atual->valor != valor){
            //Sai da função.
            return false;
        }

        if(anterior){
            /**
             * Se existe um nó anterior, entra no IF.
             * O próximo nó, a partir do anterior será o próximo nó a partir do atual.(anterior->proximo = atual->proximo)
             * Ou seja, o endereço do nó anterior será igual ao endereço do próximo nó do nó que deseja-se excluir,
             * basicamente, refaz a ligação:
             *    ->Por exemplo, considere a lista: 1 2 3 e deseja-se remover o 2.
             *    o anterior->proximo acessa o endereço do 2 (o qual vamos excluir) e iguala esse endereço
             *    ao endereço do próximo nó a partir do nó atual (3), removendo todas a ligações com o 2.
             */
            anterior->proximo = atual->proximo;
        }
        else{
            /**
             * Se não existe um nó anterior, o primeiro nó será o endereço do próximo nó.
             */
            primeiro = atual->proximo;
        }

        if(atual->proximo){
            /**
             * Se existe um próximo nó a partir do atual, entra no IF.
             * Liga-se o endereço do nó anterior do próximo nó a partir do atual (proximo->proximo->anterior)
             * ao nó anterior do atual.
             *    -> Aproveitando o exemplo anterior, essa linha faz a ligação entre o 1 e o 3.
             */
            atual->proximo->anterior = atual->anterior;
        }
        else{
            /**
             * Se não existe um próximo nó, quer dizer que o nó buscado é o último.
             */
            ultimo = anterior;
        }
        delete atual;
        n--;
        return true;
    }
    void imprime(){
        No* temp = primeiro;
        for(int i=0; i < n; i++){
            cout << temp->valor << " ";
            temp = temp->proximo;
        }
        cout << endl;
    }
};



int main(){
    LDDE lista;
    cout << "INICIO" << endl;
    /*********************************
     *    !      TEST ZONE         !
     *********************************/
    lista.insere(1);
    lista.imprime();
    lista.insere(5);
    lista.imprime();
    lista.insere(10);
    lista.imprime();
    lista.insere(7);
    lista.imprime();
    int x = lista.busca(10);
    cout << "Valor buscado esta no n: " << x << endl;
    lista.remove(1);
    lista.imprime();
    lista.remove(10);
    lista.imprime();
    lista.insere(6);
    lista.remove(5);
    lista.remove(6);
    lista.imprime();
    return 0;
}