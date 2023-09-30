struct eDcc {
    int n;
    vector<vector<pair<int, int>>> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int cur, cnt;
    eDcc() {}
    eDcc(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        stk.clear();
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        cnt = cur = 0;
    }
    void addEdge(int u, int v, int id) {
        adj[u].emplace_back(v, id);
        adj[v].emplace_back(u, id);
    }
 
    void dfs(int u, int from) {
        dfn[u] = low[u] = cur++;
        stk.push_back(u);
 
        for (auto [v, id] : adj[u]) {
            if (dfn[v] == -1) {
                dfs(v, id);
                low[u] = min(low[u], low[v]);
            } else if (id != from) {
                low[u] = min(low[u], dfn[v]);
            }
        }
 
        if (dfn[u] == low[u]) {
            int v;
            do {
                v = stk.back();
                bel[v] = cnt;
                stk.pop_back();
            } while (v != u);
            cnt++;
        }
 
    }
    vector<int> work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i, -1);
            }
        }
        return bel;
    }
};