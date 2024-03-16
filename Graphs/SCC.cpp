vector<int> adj[siz + 1], adj_rev[siz + 1];
vector<int> order, component; // order: list of nodes with descending exit time
vector<bool> vis;
vector<int> condensed[siz + 1]; // Condensation graph 

void dfs1(int v) {
    vis[v] = true;
    for (int i : adj[v])
        if (!vis[i])
            dfs1(i);
    order.push_back(v);
}

void dfs2(int v) {
    vis[v] = true;
    component.push_back(v);
    for (int i : adj_rev[v])
        if (!vis[i])
            dfs2(i);
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> ans(n + 1);
    int k = 0;
    vis.assign(n + 1, false);
    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }
    // Get list of vertices sorted in descending order of exit time 
    for (int i = 1; i <= n; i++) if (!vis[i]) dfs1(i);
    reverse(order.begin(), order.end());
    vis.assign(n + 1, false);
    for (int i : order) {
        if (!vis[i]) {
            dfs2(i);
            k++;
            for (int j : component)
                ans[j] = k;
            // -- condense --
            int representative = component[0];
            ll sum = 0;
            for (int j : component) {
                root[j] = representative;
                sum += A[j];
            }
            A[representative] = sum;
            // ----
            component.clear();
        }
    }
    // -- condense --
    for (int i = 1; i <= n; i++) {
        for (int j : adj[i]) {
            if (root[j] != root[i])
            condensed[root[i]].push_back(root[j]);
        }
    }
}