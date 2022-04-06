#include <bits/stdc++.h>
 
using namespace std;
 
int n, m;
const int MAX_N = 50000;
const int INF = 1e9 + 5; /// 1e9 <=> 1 * 10^9
/// 2e9 <=> 2 * 10^9
vector <pair <int, int>> gr[1 + MAX_N]; /// first-> celalalt nod din muchie, second-> costul muchiei
int dist[1 + MAX_N];
bool viz[1 + MAX_N];
void runDijkstra (int source) {
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    priority_queue <pair <int, int>> minDistances; /// first-> -dist[node], second-> node
    dist[source] = 0;
    minDistances.push ({0, source});
    while (minDistances.size () > 0) {
        int node = minDistances.top ().second;
        minDistances.pop ();
        if (viz[node] == false) {
            viz[node] = true;
            for (int i = 0; i < (int) gr[node].size (); i++) {
                int vec = gr[node][i].first;
                int cost = gr[node][i].second;
                if (dist[node] + cost < dist[vec]) {
                    dist[vec] = dist[node] + cost;
                    minDistances.push ({-dist[vec], vec});
                }
            }
        }
    }
}
 
int main () {
    freopen ("dijkstra.in", "r", stdin);
    freopen ("dijkstra.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, cost;
        cin >> x >> y >> cost;
        gr[x].push_back ({y, cost}); /// x ---cost---> y
    }
    runDijkstra (1);
    for (int i = 2; i <= n; i++) {
        if (dist[i] == INF) dist[i] = 0;
        cout << dist[i] << " ";
    }
    cout << "\n";
    return 0;
}
