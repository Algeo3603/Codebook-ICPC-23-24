struct edge {
    int a, b;
    ll cost;
};

ll const inf = 1e17; // n*m*maxW
// +v cycle detection

vector<int> BellmanFord(vector<edge> &e,int n, vector<ll> &d) {
    vector<int> path;
    int v = -1;
    vector<int> parent(n + 1, -1);
    // Add new node 0 to find cycle in each component
    // V-1 phases
    for (int phase = 2; phase <= n + 1; phase++) {
        v = -1;
        for (auto &i : e) {
            if (d[i.a] < inf && d[i.b] > d[i.a] + i.cost) {
                d[i.b] = d[i.a] + i.cost;
                v = i.b;
                parent[i.b] = i.a;
            }
        }
    }
    if (v == -1)
        return path;
    // If we trace back the node n times, we are sure to reach thecause(node in a cycle) 
    for (int i = 0; i < n; i++) 
        v = parent[v];
    int x = v;
    while (true) {
        path.push_back(x);
        x = parent[x];
        if (x == v) {
            path.push_back(x);
            break;
        }
    }
    reverse(path.begin(), path.end());
    return path;
}