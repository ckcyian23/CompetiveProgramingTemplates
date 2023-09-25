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


    vector<int> len(n), parent(n, -1), dep(n);
    function<void(int)> dfs = [&](int u) -> void {
        if (parent[u] != -1) {
            adj[u].erase(find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        for (auto &v : adj[u]) {
            dep[v] = dep[u] + 1;
            parent[v] = u;
            dfs(v);
            len[u] = max(len[u], len[v]);
            if (len[v] > len[adj[u][0]]) swap(adj[u][0], v);
        }

        len[u]++;
    };
    dfs(0);


    vector<int> top(n);
    dfs = [&](int u) -> void {
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs(v);
        }
    };
    dfs(0);

    int cur = 0;
    vector<int> o(n);
    vector<int> dp(n);
    vector<int> ans(n);
    dfs = [&](int u) -> void {
        dp[o[u]] = 1;
        if (!adj[u].empty()) {
            o[adj[u][0]] = o[u] + 1;
            dfs(adj[u][0]);
            ans[u] = ans[adj[u][0]] + 1;
        }

        if (dp[o[u] + ans[u]] <= 1) ans[u] = 0;

        for (auto v : adj[u]) {
            if (v == adj[u][0]) continue;
            o[v] = cur;
            cur += len[v];
            dfs(v);
            for (int i = 0; i < len[v]; i++) {
                dp[o[u] + i + 1] += dp[o[v] + i];
                if (dp[o[u] + i + 1] > dp[o[u] + ans[u]] || (dp[o[u] + i + 1] == dp[o[u] + ans[u]] && i + 1 < ans[u])) {
                    ans[u] = i + 1;
                }
            }
        }

    };
    cur += len[0];
    dfs(0);


    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}