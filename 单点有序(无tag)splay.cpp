#include <bits/stdc++.h>
using namespace std;

namespace splay {
    const int N = 1e5;
    struct Node {
        int ch[2], p;
        int val, sz, cnt;
    } tr[N + 1];
    int cnt, rt;

    int newNode(int val) {
        int u = ++cnt;
        tr[u].ch[0] = tr[u].ch[1] = tr[u].p = 0;
        tr[u].val = val;
        tr[u].sz = tr[u].cnt = 1;
        return u;
    }

    void pull(int x) {
        tr[x].sz = tr[tr[x].ch[0]].sz + tr[tr[x].ch[1]].sz + tr[x].cnt;
    }

    int get(int x) {
        return tr[tr[x].p].ch[1] == x;
    }
    void link(int x, int y, int way) {
        tr[y].p = x;
        tr[x].ch[way] = y;
    }
    void rotate(int x) {
        int y = tr[x].p, z = tr[y].p;
        int k = get(x);
        link(z, x, get(y));
        link(y, tr[x].ch[1 ^ k], k);
        link(x, y, 1 ^ k);  
        pull(y);
        pull(x);
    }

    void splay(int x, int p = 0) {
        for (int f = tr[x].p; f != p; rotate(x), f = tr[x].p) {
            if (tr[f].p != p) rotate(get(f) == get(x) ? f : x);
        }
        if (!p) rt = x;
    }
    
    

    void insert(int val) {
        int cur = rt, p = 0;
        while (cur) {
            if (tr[cur].val == val) {
                tr[cur].cnt++;
                splay(cur);
                return;
            }
            p = cur;
            cur = tr[cur].ch[val > tr[cur].val];
        }
        int u = newNode(val);
        link(p, u, val > tr[p].val);
        splay(u);

    }
    int kth(int k) {
        int u = rt;
        while (true) {
            if (tr[tr[u].ch[0]].sz >= k) u = tr[u].ch[0];
            else if (tr[tr[u].ch[0]].sz + tr[u].cnt >= k) {
                splay(u);
                return u;
            }
            else k -= tr[tr[u].ch[0]].sz + tr[u].cnt, u = tr[u].ch[1];
        }
    }

    int prev(int x) {
        int cur = rt, ret = rt;
        while (cur) {
            if (tr[cur].val < x) {
                ret = cur;
            }
            cur = tr[cur].ch[tr[cur].val < x];
        }
        splay(ret);
        return ret;
        
    }

    int nex(int x) {
        int cur = rt, ret = rt;
        while (cur) {
            if (tr[cur].val > x) {
                ret = cur;
            }
            cur = tr[cur].ch[tr[cur].val <= x];
        }
        splay(ret);
        return ret;
    }

    void del(int val) {
        int l = prev(val), r = nex(val);
        splay(l, r);
        int u = tr[l].ch[1];
        if (tr[u].cnt > 1) {
            tr[u].cnt--;
            splay(u);
        } else {
            tr[l].ch[1] = 0;
            splay(l);
        }
        
    }

    int rank(int val) {
        insert(val);
        int ret = tr[tr[rt].ch[0]].sz + 1;
        del(val);
        return ret;
    }

}