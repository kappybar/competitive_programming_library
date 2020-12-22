#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define chmin(x,y) x = min((x),(y));
#define chmax(x,y) x = max((x),(y));
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
struct MP{
    int n;
    T s;
    vector<int> a;
    MP(const T& s):s(s){    //文字列or数列
        n = (int)s.size();
        a.assign(n+1,-1);
        a[0] = -1;
        int j = -1;
        for(int i=0;i<n;i++){
            while(j >= 0 && s[i] != s[j]) j = a[j];
            j++;
            a[i+1] = j;
        }
    }
    // tのなかでsがどこに登場するか検索
    vector<int> match(const T& t){
        vector<int> res;
        int j = 0;
        int m = (int)t.size();
        for(int i=0;i<m;i++){
            while(j >= 0 && t[i] != s[j]) j = a[j];
            j++;
            if(j >= n){
                res.push_back(i-n+1);
                j = a[j];
            } 
        }
        return res;
    }
};

int main(){
    int n;
    cin >> n;
    vector<int> a(2*n);
    vector<int> b(n);
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> b[i];
    rep(i,n) a[i+n] = a[i];
    vector<int> aa(2*n);
    vector<int> bb(n-1);
    rep(i,2*n-1) aa[i] = a[i] ^ a[i+1];
    rep(i,n-1) bb[i] = b[i] ^ b[i+1];

    MP<vector<int>> mp(bb);
    vector<int> ans = mp.match(aa);

    for(int p:ans){
        if(p<n) cout << p << " " << (a[p]^b[0]) << endl;
    }

    return 0;
}