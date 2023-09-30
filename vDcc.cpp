struct vDcc {
    int n;
    vector<vector<int>> adj;
    vector<int> stk;
    vector<int> dfn, low, cut;
    vector<vector<int>> dcc;
    int cur, cnt, root;
    vDcc() {}
    vDcc(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        stk.clear();
        dfn.assign(n, -1);
        low.resize(n);
        dcc.assign(n, {});
        cut.assign(n, 0);
        cnt = cur = 0;
    }
    void addEdge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    void dfs(int u) {
        dfn[u] = low[u] = cur++;
        stk.push_back(u);

        //单独点
        if (adj[u].empty()) {
            dcc[cnt++].push_back(u);
            return;
        }

        int child = 0;
        for (auto v : adj[u]) {
            if (dfn[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    child++;
                    if (u != root || child > 1) {
                        cut[u] = true;
                    }

                    int t;
                    while (true) {
                        t = stk.back();
                        stk.pop_back();
                        dcc[cnt].push_back(t);
                        if (t == v) break;
                    }
                    dcc[cnt++].push_back(u);

                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }

    vector<vector<int>> work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                root = i;
                dfs(i);
            }
        }
        return dcc;
    }
};
