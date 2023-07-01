#include <bits/stdc++.h>
using namespace std;

using i64 = long long;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }


    int rt = -1, tot = n;
    vector<int> vis(n), siz(n);
    function<void(int, int)> getRt = [&](int u, int p) {
        int mx = 0;
        siz[u] = 1;
        for (auto v : adj[u]) {
            if (vis[v] || v == p) continue;
            getRt(v, u);
            if (rt != -1) return;
            siz[u] += siz[v];
            mx = max(mx, siz[v]);
        }
        mx = max(tot - siz[u], mx);
        if (mx <= tot / 2) {
            rt = u;
            if (p >= 0) siz[p] = tot - siz[u];
        }
    };




    int ans = 0;
    function<void(int)> calc = [&](int u) -> void {
        
    };

    auto solve = [&](auto &self, int u) -> void {
        //calc计算过当前节点的贡献
        vis[u] = 1;
        for (auto v : adj[u]) {
            if (vis[v]) continue;
            rt = -1;
            tot = siz[v];
            getRt(v, -1);
            self(self, rt);
        }
    };
    getRt(0, -1);
    solve(solve, rt);


    return 0;
}