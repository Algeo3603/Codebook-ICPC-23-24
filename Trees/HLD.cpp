int const inf = 1e5; // used as -inf
class HLD
{
public:
    int n;
    vector<int> A;
    SegmentTree seg;
    LCA X;
    vector<int> sb, depth;
    vector<int> id; 
    // We label each vertex, so that only one segtree is needed
    // Labelling is done is such a way that all heavy chain nodes are numbers consecutively. This helps in querying our segtree easily.
    // For a vertex, label all the heavy chain members recursively first, and then only label the other children
    vector<int> chain; // parent of heavy chain above
    vector<int> heavy_child; // stores heavy child of ith node
    
    HLD() {}
    HLD(int n_, vector<int> &arr, vector<vector<int>> &adj) {
        // 1 based arr and adj
        A = arr;
        n = n_;
        X = LCA(1, adj);
        seg = SegmentTree(n);
        sb.resize(n + 1);
        depth.resize(n + 1);
        chain.resize(n + 1);
        id.resize(n + 1);
        heavy_child.resize(n + 1);
        dfs_sb(1, adj);
        int timer = 0;
        dfs_hld(1, 1, timer, adj);
    }

    void dfs_sb(int v, vector<vector<int>> &adj) {
        sb[v] = 1;
        depth[v] = depth[X.parent[v]] + 1;
        int child = -1, sz = -1;
        for (int i : adj[v]) {
            if (i == X.parent[v])
                continue;
            dfs_sb(i, adj);
            sb[v] += sb[i];
            if (sb[i] > sz){
                sz = sb[i];
                child = i;
            }
        }
        heavy_child[v] = child;
    }

    void dfs_hld(int v, int top, int &timer, vector<vector<int>> &adj) {
        id[v] = ++timer;
        chain[v] = top;
        seg.update(1, 1, n, id[v], A[v]);
        if (heavy_child[v] == -1) // leaf node return;
        dfs_hld(heavy_child[v], top, timer, adj);
        for (int i : adj[v]) {
            if (i == heavy_child[v] || i == X.parent[v])
                continue;
            // light edges (top = i)
            dfs_hld(i, i, timer, adj);
        }
    }
    int path_query(int u, int v) {
        int p = X.lca(u, v); // construct answer from [u,p) [v, p) and {p}
        return max({path(u, p), path(v, p), A[p]});
    }

    int path(int u, int p) { // Traverse atmost logn light edges = > Switch chains logn times atmost
        // Return ans from [u, p)
        int ans = -inf;
        while (u != p) { // not gonna happen anyway cause we want [u,p)
            if (chain[u] == u) { // light edge
                ans = max(A[u], ans);
                u = X.parent[u];
            } else if (depth[chain[u]] > depth[p]) { // p and u not in the same chain
            // id of u must be > id of chain parent so query is valid
                ans = max(ans, seg.query(1, 1, n, id[chain[u]], id[u]));
                u = X.parent[chain[u]];
            } else {
                    // // when p == u, l > r seg returns - inf
                ans = max(ans, seg.query(1, 1, n, id[p] + 1, id[u]));
                    break;
            }
        }
        return ans;
    }

    void update(int v, int new_val) {
        seg.update(1, 1, n, id[v], new_val);
        A[v] = new_val;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> A[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    HLD H(n, A, adj);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int s, x;
            cin >> s >> x;
            H.update(s, x);
        }
        else {
            int u, v;
            cin >> u >> v;
            cout << H.path_query(u, v) << " ";
        }
    }
}
