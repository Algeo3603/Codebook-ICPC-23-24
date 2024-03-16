while (!Q.empty()) {
    int v = Q.front();
    Q.pop_front();
    for (auto i : adj[v]) {
        if (dist[v] + i.second < dist[i.first]){
            dist[i.first] = dist[v] + i.second;
            if (i.second == 0)
                Q.push_front(i.first);
            else
                Q.push_back(i.first);
        }
    }
}