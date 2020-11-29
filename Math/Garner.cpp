#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
using namespace std;
using ll = long long ;
using P = pair<int,int> ;
using pll = pair<long long,long long>;
constexpr int INF = 1e9;
constexpr long long LINF = 1e17;
constexpr int MOD = 1000000007;
constexpr double PI = 3.14159265358979323846;

inline long long mod(long long x,long long m){
    if((x %= m) < 0) x += m;
    return x;
}

long long gcd(long long i,long long j){
    if(j == 0) return i;
    return gcd(j,i%j);
}

//a*x + b*y =gcd(a,b)を満たすx、yをもとめる
pair<long long,long long> extgcd(long long a,long long b){
    if(b == 0) return {1,0};
    pair<long long,long long> res = extgcd(b,a%b);
    long long x = res.first;
    long long y = res.second;
    return {y,x - (a/b) * y};
}

long long inverse(long long x,long long m){
    pair<long long,long long> res = extgcd(x,m);
    return mod(res.first,m);
}

long long Garner(vector<long long> b,vector<long long> m,long long MOD=-1){
    if(MOD!=-1) m.push_back(MOD);
    vector<long long> mproduct((int)(m.size()),1);
    vector<long long> mtproduct((int)(m.size()),0);
    for(int i=0;i<(int)b.size();i++){
        long long t = mod((b[i] - mtproduct[i]) * inverse(mproduct[i],m[i]),m[i]);
        for(int j=i+1;j<(int)m.size();j++){
            mtproduct[j] += t * mproduct[j];
            mtproduct[j] %= m[j];
            mproduct[j] *= m[i];
            mproduct[j] %= m[i];
        }
    }
    return mtproduct.back();
}

int main(){
    int n;
    cin >> n;
    vector<ll> x(n),y(n);
    rep(i,n) cin >> x[i] >> y[i];
    vector<ll> b,m;
    for(int i=1;i<n;i++){
        for(int j=i+1;j<n;j++){
            
        }
    }

    return 0;
}

/*
まだverifyしていない。
引数に　b と m　を取る。
 x % m = b という関係。
 それを満たす最小の数を MODを取りながら、返す
*/