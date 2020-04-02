#include <iostream>
#define TAM 8
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
class LDE{
private:
    /**
     * A Classe LDE possuirá somente o endereço do primeiro nó.
     */
    No* primeiro; //Ponteiro para o primeiro nó de toda a lista.
    int n; //Variavel de controle referente ao tamanho.

    LDE(){
        this->primeiro = NULL; //Ao iniciar a lista, não existe nenhum item, logo não há apontamento.
        this->n = 0;
    }

    bool insere(int valor){
        No* novo = new No(valor); //Cria um ponteiro para um novo Nó com o determinado valor. :)
        if(!novo)
            return false;
        /**
         *   Nessas linhas define-se o movimento dos endereços.
         */
        No* anterior = NULL;
        No* proximo = primeiro;

        while(proximo != NULL && proximo->valor < valor){
            anterior = proximo; //Anterior terá o endereço do próximo, mantendo o passo.
            proximo = proximo->prox; //O próximo campo do item inserido.
        }

        if(anterior)
            anterior->prox = novo;
        else{
            primeiro = novo;
        }
        novo->prox = proximo;
        n++;
        return true;
    }
    void imprime(){
        No* temp = primeiro;
        for(int i=0; i < n; i++){
            cout << temp->valor << " ";
            temp = temp->prox;
        }
    }
    No* busca(int valor){
        //Adquire-se o nó atual, no começo, será o primeiro
        No* temp = primeiro;
        while(temp && temp->valor < valor){
            //Se o valor procurado for menor que o valor presente no nó atual, o atual será
            //setado como sendo o próximo nó a partir do atual.
            temp = temp->prox;
        }
        if(temp && temp->valor == valor) //Se encontrou o valor
            return temp; //Retorna o nó atual.
        
        return NULL; //Se não encontrou o valor, retorna um nó nulo.
    }

    bool remove(int valor){
        No* proximo = primeiro;
        No* anterior = NULL;
        for(int i=0; i < n && proximo->valor != valor; i++) {
            anterior = proximo;
            proximo = proximo->prox;
        }
        if(!proximo || proximo->valor != valor){
            return false;
        }
        if(anterior){
            anterior->prox = proximo->prox;
        }
        else{
            primeiro = proximo->prox;
        }
        delete[]proximo;
        n--;
        return true;
    }

    void limpa(){
        No* atual = primeiro;
        No* temp;
        while(atual){
            temp = atual->prox;
            delete atual;
            atual = temp;
        }
        primeiro = NULL;
    }

    ~LDE(){
        limpa();
    };
    /**
     * Friend class permite que métodos e atributos privados sejam acessíveis
     * a classe Hash.
     * */
    friend class Hash;    
};

class Hash{
    /**
     * Método da divisão: h(x) = valor mod tamanho
     * Espalhamento aberto: se houver colisão, refaz o hash.
     * Essa classe basicamente utiliza todas as funcionalidade da LDE,
     * aplicando somente o conceito de organização através de uma função hash.
     */
private:
    int calcHash(int numero){
        int chave;
        chave = numero % MAX;
        return chave;
    }
public:
    LDE* v;
    int n; 
    int MAX;
    Hash(int MAX){ //Construtor
        this->MAX = MAX;
        this->v = new LDE[MAX];
        this->n = 0;
    }
    bool insere(int valor){ 
        //Se o n é menor que o máximo e se foi possível inserir dados na LDE
        if(this->n < this->MAX && v[calcHash(valor)].insere(valor)){
            this->n++;
            return true;
        }
        return false;
    }

    bool remove(int valor){
        if(v[calcHash(valor)].remove(valor)){
            this->n--;
            return true;
        }
        return false;
    }

    No* busca(int valor){
        return v[calcHash(valor)].busca(valor);
    }

    void imprime(){
        for(int j=0; j < MAX; j++){
            v[j].imprime();
        }
        cout<<endl;
    }
    

    ~Hash(){
        delete[] this->v;
    }
};
void testaBusca(Hash& h, int num){
    if(h.busca(num)){
        cout << " valor " << num << " encontrado " << endl;
    }
    else{
        cout << " valor " << num << " nao encontrado " << endl;
    }
}


int main(){
    /*******************************
    *            TESTZONE
    ********************************/
   Hash h(7);

    h.insere(20); //6
    h.insere(22); //1
    h.insere(19); //5
    h.insere(10); //3
    h.insere(11); //4
    h.insere(90); //6
    h.insere(110);//5
    h.imprime();

    testaBusca(h,20);
    testaBusca(h,22);
    testaBusca(h,19);
    testaBusca(h,10);
    testaBusca(h,34);
    testaBusca(h,850);

    h.remove(20);
    h.remove(22);
    h.remove(19);
    h.remove(10);
    h.remove(11);
    h.remove(90);

    h.imprime(); 
    
    return 0;
}