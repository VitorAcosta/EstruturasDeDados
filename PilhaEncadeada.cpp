#include <iostream>
using namespace std;

/**
 * A pilha encadeada segue o modelo LiFo - Last in, first out.
 * Ou seja, o último valor a entrar na pilha também é o primeiro a sair.
 * Diferentemente das filas, as quais o primeiro a entrar, também era o primeiro a sair. (FiFo)
 * */

class No{//Classe nó
public:
    No(int valor){ //Método construtor.
        this->valor = valor;
        this->prox = NULL;
    }
    int valor; //O valor a ser armazenado a cada item.
    No* prox; //O endereço do próximo item.
};


class PilhaEncadeada{
public:
    No* topo;

    PilhaEncadeada(){
        topo = NULL;
    }

    bool empilha(int valor){
        No* novo = new No(valor);
        if(!novo)
            return false;
        
        /**
         * Os novos valores inseridos em uma pilha sempre deverão ser o topo dessa pilha.
         * Portanto ao inserir novos valores, o ponteiro do topo antes da inserção vai apontar
         * para o novo elemento, ligando-o com a pilha.
         * Após isso, como todo novo elemento é também o topo da pilha, iguala-se o nó que representa
         * o topo ao novo elemento inserido.
         * 
         * Tais linhas funcionam também para a inserção caso a pilha esteja vazia.
         * Observe que pelo construtor, topo = NULL, logo, o próximo valor de um primeiro nó da pilha
         * será nulo, e quando atribuirmos o topo=novo, a pilha começará a se estruturar corretamente.
         * */
        novo->prox = topo;
        topo = novo;
        return true;
    }

    int desempilha(bool *resposta){
        //Se o topo é nulo, ou seja, se a pilha chegou ao seu fim.
        if(!topo){
            if(resposta)
                *resposta = false;
            return -1;
        }
        int temp = topo->valor;
        topo = topo->prox;

        if(resposta)
            *resposta = true;
        
        return temp;

    }

    void limpa(){
        No* prox;
        while(topo){
            prox = topo->prox;
            delete topo;
            topo = prox;
        }
    }
};


int main() {
    cout << "Inicio" << endl;

    /*********************************
     *              TESTZONE         *
     *********************************/

    bool ok;
    PilhaEncadeada p;
    p.empilha(1);
    p.empilha(5);
    p.empilha(2);
    cout << "Desempilhado: " << p.desempilha(&ok) << " --> ";
    cout << (ok ? "Valor valido":"Valor invalido") << endl;
    cout << "Desempilhado: " << p.desempilha(&ok) << " --> ";
    cout << (ok ? "Valor valido":"Valor invalido") << endl;
    cout << "Desempilhado: " << p.desempilha(&ok) << " --> ";
    cout << (ok ? "Valor valido":"Valor invalido") << endl;

    //A linha abaixo retorna -1 como valor invalido.
    cout << "Desempilhado: " << p.desempilha(&ok) << " --> ";
    cout << (ok ? "Valor valido":"Valor invalido") << endl;

    p.empilha(1110);
    
    cout << "Desempilhado: " << p.desempilha(&ok) << " --> ";
    cout << (ok ? "Valor valido":"Valor invalido") << endl;

    
    p.empilha(1);
    p.empilha(5);
    p.empilha(2);
    p.empilha(9);
    p.empilha(548);
    p.empilha(112);
    p.limpa();
    //Vai dar valor inválido, pois foi aplicado o método limpa() da pilha.
    cout << "Desempilhado: " << p.desempilha(&ok) << " --> ";
    cout << (ok ? "Valor valido":"Valor invalido") << endl;


    

    return 0;
}