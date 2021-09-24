#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define chmin(x,y) x = min((x),(y))
#define chmax(x,y) x = max((x),(y))
#define popcount(x) __builtin_popcountll(x)
using namespace std;
using ll = long long ;
using P = pair<int,int> ;
using pll = pair<long long,long long>;
const int INF = 1e9;
const long long LINF = 1e17;
const int MOD = 1000000007;
//const int MOD = 998244353;
const double PI = 3.14159265358979323846;

template<typename T>
void zeta_sub(vector<T> &f) {
    int n = (int)f.size();
    for (int i = 1;i < n;i <<= 1) {
        for (int j = 0;j < n; j++) {
            if (j&i) f[j] += f[j^i];
        }
    }
}

template<typename T>
void mebius_sub(vector<T> &f) {
    int n = (int)f.size();
    for (int i = 1;i < n;i <<= 1) {
        for (int j = 0;j < n; j++) {
            if (j&i) f[j] -= f[j^i];
        }
    }
}

template<typename T>
void zeta_sup(vector<T> &f) {
    int n = (int)f.size();
    for (int i = 1;i < n;i <<= 1) {
        for (int j = 0;j < n; j++) {
            if (!(j&i)) f[j] += f[j|i];
        }
    }
}

template<typename T>
void mebius_sup(vector<T> &f) {
    int n = (int)f.size();
    for (int i = 1;i < n;i <<= 1) {
        for (int j = 0;j < n; j++) {
            if (!(j&i)) f[j] -= f[j|i];
        }
    }
}


template<typename T>
vector<T> and_convolution(vector<T> a,vector<T> b) {
    assert(a.size() == b.size());
    zeta_sup(a);
    zeta_sup(b);
    int n = (int)a.size();
    for(int i = 0;i < n; i++) a[i] *= b[i];
    mebius_sup(a);
    return a;
}

template<typename T>
vector<T> or_convolution(vector<T> a,vector<T> b) {
    assert(a.size() == b.size());
    zeta_sub(a);
    zeta_sub(b);
    int n = (int)a.size();
    for(int i = 0;i < n; i++) a[i] *= b[i];
    mebius_sub(a);
    return a;
}

int main(){
    vector<int> a = {1,2,3,4,5,6,7,8};
    vector<int> b = {8,7,6,5,4,3,2,1};
    auto c = and_convolution(a,b);
    auto d = or_convolution(a,b);

    vector<int> c_(8,0),d_(8,0);
    rep(i,8)rep(j,8){
        c_[i&j] += a[i] * b[j];
        d_[i|j] += a[i] * b[j];
    }

    assert(c == c_);
    assert(d == d_);
    return 0;
}