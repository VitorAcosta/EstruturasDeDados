#include <iostream>

using namespace std;
#define MAX 100
class LES{
public:
    int v[MAX]; //Vetor com 100 posições.
    int n; //Variavel de controle n.
    LES(){ //Método construtor.
        this->n = 0; //Inicializa o n.
    }
    bool insere(int valor){//Método que insere valores.
        if(n >= MAX){ //Verifica se há espaços para inserir novos valores.
            return false;
        }
        //Procura local de inserção
        int pos;
        for(pos = 0; v[pos] <= valor ;pos++);

        //Deslocamento de elementos
        for(int j = n-1; j >= pos; j--){
            v[j+1] = v[j];
        }

        //Inserção do novo elemento
        v[pos] = valor;

        //Retorno e incremento
        n++;
        return true;
    }
    void imprime(){
        for(int i = 0; i < n; i++){
            cout << v[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    cout << "Hello, World!" << endl;
    LES l;
    l.insere(10);
    l.imprime();
    l.insere(3);
    l.imprime();
    l.insere(7);
    l.imprime();
    l.insere(1);
    l.imprime();
    return 0;
}
