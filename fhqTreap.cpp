mt19937_64 rng(183470);
struct Node {
    int lc, rc;
    int dat, siz;
    i64 w;
} tr[1 << 20];
int cnt, rt;
int newNode(int val) {
    int u = ++cnt;
    tr[u].dat = val;
    tr[u].w = rng();
    tr[u].lc = tr[u].rc = 0;
    tr[u].siz = 1;
    return u;
}
void pull(int u) {
    tr[u].siz = tr[tr[u].lc].siz + tr[tr[u].rc].siz + 1;
}
int merge(int x, int y) {
    if (x == 0 || y == 0) return x | y;
    if (tr[x].w < tr[y].w) {
        tr[x].rc = merge(tr[x].rc, y);
        pull(x);
        return x;
    } else {
        tr[y].lc = merge(x, tr[y].lc);
        pull(y);
        return y;
    }
}
void split(int u, int val, int &x, int &y) {
    if (u == 0) {
        x = y = 0;
        return;
    }
    if (tr[u].dat < val) {
        x = u;
        split(tr[u].rc, val, tr[u].rc, y);
    } else {
        y = u;
        split(tr[u].lc, val, x, tr[u].lc);
    }
    pull(u);
}

void insert(int val) {
    int x, y;
    split(rt, val, x, y);
    rt = merge(x, merge(newNode(val), y));
}
void del(int val) {
    int x, y, z;
    split(rt, val, x, y);
    split(y, val + 1, y, z);
    rt = merge(x, merge(merge(tr[y].lc, tr[y].rc), z));
}
int rk(int val) {
    int x, y, res;
    split(rt, val, x, y);
    res = tr[x].siz;
    rt = merge(x, y);
    return res;
}

int kth(int k) {
    int u = rt;
    while (true) {
        if (tr[tr[u].lc].siz > k) {
            u = tr[u].lc;
        } else if (tr[tr[u].lc].siz + 1 > k) {
            return u;
        } else {
            k -= tr[tr[u].lc].siz + 1;
            u = tr[u].rc;
        }
    }
}

int prev(int val) {
    return kth(rk(val) - 1);
}
int next(int val) {
    return kth(rk(val + 1));
}