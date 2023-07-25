#include <bits/stdc++.h>
using namespace std;
//https://www.luogu.com.cn/problem/P2495 虚树模板题
using i64 = long long;

constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int cur = 0;
    vector<int> dep(n), in(n); 
    vector<array<int, 20>> anc(n), mn(n);
    function<void(int, int)> init = [&](int u, int p) -> void {
        in[u] = cur++;
        for (auto [v, w] : adj[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;

            int k = __lg(dep[v]);
            anc[v][0] = u;
            mn[v][0] = w; 
            for (int i = 1; i <= k; i++) {
                anc[v][i] = anc[anc[v][i - 1]][i - 1];
                mn[v][i] = min(mn[v][i - 1], mn[anc[v][i - 1]][i - 1]);
            }

            init(v, u);
        }
    };
    init(0, -1);

    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        while (dep[u] > dep[v]) u = anc[u][__lg(dep[u] - dep[v])];
        if (u == v) return u;

        for (int i = __lg(dep[u]); i >= 0; i--) {
            if (anc[u][i] != anc[v][i]) {
                u = anc[u][i];
                v = anc[v][i];
            }
        }
        return anc[u][0];
    };

    auto dis = [&](int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        int ret = inf;
        while (u != v) {
            int k = __lg(dep[u] - dep[v]);
            ret = min(ret, mn[u][k]);
            u = anc[u][k];
        }
        return ret;
    };

    int m;

    cin >> m;


    vector<vector<int>> g(n);
    vector<int> mark(n);
    vector<i64> dp(n);
    while (m--) {
        int k;
        cin >> k;
        vector<int> p(k);
        for (int i = 0; i < k; i++) {
            cin >> p[i];
            p[i]--;
            mark[p[i]] = true;
        }
        sort(p.begin(), p.end(), [&](int i, int j) {
            return in[i] < in[j];
        });

        vector<int> stk(2 * k);
        cur = 0;
        for (auto x : p) {
            if (x == 0) continue;
            int r = lca(x, stk[cur]);
            while (stk[cur] != r) {
                int y = stk[cur--];
                if (in[stk[cur]] < in[r]) stk[++cur] = r;
                g[stk[cur]].push_back(y);
            }
            stk[++cur] = x;
        }

        for (int i = 0; i < cur; i++) {
            g[stk[i]].push_back(stk[i + 1]);
        }

        auto DFS = [&](auto self, int u) -> void {
            dp[u] = 0;
            for (auto v : g[u]) {
                self(self, v);
                if (mark[v]) dp[u] += dis(u, v);
                else dp[u] += min<i64>(dis(u, v), dp[v]);
            }
            g[u].clear();
        };
        DFS(DFS, 0);

        cout << dp[0] << '\n';

        for (auto x : p) mark[x] = false;
    }
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}