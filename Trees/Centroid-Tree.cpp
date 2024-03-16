class CentroidTree {
public:
    int n;
    vector<int> parent; // Centroid tree stored via parent[] vector<int> sb;
    vector<bool> vis;
    vector<vector<int>> adj; // Original tree copy
    CentroidTree() {}
    CentroidTree(vector<vector<int>> &ori) {
        adj = ori;
        n = -1 + adj.size();
        parent.resize(n + 1, -1);
        sb.resize(n + 1);
        vis.resize(n + 1);
        decompose(1);
    }
    void dfs_sb(int v, int p = -1) {
        sb[v] = 1;
        for (int i : adj[v]) {
            if (i == p || vis[i])
                continue;
            dfs_sb(i, v);
            sb[v] += sb[i];
        }
    }
    int find_centroid(int v, int p, int sz) {
        for (int i : adj[v]) {
            if (!vis[i] && i != p && sb[i] > sz / 2)
                return find_centroid(i, v, sz);
        }
        return v;
    }
    void decompose(int v, int p = -1) {
        // Subtree sizes with v as root of a tree in forest
        dfs_sb(v); // thus p = -1
        int c = find_centroid(v, -1, sb[v]);
        vis[c] = true;
        parent[c] = p;
        for (int i : adj[c]) {
            if (!vis[i])
                decompose(i, c);
        }
    }
};
// ------ QUERIES and UPDATES -----
// We store answers to ancestors.
// If node not an ancestor, then ans is in subtree of v
LCA X;
CentroidTree CT;
vector<int> best; // closest red nodedist to i 
void update(int v) { // colour v red
    int x = v;
    while (x != -1) {
        best[x] = min(best[x], X.dist(v, x));
        x = CT.parent[x];
    }
}
int query(int v) {
    int ans = INT_MAX;
    int x = v;
    while (x != -1) {
        ans = min(ans, best[x] + X.dist(v, x));
        x = CT.parent[x];
    }
    return ans;
}