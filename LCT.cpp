struct LCT {
    constexpr static int N = 200000;

    struct Node {
        int ch[2], p;
        int rev, val;
        int mx;
        Node() : ch{N, N}, p(N), rev(0), val(0) {}
    } tr[N + 1];

    int stk[N + 1];

    void init(int n) {
        for (int i = 0; i < n; i++) {
            tr[i].mx = i;
        }
    }

    void pull(int p) {
        tr[p].mx = p;
        int l = tr[tr[p].ch[0]].mx, &mx = tr[p].mx, r = tr[tr[p].ch[1]].mx;
        if (tr[l].val > tr[mx].val) mx = l;
        if (tr[r].val > tr[mx].val) mx = r;
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

    int get(int x) {
        return tr[tr[x].p].ch[1] == x;
    }

    void add(int x, int y, int way) {
        tr[y].p = x;
        tr[x].ch[way] = y;
    }

    void rotate(int x) {
        int y = tr[x].p, z = tr[y].p;
        int k = get(x);
        
        if (!isRoot(y)) tr[z].ch[get(y)] = x;
        tr[x].p = z;

        add(y, tr[x].ch[1 ^ k], k);
        add(x, y, 1 ^ k);
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
            if (!isRoot(f)) rotate(get(f) == get(x) ? f : x);
        }
    }

    void access(int x) {
        int z = x;
        for (int y = N; x != N; y = x, x = tr[x].p) {
            splay(x);
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
        if (findRoot(y) != x) tr[x].p = y;
    }

    void cut(int x, int y) {
        makeRoot(x);
        if (findRoot(y) == x && tr[y].p == x && tr[y].ch[0] == N) {
            tr[x].ch[1] = tr[y].p = N;
            push(x);
        }
        // access(y);
        // tr[y].ch[0] = tr[x].p = N;
        // pull(y);
    }
} lct;
    