#include <iostream>
using namespace std;

//Author: Vitor Acosta da Rosa

class No
{
public:
  int valor;
  No *pai;
  No *fDir;
  No *fEsq;
  No()
  { //Construtor
    pai = NULL;
    fDir = NULL;
    fEsq = NULL;
  }
};

class ArvBusca
{
private:
  No *raiz;
  int qntElementos;
  //Método que imprime todos os nós de maneira recursiva in-order.
  void imprime(No *r)
  {
    if (r == NULL)
    {
      return;
    }
    imprime(r->fEsq);
    cout << r->valor << " ";
    imprime(r->fDir);
  }

  bool removeNos(No* encontrado){
    No *pai;   
    //Caso
    if(encontrado == NULL){
      return false;
    }
    pai = encontrado->pai; //Encontra o pai do nó atual;
    if (encontrado->fEsq == NULL && encontrado->fDir == NULL){ //Primeiro caso: exclusão de uma folha (um nó sem filhos)
      if(pai){
        if (pai->valor > encontrado->valor) //Se o valor do pai é maior que o valor a ser deletado, quer dizer que o nó
            pai->fEsq = NULL;     //a ser deletado está à esquerda
        else
            pai->fDir = NULL;
      }
      else 
        raiz=NULL;
    }
    else if (encontrado->fEsq && encontrado->fDir){ 
        //terceiro caso: o nó tem dois filhos.
        //Na definição do antecessor, deve-se ir ao primeiro nó à esquerda e percorrer todos os nós à direita
        //a partir deste, até que não existam mais nós à direita, logo o while percorre todos os nós a direita,
        //até chegar em um nó que não possui mais nós à direita.
        No *antecessor = encontrado->fEsq;
        
        while (antecessor->fDir != NULL)
          antecessor = antecessor->fDir;

        //Ao invés de trocar todos os ponteiros de lugar, simplesmente adota-se
        //o valor do nó a excluir como o valor do antecessor, logo após exclui-se o antecessor
        //de forma recursiva, na qual poderá cair em algum das duas condições (nenhum ou um filho)
        encontrado->valor = antecessor->valor;
        return removeNos(antecessor);        
    }
    else
      {
        //Segundo caso: exclusão de um nó que contenha somente um filho.
        //Como existe somente um filho, verifica-se qual lado o filho está, logo cria-se um nó filho que terá o valor
        //do nó existente, seja o direito ou esquerdo, logo, verifica-se se existe por exemplo o filho esquerdo,
        //se o operador ternário for verdadeiro filho = encontrado->fEsq, caso contrário filho = encontrado->fDir;
        No *filho = (encontrado->fEsq) ? encontrado->fEsq : encontrado->fDir;

        //Se remove um nó intermediário deve-se refazer a ligação entre o pai do nó excluido com o nó filho do atual.
        filho->pai = pai;
        if (pai->valor > encontrado->valor)
          pai->fEsq = filho;
        else
          pai->fDir = filho;
      }
      delete encontrado;
      qntElementos--;
      return true;
  }


public:
  ArvBusca()
  {
    raiz = NULL;
    qntElementos = 0;
  }

  bool insere(int valor)
  {
    No *pai = NULL;   //Um ponteiro para o pai do nó atual (para manter a relação)
    No *atual = raiz; //Nó atual da árvore, partindo sempre da raiz.
    No *novo = new No;
    novo->valor = valor; //inicia o novo nó com o valor dado para a inserção

    if (raiz == NULL)
    { //Não existe nenhum elemento na árvore, logo, o novo elemento será a raiz
      raiz = novo;
      qntElementos++;
      return true;
    }

    while (atual)
    {              //Enquanto houver nós na árvore
      pai = atual; //Garante o apontamento para o nó passado.
      if (valor <= atual->valor)
      {                      //Verifica se o número a ser inserido é menor que o número do atual (inserção à esquerda)
        atual = atual->fEsq; //Se existe nó à esquerda do atual, sobreescrevemos o nó atual como sendo o próximo nó
                             //preparando para a próxima iteração.
      }
      else
      {
        atual = atual->fDir; //Se existe nó à direita do atual, sobreescrevemos o nó atual como sendo o próximo nó
                             //preparando para a próxima iteração.
      }
    }

    novo->pai = pai; //Após sair do while, já teremos onde o novo valor será inserido, e também
                     //qual será o nó pai do atual.

    if (valor <= pai->valor) //Se não houver nós à esquerda, o novo nó será inserido imediatamente após o nó atual
      pai->fEsq = novo;
    else
      pai->fDir = novo;

    qntElementos++;
    return true;
  }

  void imprime()
  {
    imprime(raiz);
    cout << endl;
  }

  No *busca(int valor, bool *resposta)
  {
    No *atual = raiz;
    if (raiz && raiz->valor == valor)
    { //Se o valor procurado já é a raiz da árvore (e também se a raiz existe).
      if (resposta)
        *resposta = true;
      return raiz;
    }
    while (atual)
    { //Deslocamento entre os nós da árvore
      if (valor == atual->valor)
      {
        if (resposta)
          *resposta = true;
        return atual;
      }
      else if (valor < atual->valor)
        atual = atual->fEsq;
      else
        atual = atual->fDir;
    }
    if (resposta)
      *resposta = false;
    return NULL;
  }

  bool removeNos(int valor){
    return(removeNos(busca(valor, NULL)));
  }

  void destroiNo(No * atual)
    {                    //Método recursivo para a desalocação de memória, pos-order.
                         //com pos-order, é acessado o lado esquerdo, desalocado totalmente, logo após desalocado
                         //o lado direito totalmente e por último a raiz.
      if (atual == NULL) //Caso base da recursão
        return;
      destroiNo(atual->fEsq);
      destroiNo(atual->fDir);
      delete atual;
    }

    virtual ~ArvBusca()
    {
      destroiNo(raiz);
      cout << "Memoria desalocada com sucesso" << endl;
    }
  };

  int main(int argc, char *argv[])
  {
    // abrindo escopo para verificar o destrutor assim que o escopo se fechar
    {
      ArvBusca a;
      bool ok;    
      a.insere(15);
      a.insere(10);
      a.insere(7);
      a.insere(8);
      a.insere(12);
      a.insere(11);
      a.insere(20);
      a.insere(30);

      cout << "Retorno da busca: " << a.busca(12,&ok) << " --> ";
      cout << (ok ? "Valor valido":"Valor invalido") << endl;
      cout << "Retorno da busca: " << a.busca(99,&ok) << " --> ";
      cout << (ok ? "Valor valido":"Valor invalido") << endl;   
      cout << "Retorno da busca: " << a.busca(15,&ok) << " --> ";
      cout << (ok ? "Valor valido":"Valor invalido") << endl;

      a.imprime();

      a.removeNos(15);
      cout << "Retorno da busca: " << a.busca(15,&ok) << " --> ";
      cout << (ok ? "Valor valido":"Valor invalido") << endl;
      a.imprime();
    }
    return 0;
  }
