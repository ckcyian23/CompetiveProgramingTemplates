constexpr int N = 1E6;
int tr[N][26], cnt[N], fail[N];
int cntNodes;
int newNode() {
    int u = ++cntNodes;
    memset(tr[u], 0, sizeof tr[u]);
    fail[u] = cnt[u] = 0;
    return u;
}

void insert(const string &s) {
    int u = 1;
    for (auto ch : s) {
        int t = ch - 'a';
        if (!tr[u][t]) tr[u][t] = newNode();
        u = tr[u][t];
    }
    cnt[u]++;
}

void build() {
    queue<int> q;
    q.push(1);
    fill(tr[0], tr[0] + 26, 1);
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (tr[u][i]) fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]);
            else tr[u][i] = tr[fail[u]][i];
        }
    }
}