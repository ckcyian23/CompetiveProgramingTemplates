#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int inf = 1e9;

struct Treap {
    static const int N = 1e5;
    int rt, tot;
    struct Node {
        int son[2] = {};
        int val = 0;
        int rnd = rand();
        int sz = 0;
        int cnt = 0;
        Node() = default;
    } tr[N + 1];
    
    Treap() : rt(0), tot(0) {}
    
    int newNode(int val) {
        tr[++tot].val = val;
        tr[tot].sz = 1;
        tr[tot].cnt = 1;
        return tot;
    }
    
    void pull(int p) {
        tr[p].sz = tr[tr[p].son[0]].sz + tr[tr[p].son[1]].sz + tr[p].cnt;
    }
    
    void rotate(int &p, int way) {
        int q = tr[p].son[way ^ 1];
        tr[p].son[way ^ 1] = tr[q].son[way];
        tr[q].son[way] = p;
        pull(q), pull(p);
        p = q;
    }
    
    void insert(int &p, int val) {
        if (p == 0) p = newNode(val);
        else if (tr[p].val == val) tr[p].cnt++;
        else if (tr[p].val > val) {
            insert(tr[p].son[0], val);
            if (tr[tr[p].son[0]].rnd > tr[p].rnd)
                rotate(p, 1);
        } else {
            insert(tr[p].son[1], val);
            if (tr[tr[p].son[1]].rnd > tr[p].rnd)
                rotate(p, 0);
        }
        pull(p);
    }
    
    void remove(int &p, int val) {
        if (!p) return;
        else if (tr[p].val == val) {
            if (tr[p].cnt > 1) tr[p].cnt--;
            else if (tr[p].son[0] || tr[p].son[1]) {
                if (!tr[p].son[0] || tr[p].son[1] && 
                    tr[tr[p].son[1]].rnd > tr[tr[p].son[0]].rnd) {
                    rotate(p, 0);
                    remove(tr[p].son[0], val);
                } else {
                    rotate(p, 1);
                    remove(tr[p].son[1], val);
                }
            } else {
                p = 0;
            }
        } else if (tr[p].val > val) {
            remove(tr[p].son[0], val);
        } else {
            remove(tr[p].son[1], val);
        }
        
        pull(p);
    }
    
    int rank(int &p, int val) {
        if (!p) return 0;
        if (tr[p].val == val) return tr[tr[p].son[0]].sz + 1;
        if (tr[p].val > val) return rank(tr[p].son[0], val);
        return rank(tr[p].son[1], val) + tr[tr[p].son[0]].sz + tr[p].cnt;
    }
    
    int kth(int &p, int k) {
        if (!p) return inf;
        if (tr[tr[p].son[0]].sz >= k) return kth(tr[p].son[0], k);
        if (tr[tr[p].son[0]].sz + tr[p].cnt >= k) return tr[p].val;
        else return kth(tr[p].son[1], k - tr[tr[p].son[0]].sz - tr[p].cnt);
    }
    
    int pre(int &p, int val) {
        if (!p) return -inf;
        if (tr[p].val == val) return pre(tr[p].son[0], val);
        if (tr[p].val < val) return max(tr[p].val, pre(tr[p].son[1], val));
        return pre(tr[p].son[0], val);
    }
    int next(int &p, int val) {
        if (!p) return inf;
        if (tr[p].val == val) return next(tr[p].son[1], val);
        if (tr[p].val > val) return min(tr[p].val, next(tr[p].son[0], val));
        return next(tr[p].son[1], val);
    }
    int lower_bound(int &p, int val) {
        if (!p) return inf;
        if (tr[p].val == val) return val;
        if (tr[p].val > val) return min(tr[p].val, lower_bound(tr[p].son[0], val));
        return lower_bound(tr[p].son[1], val);
    }
    
    int lower_bound(int val) {
        return lower_bound(rt, val);
    }
    int pre(int val) {
        return pre(rt, val);
    }
    int next(int val) {
        return next(rt, val);
    }
    int kth(int k) {
        return kth(rt, k);
    }
    int rank(int val) {
        return rank(rt, val);
    }
    void remove(int val) {
        remove(rt, val);
    }
    void insert(int val) {
        insert(rt, val);
    }
    
};