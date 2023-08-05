#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

namespace PTP {
    constexpr int N = 200000 << 7;
    struct Node {
        int lc, rc, sz, rev, val;
        i64 sum;
        u64 w;
        Node(){}; 
    } tr[N];

    int cnt;
    int newNode(int val = 0) {
        int u = ++cnt;
        tr[u].lc = tr[u].rc = tr[u].rev = 0;
        tr[u].sz = 1;
        tr[u].sum = tr[u].val = val;
        tr[u].w = rng();
        return u;
    }
    
    int copy(int u) {
        if (u == 0) return 0;
        int v = newNode();
        tr[v] = tr[u];
        return v;
    }

    void pull(int u) {
        int lc = tr[u].lc, rc = tr[u].rc;
        tr[u].sz = tr[lc].sz + tr[rc].sz + 1;
        tr[u].sum = tr[u].val + tr[lc].sum + tr[rc].sum;
    }

    void push(int u) {
        if (tr[u].rev) {
            tr[u].lc = copy(tr[u].lc);
            tr[u].rc = copy(tr[u].rc);
            swap(tr[u].lc, tr[u].rc);
            tr[tr[u].lc].rev ^= 1;
            tr[tr[u].rc].rev ^= 1;
            tr[u].rev = 0;
        }
    }

    void split(int p, int k, int &x, int &y) {
        if (!p) {
            x = y = 0;
            return;
        }
        push(p);
        if (tr[tr[p].lc].sz < k) {
            k -= tr[tr[p].lc].sz + 1;
            x = copy(p);
            split(tr[x].rc, k, tr[x].rc, y);
            pull(x);
        } else {
            y = copy(p);
            split(tr[y].lc, k, x, tr[y].lc);
            pull(y);
        }
    }

    int merge(int x, int y) {
        if (!x || !y) return x + y;
        push(x), push(y);
        if (tr[x].w > tr[y].w) {
            tr[x].rc = merge(tr[x].rc, y);
            pull(x);
            return x;
        } else {
            tr[y].lc = merge(x, tr[y].lc);
            pull(y);
            return y;
        }
    }

    void reverse(int &p, int l, int r) {
        int x, y, z;
        split(p, r, y, z);
        split(y, l, x, y);
        tr[y].rev ^= 1;
        p = merge(merge(x, y), z);
    }

    void erase(int &p, int k) {
        int x, y, z;
        split(p, k, x, y);
        split(y, 1, y, z);
        p = merge(x, z);
    }
    void insert(int &p, int k, int val) {
        int x, y;
        split(p, k, x, y);
        p = merge(merge(x, newNode(val)), y);
    }

    i64 sum(int &p, int l, int r) {
        int x, y, z;
        split(p, r, y, z);
        split(y, l, x, y);
        i64 res = tr[y].sum;
        p = merge(merge(x, y), z);
        return res;
    }

};

using namespace PTP;

