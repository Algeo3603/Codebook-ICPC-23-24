vector<pair<int, ll>> adj[siz + 1];
// O(nlogn+mlogn)=O(mlogn)
void dijkstra(int source, vector<ll> &d) {
    set<pair<ll, int>> s;
    d[source] = 0;
    s.insert({0, source});
    while (!s.empty()) {
        int v = s.begin()->second;
        // choosing min unmarked v
        s.erase(s.begin());
        // performing relaxation
        for (auto i : adj[v]) {
            int to = i.first;
            ll wt = i.second;
            if (d[to] >= inf || d[v] + wt < d[to]) {
                s.erase({d[to], to});
                d[to] = d[v] + wt;
                s.insert({d[to], to});
            }
        }
    }
}