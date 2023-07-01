#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int N = 1E5;

struct Node {
    int lc = -1, rc = -1;
} tr[N << 2];
vector<pair<int, int>> adj[N << 2];
i64 dis[N << 2];
int vis[N << 2];

int cnt, rt1, rt2;

void build(int &p1, int &p2, int l, int r) {
    if (l == r - 1) {
        p1 = p2 = l;
        return;
    }
    p1 = cnt++;
    p2 = cnt++;
    int m = (l + r) / 2;
    build(tr[p1].lc, tr[p2].lc, l, m);
    build(tr[p1].rc, tr[p2].rc, m, r);

    adj[tr[p1].lc].emplace_back(p1, 0);
    adj[tr[p1].rc].emplace_back(p1, 0);

    adj[p2].emplace_back(tr[p2].lc, 0);
    adj[p2].emplace_back(tr[p2].rc, 0);
}

void link(int p, int sl, int sr, int l, int r, int x, int w, int t) {
    if (sl >= l && sr <= r) {
        //0:点对区间 1:区间对点
        if (t == 0) {
            adj[x].emplace_back(p, w);
        } else {
            adj[p].emplace_back(x, w);
        }
        return;
    } 

    int m = (sl + sr) / 2;
    if (m > l) link(tr[p].lc, sl, m, l, r, x, w, t);
    if (m < r) link(tr[p].rc, m, sr, l, r, x, w, t);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, s;
    cin >> n >> q >> s;
    s--;

    cnt = n;
    build(rt1, rt2, 0, n);
        
    while (q--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            adj[u].emplace_back(v, w);
        } else if (opt == 2) {
            int v, l, r, w;
            cin >> v >> l >> r >> w;
            v--, l--;
            //点对区间
            link(rt2, 0, n, l, r, v, w, 0);
        } else {
            int v, l, r, w;
            cin >> v >> l >> r >> w;
            v--, l--;
            //区间对点
            link(rt1, 0, n, l, r, v, w, 1);
        }
    }

    fill(dis, dis + cnt, -1);
    fill(vis, vis + cnt, 0);

    priority_queue<pair<i64, int>> h;
    h.emplace(0, s);
    while (!h.empty()) {
        auto [d, u] = h.top();
        h.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        dis[u] = -d;
        for (auto [v, w] : adj[u]) {
            if (!vis[v] && (dis[v] == -1 || dis[v] > w - d)) {
                dis[v] = w - d;
                h.emplace(d - w, v);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << dis[i] << " \n"[i == n - 1];
    }

    return 0;
}