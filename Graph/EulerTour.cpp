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

int n;
vector<vector<pll>> tree(n);
vector<int> idx(n);//オイラーツアーしたときの頂点のindex
vector<int> euler;//オイラーツアーした時の辺 sum[0:i)でrootからの距離になる

void dfs(int v,int before){
    idx[v] = (int)euler.size();//idx
    for(pll j:tree[v]){
        if(j.second == before) continue;
        euler.push_back(j.first);//+
        dfs(j.second,v);
        euler.push_back(-j.first);//-
    }
    return ;
}

//雰囲気