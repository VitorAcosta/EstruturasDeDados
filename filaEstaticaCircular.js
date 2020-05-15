class Fila{
    constructor(){
        this.fila = [];
        this.begin = 0;
        this.end = 0;
        this.tamanho = 6; //Max+1
    }

    enfileira(numero){
        if((this.end+1)%(this.tamanho) === this.begin){
            return false;
        }
        this.fila[this.end] = numero;

        this.end = (this.end+1) % (this.tamanho);
        
        return true;
    }

    desinfileira(){
        if(this.begin === this.end){
            return [false, this.fila[0]];
        }
        let temp = this.fila[this.begin];
        this.begin = (this.begin + 1) % (this.tamanho);
        return [true,temp];
    }

    imprime(){
        for(var i = this.begin; i != this.end; i=(i + 1) % (this.tamanho)){
            console.log(this.fila[i]);
        }
        console.log('\n');
    }
}

f = new Fila();
console.log('Inicio');
console.log(f.desinfileira());
f.enfileira(10);
f.enfileira(2);
f.enfileira(7);
f.enfileira(17);
f.enfileira(3);
f.imprime();
console.log(f.desinfileira());
console.log(f.desinfileira());
console.log(f.desinfileira());
f.imprime();
f.enfileira(99);
f.enfileira(80);
f.enfileira(2);
f.imprime();
console.log(f.enfileira(10));
f.imprime();