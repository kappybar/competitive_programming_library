#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
using ll =  long long ;
using P = pair<ll,ll> ;
const ll INF = 10000000000;
const int MOD = 1000000007;


int v = 100005; //頂点の数
vector<vector<P>> tree(v,vector<P>()); //木
vector<vector<int>> parents; //parents[i][j] := i の　2^j　上の祖先
vector<int> depth(v,0); //rootからの深さ
vector<ll> dist(v,0); //木の辺に重みをつけてrootからの距離もわかる。

void init_dfs(int i,int before=-1,int d=0,ll dis=0){
    parents[i][0] = before;
    depth[i] = d;
    dist[i] = dis;
    for(P next:tree[i]){
        if(next.second == before) continue;
        init_dfs(next.second,i,d+1,dis+next.first);
    }
}

void LCAinit(int root = 0){
    int k = 1;
    while((1<<k)<v) k ++;
    parents.assign(v,vector<int>(k,-1));
    init_dfs(root);
    for(int j = 0;j < k-1;j++){
        for(int i = 0;i < v;i++){
            if(parents[i][j] < 0){
                parents[i][j+1] = -1;
            }else{
                parents[i][j+1] = parents[parents[i][j]][j];
            }
        }
    }
}

int LCA(int x,int y){
    if(depth[x] < depth[y]) swap(x,y);
    int k = parents[0].size();
    for(int i = 0;i < k;i++){
        if((depth[x]-depth[y]) >> i & 1){
            x = parents[x][i];
        }
    }

    if(x == y) return x;
    for(int i = k-1;i >= 0 ;i--){
        if(parents[x][i] != parents[y][i]){
            x = parents[x][i];
            y = parents[y][i];
        }
    }
    return parents[x][0];
}


int main(){
    cin >> v;
    rep(i,v-1){
        ll u,v,w;
        cin >> u >> v >> w;
        tree[u].push_back(P(w,v));
        tree[v].push_back(P(w,u));
    }
    LCAinit();

    /*
    cout << endl;
    rep(i,v) cout << dist[i] << " " ;
    cout << endl;
    */

    int q;
    cin >> q;
    while(q--){
        int x,y,z;
        cin >> x >> y >> z;
        ll res = dist[x]+dist[y]+dist[z];
        //cout << res << endl;
        res -= dist[LCA(x,y)] + dist[LCA(y,z)] + dist[LCA(z,x)];
        cout << res << endl;
    }

    return 0;
}