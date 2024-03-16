bool is_ancestor(int a, int b, LCA &X) {
    return X.first[a] <= X.first[b] && X.last[b] <= X.last[a];
}

for (auto it : col) {
    int c = it.first;
    // Build virtual tree
    auto vt_nodes = it.second;
    sort(vt_nodes.begin(), vt_nodes.end(), [&](int a, int b) { return X.first[a] < X.first[b]; });
    int sz = vt_nodes.size();
    for (int i = 0; i < sz - 1; i++)
        vt_nodes.push_back(X.lca(vt_nodes[i], vt_nodes[i + 1]));
    sort(vt_nodes.begin(), vt_nodes.end(), [&](int a, int b) { return X.first[a] < X.first[b]; });
    vt_nodes.erase(unique(vt_nodes.begin(), vt_nodes.end()), vt_nodes.end());
    stack<int> s;
    s.push(vt_nodes[0]);
    sz = vt_nodes.size();
    for (int i = 1; i < sz; i++) {
        int curr = vt_nodes[i];
        while (!s.empty() && !is_ancestor(s.top(), curr, X))
            s.pop();
        // Now s.top() is parent of curr. Edge(s.top(), curr) exists
        update(curr, s.top(), c, diff);
        s.push(curr);
    }
}