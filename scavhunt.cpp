#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;

vector< vector<int> > ady;  //lista de adyacencia
vector<bool> visitado;    //para nodos visitados
stack<int> pila;
map<string, int> id;
map<int, string> nombre;
int n;

///Ver todo el recorrido del grafo de acuerdo al orden ingresado en la lista de adyacencia
void dfs(int u){

    if (visitado[u])
        return;
    visitado[u] = true;
    for(int v = 0 ; v < ady[u].size() ; ++v)
        dfs(ady[u][v]);
    pila.push(u);

}

void toposort () {

    visitado.clear();
    visitado.resize(n);
    for (int i = 0 ; i < n ; i++)
        if (!visitado[i])
            dfs(i);

}

int main(){

    int casos;
    cin >> casos;
    for (int c = 1 ; c <= casos ; c++) {
        cin >> n;
        int k = 0;
        ady.clear();
        ady.resize(n);
        for (int i = 0 ; i < n-1 ; i++) {
            string desde, hasta;
            cin >> desde >> hasta;
            if (!id.count(desde)) {
                nombre[k] = desde;
                id[desde] = k++;
            }
            if (!id.count(hasta)) {
                nombre[k] = hasta;
                id[hasta] = k++;
            }
            ady[id[desde]].push_back(id[hasta]);
        }
        toposort();
        cout << "Scenario #" << c << ":" << endl;
        while (!pila.empty()) {
            int siguiente = pila.top();
            pila.pop();
            cout << nombre[siguiente] << endl;
        }
        cout << endl;
    }

    return 0;
}