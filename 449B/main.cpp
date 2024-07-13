#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, k, u, v, x, s, y;

    cin >> n >> m >> k;

    vector<pair<int, int>> adj[n + 1];

    for (int i = 0; i < n; i++) {
        cin >> u >> v >> x;

        adj[u].push_back({v, x});
        adj[v].push_back({u, x});
    }

    vector<pair<int, int>> tr(k);

    for (int i = 0; i < n; i++) {
        cin >> s >> y;

        tr[i] = {s, y};

//        adj[1].push_back({s, y});
//        adj[s].push_back({1, y});
    }

    priority_queue<pair<int, int>> q;

    vector<int> distance(n + 1, INT_MAX);
    vector<bool> processed(n + 1, false);

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

    int train_routes_used = 0;

    for (int i = 0; i < k; i++) {
        if (tr[i].second < distance[tr[i].first])
            train_routes_used++;
    }

    cout << k - train_routes_used << endl;
}
