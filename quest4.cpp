#include <iostream>
#include <vector>
using namespace std;

const int MAX = 120;
vector < int > edges[MAX];
bool visited[MAX];
int Left[MAX], Right[MAX];

bool dfs(int u) {
	if(visited[u])
		return false;
	visited[u] = true;
	int len = edges[u].size(), i, v;
	for(i = 0; i < len; i++) {
		v = edges[u][i];
		if(Right[v] == -1) {
			Right[v] = u;
			 Left[u] = v;
			return true;
		}
	}
	for(i = 0; i < len; i++) {
		v = edges[u][i];
		if(dfs(Right[v])) {
			Right[v] = u, Left[u] = v;
			return true;
		}
	}
	return false;
}

// Our matching algorithm that calls dfs
int match() {
	int i, value = 0;
	for (i = 0; i < MAX; i++)
		Left[i] = Right[i] = -1;
		visited[i] = 0;
	bool done;
	do {
		done = true;
		for (i = 0; i < MAX; i++)
			visited[i] = 0;
		for(i = 0; i < MAX; i++) {
			if(Left[i] == -1 && dfs(i)) {
				done = false;
			}
		}
	} while(!done);
	for(i = 0; i < MAX; i++)
		value += (Left[i]!=-1);
	return value;
}


int main() {
	int t, n, i, x, y;
	cin >> t;
	while(t--) {
		cin >> n;
		for(i = 0; i < MAX; i++)
			edges[i].clear();
		for(i = 0; i < n; i++) {
			cin >> x >> y;
			edges[x].push_back(y);
		}
		cout << match() << endl;
	}
	return 0;
}
