#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>
using namespace std;

#define pii pair< int,int >
#define mp(x,y) make_pair(x,y) 
#define grafo vector< vector< pair< int, int >>>

// Djisktra más entendible que encontre. Lo unico extraño que tiene viene de limits.
// Pero asi no tienen que declarar infinito, es bello.
int dijkstra(int start, grafo graph, int end)
{
    vector<int> route(graph.size(), numeric_limits<int>::max());
    priority_queue< pii, vector< pii >, greater< pii > > pqueue;
    pqueue.push(mp(0, start));
    while(pqueue.size())
    {
        int weight = pqueue.top().first;
        int dest = pqueue.top().second;
        pqueue.pop();
        if(dest == end)
            return min(route[dest], weight);
        if(route[dest] > weight)
        {
            route[dest] = weight;
            for (int i = 0; i < graph[dest].size(); ++i)
            {
                pqueue.push(mp(route[dest] + graph[dest][i].second, graph[dest][i].first));
            }
        }
    }
    return numeric_limits<int>::max();
}


int main()
{
    int tests;
    cin >> tests;
    while(tests--) {
        // Nuestro dictionario ciudad:id y grafo
        map<string, int> cityDictionary;
        vector<vector<pair<int, int> > > graph;
        int numberOfCities;
        cin >> numberOfCities;
        for (int id = 0; id < numberOfCities; ++id)
        {
            // Llenamos nuestro diccionario
            string city;
            cin >> city;
            cityDictionary[city] = id;
            // Nuestro grafo esta conformado por nodos con conexiones
            graph.push_back(vector<pair<int, int> >());
            int connections;
            cin >> connections;
            // Leemos los costos de nuestras conecciones
            for(int i = 0; i < connections; i++)
            {
                int dest;
                int weight;
                cin >> dest >> weight;
                // -1 porque nuestro diccionario comienza en 0
                // Defini mp más arriba para que se viera organizado
                graph[id].push_back(mp(dest - 1, weight));
            }
        }
        // Nuestras casos pregunta
        int cases;
        cin >> cases;
        for (int i = 0; i < cases; ++i)
        {
            // Inicio y destino
            string source;
            string dest;
            cin >> source >> dest;
            int answer;
            answer = dijkstra(cityDictionary[source], graph, cityDictionary[dest]);
            cout << answer << '\n';
        }
    }
    return 0;
}
