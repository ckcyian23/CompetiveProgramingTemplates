struct seg {
    i64 k, b;
    seg() {}
    seg(i64 k, i64 b) : k(k), b(b) {}
    i64 eval(int x) {
        return (k * x + b);
    }
};

constexpr int N = 1E5;
struct Node {
    int lc, rc;
    seg dat;
    Node(i64 k = 0, i64 b = 0) : dat(k, b) {}
    i64 eval(i64 x) {
        return dat.eval(x);
    }
} tr[N * 60];
int cnt, root;

void modify(int &p, int sl, int sr, int l, int r, seg t) {
    if (p == 0) p = ++cnt;
    int m = (sl + sr) / 2;
    if (sl >= r || sr <= l) return;
    if (l <= sl && sr <= r) {
        if (tr[p].eval(sl) > t.eval(sl) && tr[p].eval(sr) > t.eval(sr)) return;
        if (tr[p].eval(sl) < t.eval(sl) && tr[p].eval(sr) < t.eval(sr)) {
            tr[p].dat = t;
            return;
        }

        if (t.eval(m) > tr[p].eval(m)) {
            swap(tr[p].dat, t);
        }
        if (t.eval(sl) > tr[p].eval(sl)) modify(tr[p].lc, sl, m, l, r, t);
        if (t.eval(sr) > tr[p].eval(sr)) modify(tr[p].rc, m, sr, l, r, t);
        return;
    }
    modify(tr[p].lc, sl, m, l, r, t);
    modify(tr[p].rc, m, sr, l, r, t);
}

seg query(int p, int sl, int sr, int x) {
    if (sl == sr - 1) {
        return tr[p].dat;
    }
    int m = (sl + sr) / 2;
    seg t;
    if (x < m) t = query(tr[p].lc, sl, m, x);
    else t = query(tr[p].rc, m, sr, x);
    if (tr[p].eval(x) > t.eval(x)) t = tr[p].dat;
    return t;
}
