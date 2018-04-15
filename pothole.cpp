#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define pb(x) push_back(x)
#define v 210

bool visited[v];
int parent[v];
vector<int> adj[v];
int rescap[v][v]; //Residual Capacity. At first these are the original capacities
int cap[v][v];

void initialize()
{
    for(int i = 0; i < v; i++) {
        for(int j = 0; j < v; j++) {
            rescap[i][j] = 0;
            cap[i][j] = 0;
         }
    }
    for(int i = 0; i < v; i++)
        adj[i].clear();
}

// Implementacion de BFS --> Edmonds-Karp
bool BFS(int chambers,int s,int t)
{
   // Limpiando
    for (int i = 0; i < v; i++) {
      visited[i] = false;
      parent[i] = -1;
    }
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while(!q.empty())
    {
        int temp = q.front();
        q.pop();
        if(temp == t)
            break;
         // We check every Vertex because connections are bidirectional.
        for(int i = 1; i < chambers + 1; i++)
        {
            if(visited[i] == false && rescap[temp][i] > 0)
            {
                q.push(i);
                parent[i] = temp;
                visited[i] = true;
            }
        }
    }
    for (int vertex = t; vertex > -1 ; vertex = parent[vertex])
    {
        int temp = parent[vertex];
        rescap[temp][vertex]--;  // Add/Subtract Original Capacities.
        rescap[vertex][temp]++;
    }
    return (visited[t] == true);
}

int main() {
    int tests;
    cin >> tests;
    while(tests--)
    {
        initialize();
        int chambers, numberOfCorridors, corridor;
        cin >> chambers;
        for(int i = 0; i < chambers - 1; i++)
        {
           cin >> numberOfCorridors;
            for(int j = 0; j < numberOfCorridors; j++)
            {
               cin >> corridor;
               adj[i + 1].pb(corridor);
               // We check if we are at the beginning or our flow it's really simple
               // Then we put our connections capacities at inf
               rescap[i + 1][corridor] = ((i == 0 || corridor == chambers) ? 1:10000);
            }
        }
        int count = 0;
        //We have to count how many people can be sent
        //i.e. how many times BFS can be applied.
        while(BFS(chambers,1,chambers)) count++;
        cout << count << endl;
    }
    return 0;
}
