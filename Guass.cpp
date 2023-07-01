
//array : a[n][n + 1]
for (int r = 0, c = 0; c < n; c++) {
    for (int i = r + 1; i < n; i++) {
        if (fabs(a[i][c]) > fabs(a[r][c])) {
            swap(a[r], a[i]);
        }
    }
    if (!a[r][c]) continue;

    for (int i = n; i >= c; i--) {
        a[r][i] /= a[r][c];
    }

    for (int i = 0; i < n; i++) {
        if (i == r) continue;
        for (int j = n; j >= c; j--) {
            a[i][j] -= a[i][c] * a[r][j];
        }
    }

    r++;
}