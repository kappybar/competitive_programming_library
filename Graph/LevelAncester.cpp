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

struct LevelAncester {
    int n,logn,root;
    bool built;
    vector<vector<int>> G;
    vector<vector<int>> ancester;
    LevelAncester(int n,int root):n(n),root(root),built(false) {
        G.resize(n);
        logn = 0;
        while((1<<logn) < n) logn++;
        ancester.assign(n,vector<int>(logn,-1));
    }

    void add_edge(int a,int b) {
        G[a].push_back(b);
        G[b].push_back(a);
    }

    void build(void) {
        built = true;
        vector<int> par(n);
        auto dfs = [&](auto&& dfs,int i,int p = -1) -> void {
            par[i] = p;
            for(int j:G[i]){
                if(j == p) continue;
                dfs(dfs,j,i);
            }
        };
        dfs(dfs,root);
        for(int i=0;i<n;i++) ancester[i][0] = par[i];
        for(int j=0;j<logn;j++){
            for(int i=0;i<n;i++){
                if (ancester[i][j] == -1) continue;
                ancester[i][j+1] = ancester[ancester[i][j]][j];
            }
        }
    }

    // vから祖先方向にk進んだ先の頂点
    int LA(int v,int k){
        assert(built);
        for(int i=30;i>=0;i--){
            if (k>>i&1) {
                v = ancester[v][i];
                if (v == -1) return -1;
            }
        }
        return v;
    }
};