#include <bits/stdc++.h>
using namespace std;

struct SA {
    static const int N = 1E6;
    using cArray = int[N + 5];
    int n, m;
    cArray sa, hgt, rk, x, y, c, p;

    template <class T>
    void init(const T &s) {
        n = s.size(), m = max<int>(n, 'z') + 1;
        for(int i = 0; i < n; i++) x[i] = s[i], y[i] = i;
        rSort();
        for(int k = 1; k <= n; k <<= 1) {
            int cur = 0;
            for(int i = n - k; i < n; i++) y[cur++] = i;
            for(int i = 0; i < n; i++)
                if(sa[i] >= k) y[cur++] = sa[i] - k;
            rSort();
            rk[sa[0]] = cur = 0;
            for(int i = 1; i < n; i++) {
                int a = sa[i], b = sa[i - 1];
                if(a >= n - k || b >= n - k || x[a] != x[b] || x[a + k] != x[b + k]) cur++;
                rk[a] = cur;
            }
            if(cur == n - 1) break;
            for (int i = 0; i < n; i++) x[i] = rk[i];
            // swap(x, rk);
            m = ++cur;
        }
        for(int i = 0, k = hgt[0] = 0; i < n; i++) {
            if(!rk[i]) continue;
            if(k) k--;
            int j = sa[rk[i] - 1];
            while(i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            hgt[rk[i]] = k;
        }
    }
    void rSort() {
        for(int i = 0; i < n; i++) c[x[i]]++;
        for(int i = 1; i <= m; i++) p[i] = p[i - 1] + c[i - 1], c[i - 1] = 0;
        for(int i = 0; i < n; i++) sa[p[x[y[i]]]++] = y[i];
        p[0] = 0;
    }
} sa;

//xi 第i个后缀的关键字， yi，以第二关键字排名，排名为i的后缀   
//sa 给排名返回位置，  hgt给排名，返回这个排名和前一位最长相同前缀长度，     rk给位置，返回排名

//abababab
//sa:7 5 3 1 8 6 4 2
//hgt:0 2 4 6 0 1 3 5




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    sa.init(s);
    for(int i = 0; i < s.size(); i++)
        cout << sa.sa[i] + 1 << ' ';
    return 0;
}