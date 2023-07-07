template<class T>
void fmt(vector<T> &a) {
    int n = a.size();
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                int u = a[i + j], v = a[i + j + k];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
}

template<class T>
void ifmt(vector<T> &a) {
    int n = a.size();
    fmt(a);
    for (int i = 0; i < n; i++) {
        a[i] /= n;
    }
}
