/* Source: https://github.com/gabrielrussoc/competitive-programming/blob/master/spoj/amr11f.cpp
Made to run with C++ instead of C and commented to understand how the solution works
*/

#include <iostream>
#include <map>
#include <set>
#include <limits>
using namespace std;

#define pii pair< int,int >

const int inf = 99999999;

int adj[1001][1001];
map< pii, int > hogwarts;
// This set could be a vector. This is simply easier to manipulate.
set< int > fl[1001];


// We want to run Floyd-Warshall on the vertices that matter to us

int main() {
    int t;
    // Number of test cases
    cin >> t;
    while(t--) {
        int towers, floors, bridges, count;
        cin >> towers >> floors >> bridges;
        count = towers;
        hogwarts.clear();
        // Fill our set with 0s
        for(int i = 0; i < towers; i++) {
            fl[i].clear();
            fl[i].insert(0);
        }
        // Prepare our Djisktra setting distances to infinite
        // And our initial position to 0
        for(int i = 0; i < 2 * (towers + bridges); i++) {
            adj[i][i] = 0;
            for(int j = i + 1; j < 2 * (towers + bridges); j++)
                adj[i][j] = adj[j][i] = inf;
        }
        // The problem states first and last tower are reachable
        adj[0][towers - 1] = adj[towers - 1][0] = 1;
        for(int i = 0; i < towers; i++) {
           // Adjacent towers are connected by default
            adj[i][i + 1] = 1;
            adj[i + 1][i] = 1;
            // Our map is made of connection:number
            hogwarts[pii(i, 0)] = i;
        }
        // Out of bounds
        adj[towers - 1][towers] = inf;
        adj[towers][towers - 1] = inf;
        // Reading bridges connections
        for(int i = 0; i < bridges; i++) {
            int bi, fi, bj, fj, w;
            cin >> bi >> fi >> bj >> fj >> w;
            bi--; bj--; fi--; fj--;
            pii a = pii(bi, fi);
            pii b = pii(bj, fj);
            if(!hogwarts.count(a))
               hogwarts[a] = count++;
            if(!hogwarts.count(b))
               hogwarts[b] = count++;
            int u = hogwarts[a];
            int v = hogwarts[b];
            adj[u][v] = min(adj[u][v], w);
            adj[v][u] = min(adj[v][u], w);
            fl[bi].insert(fi);
            fl[bj].insert(fj);
        }
        // Getting our count and figuring which adjacent paths are shorter
        for(int i = 0; i < towers; i++) {
            for(set<int>::iterator it = ++fl[i].begin(); it != fl[i].end(); it++) {
                int fa = *(--it);
                int fb = *(++it);
                pii a = pii(i, fa);
                pii b = pii(i, fb);
                if(!hogwarts.count(a))
                  hogwarts[a] = count++;
                if(!hogwarts.count(b))
                  hogwarts[b] = count++;
                int u = hogwarts[a];
                int v = hogwarts[b];
                adj[u][v] = min(adj[u][v], abs(fb-fa));
                adj[v][u] = min(adj[v][u], abs(fb-fa));
            }
        }
        // Comparing routes so we can get shortest path
        for(int k = 0; k < count; k++)
            for(int i = 0; i < count; i++)
                for(int j = 0; j < count; j++)
                    adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
        int q;
        cin >> q;
        while(q--) {
           // Reading which distances they are asking us for
            int bi, fi, bj, fj;
            cin >> bi >> fi >> bj >> fj;
            bi--; fi--; bj--; fj--;
            int pa, pb, na, nb;
            set<int>::iterator it;

            it = fl[bi].upper_bound(fi);
            if(it != fl[bi].end()) na = *it;
            else na = -1;
            if(it != fl[bi].begin()) pa = *(--it);
            else pa = -1;

            it = fl[bj].upper_bound(fj);
            if(it != fl[bj].end()) nb = *it;
            else nb = -1;
            if(it != fl[bj].begin()) pb = *(--it);
            else pb = -1;

            // Comparing routes to know which is the shortest
            // In a really complicated manner
            int answer = numeric_limits<int>::max();
            if(na != -1) {
                if(nb != -1) {
                    int d = abs(fi-na) + abs(fj-nb);
                    int u = hogwarts[pii(bi, na)];
                    int v = hogwarts[pii(bj, nb)];
                    answer = min(answer, d + adj[u][v]);
                }
                if(pb != -1) {
                    int d = abs(fi-na) + abs(fj-pb);
                    int u = hogwarts[pii(bi, na)];
                    int v = hogwarts[pii(bj, pb)];
                    answer = min(answer, d + adj[u][v]);
                }
            }
            if(pa != -1) {
                if(nb != -1) {
                    int d = abs(fi-pa) + abs(fj-nb);
                    int u = hogwarts[pii(bi, pa)];
                    int v = hogwarts[pii(bj, nb)];
                    answer = min(answer, d + adj[u][v]);
                }
                if(pb != -1) {
                    int d = abs(fi-pa) + abs(fj-pb);
                    int u = hogwarts[pii(bi, pa)];
                    int v = hogwarts[pii(bj, pb)];
                    answer = min(answer, d + adj[u][v]);
                }
            }
            if(bi == bj)
               answer = min(answer, abs(fi-fj));
            // Printing our answer 
            cout << answer << endl;
        }
    }
}
