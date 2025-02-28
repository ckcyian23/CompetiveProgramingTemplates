
vector<int> next(n + 1);
for(int i = 1, j = 0; i < s.size(); i++) {
    while(j && s[i] != s[j]) j = next[j];
    if(s[j] == s[i]) j++;
    next[i + 1] = j;
}

for(int i = 0, j = 0; i < m; i++) {
    while(j && ss[i] != s[j]) j = next[j];
    if(ss[i] == s[j]) j++;
    if(j == n) {
        cout << i - n + 1 << ' ';
        j = next[j];
    }
}