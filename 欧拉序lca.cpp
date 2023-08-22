int cur = 0;
    vector<int> seq(2 * n);
    vector<int> in(n), parent(n, -1), dep(n);
    function<void(int)> dfs = [&](int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs(v);
            seq[cur++] = u;
        }
    };
    dfs(0);
            
    auto merge = [&](int u, int v) {
        return dep[u] < dep[v] ? u : v;
    };
    vector<vector<int>> st(__lg(2 * n) + 1);
    st[0] = seq;
    for (int k = 1; k <= __lg(2 * n); k++) {
        st[k].resize((2 * n + 1) - (1 << k));
        for (int i = 0; i + (1 << k) <= 2 * n; i++) {
            st[k][i] = merge(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
        }
    }

    auto lca = [&](int u, int v) {
        if (in[u] > in[v]) swap(u, v);
        int l = in[u], r = in[v] + 1;
        int lg = __lg(r - l);
        return merge(st[lg][l], st[lg][r - (1 << lg)]);
    };