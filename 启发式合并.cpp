
auto addv = [&](int x, int t) {

};

function<void(int, int)> addTree = [&](int u, int t) -> void {
    addv(u, t);
    for (auto v : adj[u]) {
        addTree(v, t);
    }
};

function<void(int)> dfs = [&](int u) {
    for (auto v : adj[u]) {
        if (v != adj[u][0]) {
            dfs(v);
            addTree(v, -1);

        }
    }

    if (!adj[u].empty()) {
        dfs(adj[u][0]);
        for (auto v : adj[u]) {
            if (v != adj[u][0]) {
                addTree(v, 1);
            }
        }
    }
    addv(u, 1);

};
dfs(0);
addTree(0, -1);
