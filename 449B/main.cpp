#include <bits/stdc++.h>

using namespace std;

// Encontra o menor caminho do primeiro nó até todos os outros nós do grafo
void dijkstra(vector<pair<int, int>> adj[], priority_queue<pair<int, int>> &q, vector<int> &distance, vector<bool> &processed) {
    distance[1] = 0;
    q.push({0, 1});

    while (!q.empty()) {
        int a = q.top().second;
        q.pop();

        if (processed[a]) continue;

        processed[a] = true;

        for (auto u : adj[a]) {
            int b = u.first, w = u.second;

            if (distance[a] + w < distance[b]) {
                distance[b] = distance[a] + w;
                q.push({-distance[b], b});
            }
        }
    }
}

int main() {
    unsigned int n, m, k, u, v, x, s, y;

    cin >> n >> m >> k;

    vector<pair<int, int>> adj[n + 1];

    priority_queue<pair<int, int>> q;

    vector<int> distance1(n + 1, INT_MAX), distance2(n + 1, INT_MAX);
    vector<bool> processed1(n + 1, false), processed2(n + 1, false);

    vector<pair<int, int>> tr(k);

    for (int i = 0; i < n; i++) {
        cin >> u >> v >> x;

        adj[u].push_back({v, x});
        adj[v].push_back({u, x});
    }

    dijkstra(adj, q, distance1, processed1);

    for (int i = 0; i < k; i++) {
        cin >> s >> y;

        tr[i] = {s, y};

        adj[1].push_back({s, y});
        adj[s].push_back({1, y});
    }

    dijkstra(adj, q, distance2, processed2);

    int train_routes_used = 0;

    for (int i = 1; i <= n; i++) {
        if (distance2[i] < distance1[i])
            train_routes_used++;
    }

    cout << k - train_routes_used << endl;
}
