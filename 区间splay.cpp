#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int N = 5e5;

int cache[N + 10];
int cnt = N + 4;

namespace splay {

    struct Node {
        int sum;
        int v;
        int lmax, rmax, mmax;
        int sz;
        int p;
        int ch[2];
    } tr[N + 5];

    bool rev[N + 5];
    bool eq[N + 5];

    int rt;

    int newNode(int val) {
        int u = cache[cnt--];
        tr[u].mmax = tr[u].v = tr[u].sum = val;
        tr[u].lmax = tr[u].rmax = max(val, 0);
        tr[u].sz = 1;
        tr[u].ch[0] = tr[u].ch[1] = tr[u].p = 0;
        eq[u] = false;
        rev[u] = false;
        return u;
    }

    void pull(int x) {
        int l = tr[x].ch[0], r = tr[x].ch[1];
        tr[x].sz = tr[l].sz + tr[r].sz + 1;

        tr[x].sum = tr[l].sum + tr[r].sum + tr[x].v;
        tr[x].lmax = max(tr[l].lmax, tr[l].sum + tr[x].v + tr[r].lmax);
        tr[x].rmax = max(tr[r].rmax, tr[r].sum + tr[x].v + tr[l].rmax);
        tr[x].mmax = max({tr[l].rmax + tr[r].lmax + tr[x].v, tr[l].mmax, tr[r].mmax});
        
    }

    int build(int sl, int sr, const vector<int> &a) {
        if (sl > sr) return 0;
        int mid = sl + sr >> 1;
        int u = newNode(a[mid]);
        int l = build(sl, mid - 1, a), r = build(mid + 1, sr, a);
        tr[l].p = tr[r].p = u;
        tr[u].ch[0] = l;
        tr[u].ch[1] = r;
        pull(u);
        return u;
    }

    int get(int x) {
        return tr[tr[x].p].ch[1] == x;
    }

    void link(int x, int y, int way) {
        tr[y].p = x;
        tr[x].ch[way] = y;
    }

    void apply(int x, int v1, int v2, int val) {
        if (!x) return;
        if (v1) {
            swap(tr[x].ch[0], tr[x].ch[1]);
            swap(tr[x].lmax, tr[x].rmax);
        }
        if (v2) {
            tr[x].v = val;
            tr[x].sum = tr[x].sz * val;
            tr[x].lmax = tr[x].rmax = max(tr[x].sum, 0);
            tr[x].mmax = val > 0 ? tr[x].sum : val;
            eq[x] = 1;
        }
        rev[x] ^= v1;
    }
    void push(int x) {
        apply(tr[x].ch[0], rev[x], eq[x], tr[x].v);
        apply(tr[x].ch[1], rev[x], eq[x], tr[x].v);
        rev[x] = 0;
        eq[x] = 0;
    }

    void rotate(int x) {
        if (!x) return;
        int y = tr[x].p, z = tr[y].p;
        int k = get(x);
        link(z, x, get(y));
        link(y, tr[x].ch[1 ^ k], k);
        link(x, y, 1 ^ k);
        pull(y), pull(x);
    }

    int splay(int x) {
        for (int f = tr[x].p; f; rotate(x), f = tr[x].p) {
            if (tr[f].p) {
                rotate(get(f) == get(x) ? f : x);
            } 
        }
        return rt = x;
    }

    int kth(int k) {
        int u = rt;
        // int kk = k;
        while (true) {
            push(u);
            if (k <= tr[tr[u].ch[0]].sz) u = tr[u].ch[0];
            else if (tr[tr[u].ch[0]].sz + 1 == k) {
                splay(u);
                return u;
            } else {
                
                k -= tr[tr[u].ch[0]].sz + 1;
                u = tr[u].ch[1];
            }
        }

    }

    //返回引用，方便区间操作
    int& range(int l, int r) {
        l = kth(l + 1), r = kth(r + 2);
        if (tr[l].p != r) {
            rotate(l);
        }
        return tr[l].ch[1];
    }
    void rangePull() {
        pull(tr[rt].ch[0]);
        pull(rt);
    }

    void rangeApply(int l, int r, int v1, int v2, int val) {
        int x = range(l, r);
        apply(x, v1, v2, val);
        rangePull();
    }

    void del(int l, int r) {
        int &x = range(l, r);
        queue<int> q;
        q.push(x);
        x = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (!u) continue;
            cache[++cnt] = u;
            q.push(tr[u].ch[0]);
            q.push(tr[u].ch[1]);
        }
        rangePull();
    }

    void insert(int x, const vector<int> &a) {
        int &u = range(x, x);
        u = build(0, a.size() - 1, a);
        tr[u].p = tr[rt].ch[0];
        rangePull();
    }
    int rangeSum(int l, int r) {
        return tr[range(l, r)].sum;
    }
    int maxSeg() {
        return tr[rt].mmax;
    }
    
    void output(int u = rt) {
        if (!u) return;
        push(u);
        output(tr[u].ch[0]);
        if (tr[u].v != -inf)
            cout << tr[u].v << ' ';
        output(tr[u].ch[1]);
    }
}