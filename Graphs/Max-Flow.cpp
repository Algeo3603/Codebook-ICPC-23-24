// Dinic’s
struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;
    
    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int &cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

// Edmond Karp + min cut
int const siz = 500;
vector<int> adj[siz + 1];
int capacity[siz + 1][siz + 1];

int bfs(int s, int t, vector<int> &parent, int n) {
    // find shortest length Augment Path
    // and return the bottleneck
    fill(parent.begin(), parent.end(), -1); // -1 implies unvisited too
    parent[s] = -2;
    // visited
    queue<pair<int, int>> Q; // second maintains bottleneck so far
    Q.push({s, INT_MAX});

    while (!Q.empty()) {
        int v = Q.front().first;
        int flow = Q.front().second;
        Q.pop();
        if (v == t)
            return flow;
        for (int i : adj[v]) {
            if (parent[i] == -1 && capacity[v][i]) { // residual capacity > 0 
                flow = min(flow, capacity[v][i]);
                parent[i] = v;
                Q.push({i, flow});
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t, int n) {
    vector<int> parent(n + 1, -1);
    int F = 0;
    while (int new_flow = bfs(s, t, parent, n)) {
        F += new_flow;
        // augment the shortest path found
        int v = t;
        bool once = false;
        while (v != s) {
            int p = parent[v];
            capacity[p][v] -= new_flow;
            // residual capacity
            capacity[v][p] += new_flow;
            // reversed edge
            v = p;
        }
    }
    return F;
}

vector<pair<int, int>> minCut(int s, int t, int n) {
    vector<bool> vis(n + 1);
    vis[s] = true;
    queue<int> Q;
    Q.push(s);
    set<int> A;
    A.insert(s);
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int i : adj[v]) {
            if (!vis[i] && capacity[v][i]) {
                vis[i] = true;
                Q.push(i);
                A.insert(i);
            }
        }
    }
    vector<pair<int, int>> ans;
    for (int i : A) {
        for (int j : adj[i]) {
            if (A.find(j) == A.end())
                ans.emplace_back(i, j);
        }
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += 1;
        capacity[v][u] += 1; // 2 WAY STREETS
        // capacity of back edge = 0 => no reversed edges yet = > now flow to source
    }
    ll F = maxFlow(1, n, n);
    cout << F << "\n";
    vector<pair<int, int>> ans = minCut(1, n, n);
}
