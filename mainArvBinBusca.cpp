#include <iostream>
using namespace std;


class No {
public:
  int valor;
  No* pai;
  No* fDir;
  No* fEsq;
  No(){ //Construtor
    pai = NULL;
    fDir = NULL;
    fEsq = NULL;
  }
};

class ArvBusca {
private:
  No* raiz;
  int qntElementos;
  //Método que imprime todos os nós de maneira recursiva in-order.
  void imprime (No* r) {
    if(r == NULL){
      return;
    }
    imprime(r->fEsq);
    cout << r->valor << " ";
    imprime(r->fDir);
  }
public:
  ArvBusca () {
    raiz = NULL;
    qntElementos = 0;
  }

  bool insere (int valor) {
    No* pai = NULL; //Um ponteiro para o pai do nó atual (para manter a relação)
    No* atual = raiz; //Nó atual da árvore, partindo sempre da raiz.
    No* novo = new No;
    novo->valor = valor; //inicia o novo nó com o valor dado para a inserção

    if(raiz == NULL){ //Não existe nenhum elemento na árvore, logo, o novo elemento será a raiz
      raiz = novo;
      qntElementos++;
      return true;
    }

    while(atual){ //Enquanto houver nós na árvore
      pai = atual; //Garante o apontamento para o nó passado.
      if(valor <= atual->valor){ //Verifica se o número a ser inserido é menor que o número do atual (inserção à esquerda)
          atual = atual->fEsq; //Se existe nó à esquerda do atual, sobreescrevemos o nó atual como sendo o próximo nó
                               //preparando para a próxima iteração.
      }
      else{
          atual = atual->fDir; //Se existe nó à direita do atual, sobreescrevemos o nó atual como sendo o próximo nó
                               //preparando para a próxima iteração.
      }
    }
    
    novo->pai = pai; //Após sair do while, já teremos onde o novo valor será inserido, e também
                     //qual será o nó pai do atual.

    if(valor <= pai->valor)//Se não houver nós à esquerda, o novo nó será inserido imediatamente após o nó atual
      pai->fEsq = novo;
    else
      pai->fDir = novo;
    
    qntElementos++;
    return true;  
  }

  void imprime () {
      imprime(raiz);
      cout<<endl;
  }

  No* busca (int valor, bool* resposta) {
    No* atual = raiz;
    if(raiz && raiz->valor == valor){ //Se o valor procurado já é a raiz da árvore (e também se a raiz existe).
      if(resposta)
        *resposta = true;
      return raiz;
    }
    while(atual){ //Deslocamento entre os nós da árvore
      if(valor == atual->valor){
        if(resposta)
          *resposta = true;
        return atual;
      }
      else if(valor < atual->valor)
        atual = atual->fEsq;
      else
        atual = atual->fDir; 
    }
    if(resposta)
      *resposta = false;
    return NULL;

  }

  void destroiNo(No* atual){ //Método recursivo para a desalocação de memória, pos-order.
                             //com pos-order, é acessado o lado esquerdo, desalocado totalmente, logo após desalocado
                             //o lado direito totalmente e por último a raiz.
    if(atual == NULL) //Caso base da recursão
      return;
    destroiNo(atual->fEsq);
    destroiNo(atual->fDir);
    delete atual;
  }

  virtual ~ArvBusca () {
    destroiNo(raiz);
    cout<<"Memoria desalocada com sucesso"<<endl;
  }
  
};

int main (int argc, char* argv[]) {
  // abrindo escopo para verificar o destrutor assim que o escopo se fechar
  {
    ArvBusca a;
    bool ok;
    a.insere (99);
    a.insere (34);
    a.insere (100);
    a.insere (29);
    a.insere (64);

    cout << "Retorno da busca: " << a.busca(100,&ok) << " --> ";
    cout << (ok ? "Valor valido":"Valor invalido") << endl;
    cout << "Retorno da busca:: " << a.busca(99,&ok) << " --> ";
    cout << (ok ? "Valor valido":"Valor invalido") << endl;   
    cout << "Retorno da busca:: " << a.busca(52,&ok) << " --> ";
    cout << (ok ? "Valor valido":"Valor invalido") << endl;

    a.imprime ();

    a.insere (52);
    a.insere (68);
    a.insere (79);
    a.insere (14);
    a.insere (55);

    cout << "Retorno da busca:: " << a.busca(52,&ok) << " --> ";
    cout << (ok ? "Valor valido":"Valor invalido") << endl;

    a.imprime ();

    // destrutor será chamado quando o escopo terminar*/
  }


  return 0;
}
