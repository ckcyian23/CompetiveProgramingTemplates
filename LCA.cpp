#include <bits/stdc++.h>
using namespace std;


struct LCA {
    vector<vector<int>> g;
    vector<vector<int>> fa;
    vector<int> dep;
    //__lg(n) + 1， 保证一个点时，也有个fa[u][0]
    LCA(int n, int root = 0) : g(n), fa(n, vector<int>(__lg(n) + 1)), dep(n) {}
    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void init(int u = 0, int f = 0) {
        dep[u] = dep[f] + 1;
        fa[u][0] = f;
        for(int i = 1; (1 << i) <= dep[u]; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for(auto v : g[u]) {
            if(v == f) 
                continue;
            init(v, u);
        }
        
    }
    int lca(int u, int v) {
        if(dep[u] < dep[v])
            swap(u, v);
        int d = dep[u] - dep[v];
        for(int i = 0; (1 << i) <= d; i++) {
            if((1 << i) & d)
                u = fa[u][i];
        }
        if(u == v) return u;
        for(int i = __lg(dep[u]); i >= 0; i--) {
            if(fa[u][i] ==fa[v][i]) continue;
            u =fa[u][i], v = fa[v][i];
        }
        return fa[u][0];
    }

};







int main() {

    return 0;
}