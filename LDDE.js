class No{
  constructor(valor){
    this.valor = valor;
    this.proximo = null;
    this.anterior = null;
  }
}
class LDDE{
  constructor(){
    this.primeiro = null;
    this.ultimo = null;
    this.n = 0;
  }

  insere(valor){
    let novoNo = new No(valor);
    if(!novoNo){
      return false;
    }

    let noAnterior = null;
    let noAtual = this.primeiro;

    while(noAtual != null && noAtual.valor < valor){
      noAnterior = noAtual;
      noAtual = noAtual.proximo;
    }

    if(noAnterior){ //Caso já possua elementos na lista
      noAnterior.proximo = novoNo;
      novoNo.anterior = noAnterior;
    }
    else{
      this.primeiro = novoNo;
    }

    (noAtual)? noAtual.anterior = novoNo : this.ultimo = novoNo;

    novoNo.proximo = noAtual;
    this.n++;
    return true;
  }
  busca(valor){
        let temp = this.primeiro;
        for(let i=0; i < this.n; i++) {
            if (temp.valor == valor)
                return [true,i];
            temp = temp.proximo;
        }
        return [false,-1];
  }

  remove(valor){
    let atual = this.primeiro;
    let anterior = null;
    for(let i=0; i < this.n && atual.valor != valor; i++) {
        anterior = atual;
        atual = atual.proximo;
    }
    if(!atual || atual.valor != valor){
        return [false,'O valor a ser removido não existe.'];
    }

    if(anterior){
        anterior.proximo = atual.proximo;
    }
    else{
        this.primeiro = atual.proximo;
    }

    if(atual.proximo){
        atual.proximo.anterior = atual.anterior;
    }
    else{
        this.ultimo = anterior;
    }
    this.n--;
    return [true,'Valor removido com sucesso'];
  }
  
  /**
   * Método inserido para ser compatível o tipo de retorno
   * para a simulação com o React Native.
   * Basicamente, transforma a estrutura ligada por ponteiros em um vetor.
   * Dessa forma, no clientSide é possível aplicar o .map
   * nesse vetor, possibilitando a simulação.
   */
  tranformaArray(){
    let temp = this.primeiro;
    let array = [];
    for(let i = 0; i < this.n; i++){
      array.push(temp.valor);
      temp = temp.proximo;
    }
    return array;
  }

  imprime(){
    let temp = this.primeiro;
    for(let i = 0; i < this.n; i++){
      console.log(temp.valor);
      temp = temp.proximo;
    }
    console.log("\n");
  }
}
lista = new LDDE();
 lista.insere(1);
    lista.imprime();
    lista.insere(5);
    lista.imprime();
    lista.insere(10);
    lista.imprime();
    lista.insere(7);
    lista.imprime();
    console.log(lista.tranformaArray());
