#include <bits/stdc++.h>
using namespace std;
//普通（维护了一个sz可以省略）并查集
struct DSU {
    int n;
    vector<int> f, sz;
    DSU(){};
    DSU(int n) : n(n), f(n), sz(n, 1) {
        iota(f.begin(), f.end(), 0);
    }
    void init(int k) {
        n = k;
        f.resize(n);
        sz.assign(n, 1);
        iota(f.begin(), f.end(), 0);
    }
    int get(int x) {
        if(f[x] != x) f[x] = get(f[x]);
        return f[x];
    }
    bool same(int x, int y) {
        return get(x) == get(y);
    }
    int size(int x) {
        return sz[get(x)];
    }
    bool merge(int x, int y) {
        x = get(x), y = get(y);
        if(x == y) return false;
        sz[x] += sz[y];
        f[y] = x;
        return true;
    }
    bool isRoot(int x) {
        return get(x) == x;
    }

};

//带权并查集
struct DSU {
    const int n;
    vector<int> p, d;
    DSU(int n) : n(n), p(n), d(n) {iota(p.begin(), p.end(), 0);}
    array<int, 2> get(int u) {
        if(p[u] != u) {
            auto [v, y] = get(p[u]);
            p[u] = p[v];
            d[u] += y;
        }
        return {p[u], d[u]};
    }
    bool merge(int u, int v, int dist) {
        auto [ru, x] = get(u);
        auto [rv, y] = get(v);
        if(ru == rv) {
            return y == x + dist;
        };
        d[rv] = x + dist - y;
        p[rv] = ru;
        return true;
    }
};
