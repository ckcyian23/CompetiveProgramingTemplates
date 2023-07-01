#include<bits/stdc++.h>
using namespace std;


//单点修改，区间查询, 左闭右开(jiangly类似同款)

//注意 assert(l != r)并且  modify(x) : assert(0 <= x < n) 如果大于等于n会修改到n - 1处
//Data的构造函数注意满足要求，特别是默认构造问题



template<class Data, class Merge = std::plus<Data>>
struct SegmentTree {
    const int n;
    const Merge merge;
    vector<Data> a;

    SegmentTree(int n) : n(n), a(n << 2), merge(Merge()) {}
    SegmentTree(const vector<Data>& info) : SegmentTree(info.size()) {
        build(info);
    }
    void build(const vector<Data>& info, int p, int sl, int sr) {
        if (sr - sl == 1) {
            a[p] = info[sl];
            return;
        }
        int mid = sl + sr >> 1;
        build(info, p << 1, sl, mid);
        build(info, p << 1 | 1, mid, sr);
        pull(p);
    }
    void build(const vector<Data>& info) {
        build(info, 1, 0, n);
    }
    void pull(int p) {
        a[p] = merge(a[p << 1], a[p << 1 | 1]);
    }
    Data query(int l, int r, int p, int sl, int sr) {
        if (l <= sl && sr <= r) {
            return a[p];
        }
        int mid = sl + sr >> 1;
        if(mid >= r) return query(l, r, p << 1, sl, mid);
        if(mid <= l) return query(l, r, p << 1 | 1, mid, sr);
        return merge(query(l, r, p << 1, sl, mid), query(l, r, p << 1 | 1, mid, sr));
    }
    Data query(int l, int r) {
        return query(l, r, 1, 0, n);
    }
    void modify(int x, const Data& v, int p, int sl, int sr) {
        if (sr - sl == 1) {
            a[p] = v;
            return;
        }
        int mid = sl + sr >> 1;
        if (x < mid) modify(x, v, p << 1, sl, mid);
        else modify(x, v, p << 1 | 1, mid, sr);
        pull(p);
    }
    void modify(int s, const Data& v) {
        modify(s, v, 1, 0, n);
    }


};

struct Max {
    int x;
    Max(int x = 0) : x(x) {}
};

Max operator+(const Max& a, const Max& b) {
    return std::max(a.x, b.x);
}