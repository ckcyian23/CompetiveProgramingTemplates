struct LCT {
    constexpr static int N = 400000;

    struct Node {
        int ch[2], p;
        //val v chain tree, sum: splay + val
        //mx 维护链w max id
        int rev, val;
        int sum, w, mx;
        Node() : ch{N, N}, p(N), rev(0), val(0) {}
    } tr[N + 1];

    int stk[N + 1];

    void init(int n, int m) {
        for (int i = 0; i < n; i++) {
            tr[i].val = 1;
        }
        for (int i = 0; i < n + m; i++) {
            tr[i].mx = i;
        }
        tr[N].mx = N;
    }   

    int maxid(int i, int j) {
        return (tr[tr[i].mx].w > tr[tr[j].mx].w ? tr[i].mx : tr[j].mx);
    }

    void pull(int p) {
        int lc = tr[p].ch[0], rc = tr[p].ch[1];
        tr[p].sum = tr[lc].sum + tr[rc].sum + tr[p].val;
        //mx指向自己
        tr[p].mx = p;
        tr[p].mx = maxid(lc, maxid(p, rc));
    }

    void push(int p) {
        if (tr[p].rev) {
            reverse(tr[p].ch[0]);
            reverse(tr[p].ch[1]);
            tr[p].rev = 0;
        }
    }
    Node& operator[] (int i) {
        return tr[i];
    }

    void reverse(int p) {
        std::swap(tr[p].ch[0], tr[p].ch[1]);
        tr[p].rev ^= 1;
    }

    bool isRoot(int p) {
        return (tr[tr[p].p].ch[0] != p && tr[tr[p].p].ch[1] != p);
    }

    int side(int x) {
        return tr[tr[x].p].ch[1] == x;
    }

    void connect(int x, int y, int side) {
        tr[y].p = x;
        tr[x].ch[side] = y;
    }

    void rotate(int x) {
        int y = tr[x].p, z = tr[y].p;
        int k = side(x);
        
        if (!isRoot(y)) tr[z].ch[side(y)] = x;
        tr[x].p = z;

        connect(y, tr[x].ch[1 ^ k], k);
        connect(x, y, 1 ^ k);
        pull(y), pull(x);
    }

    void splay(int x) {
        int t = x, cnt = 0;
        stk[cnt++] = t;
        while (!isRoot(t)) {
            stk[cnt++] = t = tr[t].p;
        }
        while (cnt) {
            push(stk[--cnt]);
        }
        for (int f = tr[x].p; !isRoot(x); rotate(x), f = tr[x].p) {
            if (!isRoot(f)) rotate(side(f) == side(x) ? f : x);
        }
    }

    void access(int x) {
        int z = x;
        for (int y = N; x != N; y = x, x = tr[x].p) {
            splay(x);

            //v tree pull : minus origin, plus current
            tr[x].val += tr[tr[x].ch[1]].sum;
            tr[x].val -= tr[y].sum;

            tr[x].ch[1] = y;
            pull(x);
        }
        splay(z);
    }

    void makeRoot(int x) {
        access(x);
        reverse(x);    
    }

    int findRoot(int x) {
        access(x);
        while (tr[x].ch[0] != N) push(x), x = tr[x].ch[0];
        splay(x);
        return x;
    }

    void split(int x, int y) {
        makeRoot(x);
        access(y);
    }

    void link(int x, int y) {
        makeRoot(x);
        access(y);
        tr[x].p = y;
        //V pull
        tr[y].val += tr[x].sum;
        pull(y);
    }

    void cut(int x, int y) {
        makeRoot(x);
        // if (findRoot(y) == x && tr[y].p == x && tr[y].ch[0] == N) {
        //     tr[x].ch[1] = tr[y].p = N;
        //     pull(x);
        // }
        access(y);
        tr[y].ch[0] = tr[x].p = N;
        pull(y);
    }

    //只有root tr[x].p == N
    bool connected(int u, int v) {
        access(u);
        access(v);
        return tr[u].p != N;
    }

    int pathMax(int u, int v) {
        split(u, v);
        return tr[v].mx;
    }
    int size(int u) {
        makeRoot(u);
        return tr[u].sum;
    }
} lct;