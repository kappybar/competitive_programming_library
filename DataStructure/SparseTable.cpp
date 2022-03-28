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
struct SparseTable{
    vector<vector<T>> table;
    vector<int> log_table;
    SparseTable(vector<T> v){
        int n = (int)v.size();
        log_table.assign(n+1,0);
        for(int i=2;i<=n;i++) log_table[i] = log_table[i>>1]+1;
        table.assign(log_table[n]+1,vector<T>(n,0));
        for(int i=0;i<n;i++) table[0][i] = v[i];
        for(int i=1;i<=log_table[n];i++){
            for(int j=0;(j+(1<<(i-1)))<n;j++){
                table[i][j] = max( table[i-1][j], table[i-1][j+(1<<(i-1))] );
            }
        }
    }
    //[l,r)
    T query(int l,int r){
        int len = r-l;
        return max(table[log_table[len]][l],table[log_table[len]][r-(1<<log_table[len])]);
    }
};