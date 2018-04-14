#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int n, contdfs;
vector< vector<int> > ady;
vector<bool> visitado;

void leer_grafo() {
	ady.clear(); 
	cin >> n; 
	ady.resize(n); 
	int m;
	cin >> m; 
	while (m--) { 
		int a, b;
		cin >> a >> b; 
		ady[a].push_back(b);
		ady[b].push_back(a); 	
	}
}

void dfs(int inicial) {
	stack<int> pila;
	pila.push(inicial); 
	while (!pila.empty()) { 
		int actual = pila.top() ;
		pila.pop(); 
		if (visitado[actual]) continue; 
		visitado[actual] = true; 
		for (int i = 0 ; i < ady[actual].size() ; i++) 
			pila.push(ady[actual][i]); 
	}
	contdfs++;
}

int main () {
	int cases;
	cin >> cases;
	while (cases--){
		contdfs=0;
		leer_grafo();
		visitado.resize(n);
		for (int i = 0 ; i < n ; i++) visitado[i] = false; 
		dfs(0);
		int marcador = 0;
		while(marcador < n){
		 	if (visitado[marcador]== false) dfs(marcador);
		 	marcador ++;
		 }
		cout << contdfs <<endl;
	}

	return 0;
}
