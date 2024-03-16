// call for each component
bool check_bipartite(int v, int c) {
    colour[v] = c;
    bool yes = true;
    for (int i : adj[v]) {
        if (colour[i] == c)
            yes = false;
        else {
            if (colour[i] == -1)
                yes &= check_bipartite(i, c ^ 1);
        }
    }
    return yes;
}