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

  imprime(){
    let temp = this.primeiro;
    for(let i = 0; i < this.n; i++){
      console.log(temp.valor);
      temp = temp.proximo;
    }
    console.log("\n");
  }
}