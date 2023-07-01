#include <bits/stdc++.h>
using namespace std;



template <std::size_t size = 26>
struct Trie{
    std::vector<std::array<int, size>> son;
    std::vector<int> cnt;
    int idx;
    Trie(int s) : son(s), cnt(s), idx(0){}

    void insert(std::string s, int No) {
        int p = 0;
        for(char c : s) {
            int u = c - 'a';
            if(!son[p][u]) son[p][u] = ++idx;
            p = son[p][u];
            assert(p < son.size());
            if(!cnt[p]) cnt[p] = No;
            else cnt[p] = -1;
        }

    }


    int query(std::string s) {
        int p = 0;
        for(char c : s) {
            int u = c - 'a';

            if(!son[p][u]) son[p][u] = ++idx;
            p = son[p][u];
            assert(p < son.size());
        }
        return cnt[p];
    }
};






int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    

    return 0;
}

















