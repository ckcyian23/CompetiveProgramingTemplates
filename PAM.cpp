#include <bits/stdc++.h>
using namespace std;

struct PAM  {
    static constexpr int M = 26;
    int n;
    vector<array<int, M>> t;
    vector<int> link, len, s, diff, slink, trans;
    int cur, cnt;

    PAM(){}
    PAM(int x) {init(x);}

    void init(int x) {
        n = x + 2;
        t.assign(n, {});
        link.assign(n, 0);
        len.assign(n, 0);
        s.assign(n, -1);
        diff.assign(n, 0);
        slink.assign(n, 0);
        trans.assign(n, 0);
        cur = 0;
        cnt = 2;
        len[1] = -1;
        link[0] = link[1] = 1;
    }


    int extend(int p, int c) {
        s[++cur] = c;
        int now = getfail(p);
        if (!t[now][c]) {
            int u = cnt++;
            len[u] = len[now] + 2;
            link[u] = t[getfail(link[now])][c];

            //回文分割 diff slink
            diff[u] = len[u] - len[link[u]];
            slink[u] = (diff[u] == diff[link[u]]) ? slink[link[u]] : link[u];

            //双倍回文 trans
            if (len[u] < 2) trans[u] = link[u];
            else {
                int x = trans[now];
                while (s[cur - len[x] - 1] != s[cur] || len[x] + 2 > len[u] / 2) {
                    x = link[x];
                }
                trans[u] = t[x][c];
            }
            //节点数量
            // val[u] = val[link[u]] + 1;
            t[now][c] = u;
        }
        p = t[now][c];
        return p;
    }

    int getfail(int x) {
        while (s[cur - len[x] - 1] != s[cur]) x = link[x];
        return x;
    }

};


int main() {
    string s = "aaaa";
    int n = s.size();

    PAM pam(n);
    int p = 1;
    vector<int> g(n + 2), dp(n + 1);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        p = pam.extend(p, s[i] - 'a');
        for (int x = p; pam.len[x]; x = pam.slink[x]) {
            g[x] = dp[i + 1 - pam.len[pam.slink[x]] - pam.diff[x]] ;
            if (pam.diff[x] == pam.diff[pam.link[x]]) {
                g[x] = (g[x] + g[pam.link[x]]);
            }
            dp[i + 1] += g[x];
        }
    }

    cout << dp[n] << '\n';
}