
mt19937 rng(58158);
constexpr int N = 4E5;
struct Node {
    int lc = N, rc = N;
    int dat = 0;
    int siz = 0;
    int p = N;
    int w = rng();
} tr[N + 1];
int rt = N;

int tag[N + 1];

void pull(int x) {
    tr[x].siz = tr[tr[x].lc].siz + tr[tr[x].rc].siz + 1;
    tr[tr[x].lc].p = tr[tr[x].rc].p = x;
}

void apply(int x, int v) {
    if (x == N) return;
    tr[x].dat = v;
    tag[x] = v;
}

void push(int x) {
    if (tag[x] != -1) {
        apply(tr[x].lc, tag[x]);
        apply(tr[x].rc, tag[x]);
        tag[x] = -1;
    }
}
void update(int x) {
    if (x == N) return;
    update(tr[x].p);
    push(x);
}
//按值划分，前面 < v
void splitV(int u, int v, int &x, int &y) {
    if (u == N) {
        x = y = N;
        return;
    }
    push(u);
    if (tr[u].dat < v) {
        x = u;
        splitV(tr[u].rc, v, tr[u].rc, y);
    } else {
        y = u;
        splitV(tr[u].lc, v, x, tr[u].lc);
    }
    pull(u);
}
//按照大小划分，前面k个，后面n - k
void splitK(int u, int k, int &x, int &y) {
    if (u == N) {
        x = y = N;
        return;
    }
    push(u);
    if (tr[tr[u].lc].siz < k) {
        k -= tr[tr[u].lc].siz + 1;
        x = u;
        splitK(tr[u].rc, k, tr[u].rc, y);
    } else {
        y = u;
        splitK(tr[u].lc, k, x, tr[u].lc);
    }
    pull(u);
}

int merge(int x, int y) {
    if (x == N) return y;
    if (y == N) return x;

    if (tr[x].w < tr[y].w) {
        push(x);
        tr[x].rc = merge(tr[x].rc, y);
        pull(x);
        return x;
    } else {
        push(y);
        tr[y].lc = merge(x, tr[y].lc);
        pull(y);
        return y;
    }
}
//查编号的位置在哪
int rnk(int x) {
    update(x);
    int res = tr[tr[x].lc].siz;
    while (tr[x].p != N) {
        if (tr[tr[x].p].rc == x) {
            res += tr[tr[tr[x].p].lc].siz + 1;
        }
        x = tr[x].p;
    }
    return res;
}

//以上为维护区间（值的区间）赋值并记录原来编号

//以下为旧版部分代码
void insert(int val) {
    int x, y;
    splitV(rt, val, x, y);
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


