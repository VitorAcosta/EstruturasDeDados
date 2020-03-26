#include <iostream>
using namespace std;

class No{//Classe nó
public:
    No(int valor){ //Método construtor.
        this->valor = valor;
        this->prox = NULL;
    }
    int valor; //O valor a ser armazenado a cada item.
    No* prox; //O endereço do próximo item.
};


class FilaEncadeada{
public:
    No* primeiro; //Ponteiro para o primeiro nó de toda a lista.
    No* ultimo;

    FilaEncadeada(){
        primeiro = NULL;
        ultimo = NULL;
    }

    bool enfileira(int valor){
        No* novo = new No(valor);
        //Se não é possível criar um novo Nó.
        if(!novo)
            return false;
        
        if(ultimo) //Se a fila já possui elementos, o ultimo já está apontando para algum valor
                  //então, se existir um elemento considerado como o último, o novo valor será
                 //o próximo do atual.
                 /**         
                  * Fila: 1  5
                  *          |
                  *        ultimo
                  * 
                  * Novo valor inserido: 2
                  *          
                  *            ultimo   ultimo->proximo
                  *               |          |
                  * Fila: 1       5          2
                  * */
            ultimo->prox = novo;

        else
            //Se a fila está vazia, o primeiro elemento será o novo inserido.
            primeiro = novo;
        
        //O ultimo elemento da fila sempre será o novo valor inserido.
        ultimo = novo;
        return true;
    }


    int desenfileira(bool *ok = NULL){
        //Verifica se não existem mais elementos na lista.
        if (!primeiro){
            //Se o usuário deseja o retorno (passou o ponteiro de bool)
            if(ok){
                //Define-se o valor como false e retorna -1;
                //Dessa forma, o usuário saberá que o valor -1 trata-se de um erro
                //ao remover.
                *ok = false;
                return -1;
            }
        }
        
        int temp = primeiro->valor; //int temp é o valor a ser retornado
        primeiro = primeiro->prox; //primeiro->prox adquire o próximo valor da fila.

        if(ok) //Se o usuário deseja retorno (passou ponteiro de bool)
            *ok = true; //Define como verdadeiro (o valor retornado do método é realmente o valor retirado da fila)
        
        return temp;
    }

    void limpa(){
        No* atual = primeiro;
        No* prox;
        while(atual){
            prox = atual->prox;
            delete atual;
            atual = prox;
        }
    }

    void imprime(){
        No* atual;
        for(atual = primeiro ;atual != NULL;atual = atual->prox)
            cout << atual->valor << " ";
        cout << "\n" << endl;
    }

    ~FilaEncadeada(){
    }
};


int main() {
    cout << "Inicio" << endl;
    bool ok;
    FilaEncadeada fi;
    fi.enfileira(1);
    fi.enfileira(5);
    fi.enfileira(58);
    fi.enfileira(13);
    fi.imprime();
    cout << fi.desenfileira(&ok) << endl;
    cout << (ok ? "Valor valido":"Valor invalido") << endl;
    cout << fi.desenfileira(&ok) << endl;
    cout << (ok ? "Valor valido":"Valor invalido") << endl;
    cout << fi.desenfileira(&ok) << endl;
    cout << (ok ? "Valor valido":"Valor invalido") << endl;
    cout << fi.desenfileira(&ok) << endl;
    cout << (ok ? "Valor valido":"Valor invalido") << endl;

    //Essa linha deve retornar -1, sendo um valor invalido.
    cout << fi.desenfileira(&ok) << endl;
    cout << (ok ? "Valor valido":"Valor invalido") << endl;

    return 0;
}