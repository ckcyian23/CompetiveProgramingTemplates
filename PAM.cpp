struct PAM  {
    static constexpr int M = 26;
    const int n;
    vector<array<int, M>> t;
    vector<int> link, len, s, diff, slink;
    int cur, cnt;

    PAM(int x) : n(x + 2), t(n), link(n), len(n), s(n, -1), diff(n), slink(n) {
        cur = 0;
        cnt = 2;
        len[1] = -1;
        link[0] = link[1] = 1;
    }


    int extend(int p, int c) {
        s[++cur] = c;
        int now = getfail(p);
        if(!t[now][c]) {
            int u = cnt++;
            len[u] = len[now] + 2;
            link[u] = t[getfail(link[now])][c];
            diff[u] = len[u] - len[link[u]];
            slink[u] = (diff[u] == diff[link[u]]) ? slink[link[u]] : link[u];
            // val[u] = val[link[u]] + 1;
            t[now][c] = u;
        }
        p = t[now][c];
        return p;
    }

    int getfail(int x) {
        while(s[cur - len[x] - 1] != s[cur]) x = link[x];
        return x;
    }

};
