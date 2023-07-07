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

    //初始化 rt， tot
    int rt = -1, tot = n;

    vector<int> vis(n), siz(n);
    function<void(int, int)> getRt = [&](int u, int p) {
        int wgt = 0;
        siz[u] = 1;
        for (auto v : adj[u]) {
            if (vis[v] || v == p) continue;
            getRt(v, u);
            if (rt != -1) return; //(1)找到就立即退出，因为改过重心p的大小
            siz[u] += siz[v];
            wgt = max(wgt, siz[v]);
        }
        wgt = max(tot - siz[u], wgt);

        if (wgt <= tot / 2) {
            if (p != -1) siz[p] = tot - siz[u]; //对于重心w，我们分治的是他所联通的各个部分，需要维护tot
            //tot获取由w所直接连向的点获取，所以得到w后，如果p存在，就改正大小并由(1)直接退出。
            rt = u;
        }
    };




    int ans = 0;
    function<void(int)> calc = [&](int u) -> void {
        
    };

    auto solve = [&](auto &self, int u) -> void {
        //calc计算过当前节点的贡献
        //一般是 ans += calc(u) :容斥思想
        vis[u] = 1;
        for (auto v : adj[u]) {
            if (vis[v]) continue;

            //ans -= calc(v)


            //重置 rt 和 tot， 找根并且继续递归
            rt = -1;
            tot = siz[v];
            getRt(v, -1);
            self(self, rt);
        }
    };
    //先找重心再对重心计算
    getRt(0, -1);
    solve(solve, rt);


    return 0;
}