//初始化 crt(重心根)， tot
int crt = -1, tot = n;

vector<int> vis(n), siz(n);
function<bool(int, int)> getRt = [&](int u, int p) -> bool {
    int wgt = 0;
    siz[u] = 1;
    for (auto v : adj[u]) {
        if (vis[v] || v == p) continue;
        if (getRt(v, u)) return true;
        siz[u] += siz[v];
        wgt = max(wgt, siz[v]);
    }
    wgt = max(tot - siz[u], wgt);

    if (wgt <= tot / 2) {
        if (p != -1) siz[p] = tot - siz[u]; //对于重心w，我们分治的是他所联通的各个部分，需要维护tot
        //tot获取由w所直接连向的点获取，所以得到w后，如果p存在，就改正大小并由(1)直接退出。
        crt = u;
        return true;
    }
    return false;
};

int ans = 0;
function<void(int)> calc = [&](int u) -> void {

};

//点分树可以在这里存储结构和要维护信息
auto solve = [&](auto &self, int u) -> void {
    //calc计算过当前节点的贡献
    //一般是 ans += calc(u) :容斥思想
    vis[u] = 1;
    for (auto v : adj[u]) {
        if (vis[v]) continue;

        //ans -= calc(v)


        //重置 crt 和 tot， 找根并且继续递归
        crt = -1;
        tot = siz[v];
        getRt(v, -1);
        self(self, crt);
    }
};
//先找重心再对重心计算
getRt(0, -1);
solve(solve, crt);
