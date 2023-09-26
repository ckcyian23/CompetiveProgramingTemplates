int tot;
vector<int> siz(n), vis(n);
function<int(int, int)> findCen = [&](int u, int p) -> int {
    siz[u] = 1;
    int hev = 0;
    for (auto v : adj[u]) {
        if (vis[v] || v == p) continue;
        int t = findCen(v, u);
        if (~t) return t;
        siz[u] += siz[v];
        hev = max(hev, siz[v]);
    }
    hev = max(hev, tot - siz[u]);
    if (2 * hev <= tot) {
        if (~p) siz[p] = tot - siz[u];
        return u;
    }
    return -1;
};


vector<Fenwick> f1(n), f2(n);
vector<int> p(n);
function<int(int)> work = [&](int u) {
    tot = siz[u];
    u = findCen(u, -1);
    vis[u] = true;

    f1[u] = f2[u] = tot + 1;

    for (auto v : adj[u]) {
        if (vis[v]) continue;
        p[work(v)] = u;
    }
    return u;
};
siz[0] = n;
p[work(0)] = -1;


vector<int> dep(n), parent(n, -1);
function<void(int)> dfs = [&](int u) {
    if (parent[u] != -1) {
        adj[u].erase(find(adj[u].begin(), adj[u].end(), parent[u]));
    }
    siz[u] = 1;
    for (auto &v : adj[u]) {
        parent[v] = u;
        dep[v] = dep[u] + 1;
        dfs(v);
        siz[u] += siz[v];

        if (siz[v] > siz[adj[u][0]]) {
            swap(v, adj[u][0]);
        }
    }
};
dfs(0);

vector<int> top(n);
dfs = [&](int u) {
    for (int v : adj[u]) {
        top[v] = v == adj[u][0] ? top[u] : v;
        dfs(v);
    }
};
dfs(0);


auto lca = [&](int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = parent[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
};

auto dist = [&](int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
};

auto modify = [&](int u, int k) {
    for (int v = u, lst = -1; v != -1; lst = v, v = p[v]) {
        int d = dist(u, v);
        f1[v].add(d, k);

        if (~lst) {
            f2[lst].add(d, k);
        }
    }
};

auto query = [&](int u, int k) {
    int res = 0;
    for (int v = u, lst = -1; v != -1; lst = v, v = p[v]) {
        int d = dist(u, v);
        res += f1[v].sum(k - d);

        if (~lst) {
            res -= f2[lst].sum(k - d);
        }
    }
    return res;
};


for (int i = 0; i < m; i++) {
    modify(a[i], 1);
}