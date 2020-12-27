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


struct LCA{
    int n;//頂点の数
    int k;//(1<<k)<n
    vector<vector<int>> tree;
    vector<vector<int>> parents;//parents[i][j]:=jの2^iの祖先
    vector<int> depth;//rootからの深さ

    LCA(int n):n(n){
        tree.resize(n);
        depth.resize(n);
        k = 1;
        while((1<<k)<n) ++k;
        parents.assign(k,vector<int>(n,-1));
    }

    //aからbの無向辺を張る
    void add_edge(int a,int b){
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    void init_dfs(int i,int before=-1,int d=0){
        parents[0][i] = before;
        depth[i] = d;
        for(int next:tree[i]){
            if(next == before) continue;
            init_dfs(next,i,d+1);
        }
        return;
    }
    //最初に
    void LCAinit(int root=0){
        init_dfs(root);
        for(int i=1;i<k;i++){
            for(int j=0;j<n;j++){
                if(parents[i-1][j] < 0){
                    parents[i][j] = -1;
                }else{
                    parents[i][j] = parents[i-1][parents[i-1][j]];
                }
            }
        }
        return;
    }
    //aとbのlcaを求める。
    int lca(int a,int b){
        if(depth[a] < depth[b]) swap(a,b);
        for(int i=0;i<k;i++){
            if((depth[a]-depth[b])>>i&1){
                a = parents[i][a];
            }
        }

        if(a == b) return a;
        for(int i=k-1;i>=0;i--){
            if(parents[i][a] != parents[i][b]){
                a = parents[i][a];
                b = parents[i][b];
            }
        }
        return parents[0][a];
    }
};

int main(){
    int n;
    cin >> n;
    LCA LCA(n);
    rep(i,n){
        int p;
        cin >> p;
        rep(j,p){
            int c;
            cin >> c;
            LCA.add_edge(i,c);
        }
    }
    LCA.LCAinit();

    int q;
    cin >> q;
    while(q--){
        int a,b;
        cin >> a >> b;
        cout << LCA.lca(a,b) << endl;
    }

    return 0;
}

