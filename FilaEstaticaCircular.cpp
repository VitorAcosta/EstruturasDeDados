#include <iostream>
#define MAX 5
using namespace std;

class Fila{
public:
    /**
     * Cria-se um vetor com a posição máxima + 1 por conta do sentinela.
     * int i é o inicio da fila, int f é o fim da fila.
     */
    int v[MAX + 1];
    int i;
    int f;
    Fila(){
        i = 0;
        f = 0;
    }
    //Em inglês chamado de inqueue.
    bool enfileira(int x){
        /**
         * Se a próxima posição indicada como fim da lista, for igual ao inicio da lista.
         * Quer dizer que não pode inserir, pois o próximo espaço é o sentinela.
         */
        if((f+1) % (MAX + 1) == i){
            return false;
        }
        v[f] = x; //Insere na lista.
        /**
         * Incrementa o fim da fila e se for necessário faz a rotação.
         */
        f = (f+1) % (MAX + 1);

        return true;
    }
    /**
     * Método que retira itens da fila.
     * @param ok Um ponteiro para booleano que verifica se a remoção foi efetuada com sucesso.
     * @return Retorna o valor que foi retirado da fila.
     */
    //Em inglês: dequeue.
    int desenfileira(bool* ok=NULL){
        /**
         * O if(ok) verifica se o ponteiro de booleano, passado pelo chamador do método,
         * está definido como True (pedindo o retorno), e também indica se o retorno é um número que foi
         * removido com sucesso ou não.
         * No caso, se a lista estiver vazia, perceba que o ponteiro irá apontar para false, retornando -1,
         * porém, a remoção não foi bem sucedida.
         */
        if(i == f) { //Verifica se o inicio é igual ao fim da fila, ou seja, não existe elementos.
            if(ok)
                *ok = false;
            return v[0];
        }
        int temp = v[i]; //Esse valor será o que devemos excluir (o primeiro valor da fila)
        i = (i+1) % (MAX + 1); //Incrementa
        if(ok)
            *ok = true;
        return temp;
    }

    void limpa(){
        i=f;
    }

    void imprime(){
        /**
         * O inicio desse for (j) deve ser igual ao inicio da fila (i),
         * O inicio deve ser diferente do fim
         * E o incremento será dado com o resto da divisão para rodar a fila caso necessário.
         * (isso é, caso o j fique maior que o f).
         */
        for(int j = i; j != f ; j=(j+ 1) % (MAX + 1))
            cout << v[j] << " ";
        cout << endl;
    }
};


int main() {
    cout << "Inicio" << endl;
    Fila f;
    f.enfileira(10);
    f.enfileira(2);
    f.enfileira(7);
    f.enfileira(17);
    f.enfileira(3);
    f.imprime();
    cout << f.desenfileira() << endl;
    cout << f.desenfileira() << endl;
    cout << f.desenfileira() << endl;
    f.enfileira(99);
    f.enfileira(80);
    f.enfileira(2);

    cout << f.desenfileira() << endl;
    cout << f.desenfileira() << endl;
    cout << f.desenfileira() << endl;
    cout << f.desenfileira() << endl;
    cout << f.desenfileira() << endl;
    cout << f.desenfileira() << endl;
    return 0;
}
