#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;

vector< vector< int > > ady;  //lista de adyacencia
vector< bool > visitado;    //para nodos visitados
stack< int > pila;
map< string, int > id;
map< int, string > nombre;
int n;

const int MAX = 111111;
int M, N, indeg[MAX];
set< int >  nextNode;
vector<int>g[MAX];
vector< int > order;
int cnt;

void dfs(int u)
{
    if (visitado[u])
        return;
    visitado[u] = true;
    for(int v = 0 ; v < ady[u].size() ; ++v)
        dfs(ady[u][v]);
    pila.push(u);

}

void toposort ()
{
    visitado.clear();
    visitado.resize(n);
    for (int i = 0 ; i < n ; i++)
        if (!visitado[i])
            dfs(i);
}

int main()
{
    int i, j, k, v, u;
    cin >> N >> M;
    for (int i = 0 ; i <= M ; i++) {
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
        if (c > 1)
            cout << endl;
        cout << "Scenario #" << c << ":" << endl;
        while (!pila.empty()) {
            int siguiente = pila.top();
            pila.pop();
            cout << nombre[siguiente] << endl;
        }
    }

    return 0;
}
