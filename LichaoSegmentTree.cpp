constexpr i64 limit = 0; //numeric_limits<i64>::min();
struct Line {
    i64 k, b;
    Line(i64 k = 0, i64 b = limit) : k(k), b(b) {}
    i64 eval(int x) {
        return (k * x + b);
    }
};

constexpr int N = 1E5;
struct Node {
    int lc, rc;
    Line dat;
    i64 eval(i64 x) {
        return dat.eval(x);
    }
} tr[N * 60];
int cnt, root;

void addLine(int &p, int sl, int sr, Line t) {
    if (p == 0) p = ++cnt;
    int m = (sl + sr) / 2;
    bool fm = t.eval(m) > tr[p].eval(m);
    bool fl = t.eval(sl) > tr[p].eval(sl);
    bool fr = t.eval(sr) > tr[p].eval(sr);
    if (fm) swap(t, tr[p].dat);
    if (fr == fl || sl == sr - 1) {
        return;
    } else if (fl != fm) {
        addLine(tr[p].lc, sl, m, t);
    } else {
        addLine(tr[p].rc, m, sr, t);
    }
}

i64 query(int p, int sl, int sr, int x) {
    if (p == 0) return limit;
    int m = (sl + sr) / 2;
    i64 res = tr[p].eval(x);
    if (x < m) res = max(res, query(tr[p].lc, sl, m, x));
    else res = max(res, query(tr[p].rc, m, sr, x));
    return res;
}
