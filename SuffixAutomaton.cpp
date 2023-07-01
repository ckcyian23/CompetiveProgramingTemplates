#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
 

struct SuffixAutomaton {
    static const int SIZE = 26, N = 4e5;
    struct Node {
        int len = 0;
        int link = 0;
        int next[SIZE]{};
        Node() = default;
    } t[2 * N];
    int cnt;
    SuffixAutomaton() {
        cnt = 1;
        fill(t[0].next, t[0].next + SIZE, 1);
        t[0].len = -1;
    }
    int extend(int p, int c) {
        if (t[p].next[c]) {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1)
                return q;
            int r = ++cnt;
            t[r] = t[q];
            t[r].len = t[p].len + 1;
            t[q].link = r;
            while (t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = ++cnt;
        t[cur].len = t[p].len + 1;
        while (!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        return cur;
    }

    Node& operator[](int i) {
        return t[i];
    }
};


//map
struct SuffixAutomaton {
    static constexpr int N = 5E5;
    struct Node {
        int len = 0;
        int link = 0;
        map<int, int> next;
        Node() = default;
    } t[2 * N];
    int cnt = 1;
    SuffixAutomaton() = default;

    int extend(int p, int c) {
        int cur = ++cnt;
        t[cur].len = t[p].len + 1;
        while (p && !t[p].next.count(c)) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        if (!p) t[cur].link = 1;
        else {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1) t[cur].link = q;
            else {
                int r = ++cnt;
                t[r].len = t[p].len + 1;
                t[r].link = t[q].link;
                t[r].next = t[q].next;

                while (t[p].next[c] == q) {
                    t[p].next[c] = r;
                    p = t[p].link;
                }
                t[cur].link = t[q].link = r;
            }
        }

        return cur;
    }

};