vector<int> *vec[maxn];
int cnt[maxn];
void dfs(int v, int p, bool keep) {
    int mx = -1, bigChild = -1;
    for (auto u : g[v])
        if (u != p && sz[u] > mx)
            mx = sz[u], bigChild = u;
    for (auto u : g[v])
        if (u != p && u != bigChild)
            dfs(u, v, 0);
    if (bigChild != -1)
        dfs(bigChild, v, 1), vec[v] = vec[bigChild];
    else
        vec[v] = new vector<int>();
    vec[v]->push_back(v);
    cnt[col[v]]++;
    for (auto u : g[v])
        if (u != p && u != bigChild)
            for (auto x : *vec[u]) {
                cnt[col[x]]++;
                vec[v]->push_back(x);
            }
    // now cnt[c] is the number of vertices in subtree of vertex v that has color c.
    // note that in this step *vec[v] contains all of the subtree ofvertex v. 
        if (keep == 0) for (auto u : *vec[v])
            cnt[col[u]]--;
}

// HLD style
int cnt[maxn];
bool big[maxn];
void add(int v, int p, int x) {
    cnt[col[v]] += x;
    for (auto u : g[v])
        if (u != p && !big[u])
            add(u, v, x)
}

void dfs(int v, int p, bool keep)
{
    int mx = -1, bigChild = -1;
    for (auto u : g[v])
        if (u != p && sz[u] > mx)
            mx = sz[u], bigChild = u;
    for (auto u : g[v])
        if (u != p && u != bigChild)
            dfs(u, v, 0); // run a dfs on small childs and clear them from cnt 
        if (bigChild != -1)
            dfs(bigChild, v, 1),
        big[bigChild] = 1; // bigChild marked as big and not cleared from cnt
        add(v, p, 1);
    // now cnt[c] is the number of vertices in subtree of vertex v that has color c.You can answer the queries easily.
    if (bigChild != -1)
        big[bigChild] = 0;
    if (keep == 0)
        add(v, p, -1);
}