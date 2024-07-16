#include <bits/stdc++.h>

using namespace std;

// Encontra o menor caminho do primeiro nó até todos os outros nós do grafo
int dijkstra(vector<tuple<int, unsigned long long, bool>> adj[], priority_queue<pair<unsigned long long, int>, vector<pair<unsigned long long, int>>, greater<pair<unsigned long long, int>> > &q, vector<unsigned long long> &distance, vector<bool> &processed) {
    int train_routes_used = 0;

    distance[1] = 0;
    q.push({0, 1});

    while (!q.empty()) {
        int a = q.top().second;
        q.pop();

        if (processed[a]) continue;

        processed[a] = true;

        for (auto u : adj[a]) {
            int b = get<0>(u);
            unsigned long long w = get<1>(u);
            bool tr = get<2>(u);

            if (distance[a] + w < distance[b]) {
                distance[b] = distance[a] + w;
                q.push({distance[b], b});

                if (tr) train_routes_used++;
            }
        }
    }

    return train_routes_used;
}

int main() {
    int n, m, k, u, v, s;
    unsigned long long x, y;

    cin >> n >> m >> k;

    vector<tuple<int, unsigned long long, bool>> adj[n + 1];

    priority_queue<pair<unsigned long long, int>, vector<pair<unsigned long long, int>>, greater<pair<unsigned long long, int>> > q;

    vector<unsigned long long> distance(n + 1, ULLONG_MAX);
    vector<bool> processed(n + 1, false);

    for (int i = 0; i < n; i++) {
        cin >> u >> v >> x;

        adj[u].push_back(make_tuple(v, x, false));
        adj[v].push_back(make_tuple(u, x, false));
    }

    for (int i = 0; i < k; i++) {
        cin >> s >> y;

        adj[1].push_back(make_tuple(s, y, true));
        adj[s].push_back(make_tuple(1, y, true));
    }

    int train_routes_used = dijkstra(adj, q, distance, processed);

    cout << k - train_routes_used << endl;
}
