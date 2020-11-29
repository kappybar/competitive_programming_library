#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
using ll =  long long ;
using P = pair<int,int> ;
const int INF = 1e9;
const int MOD = 1000000007;


int v = 100005; //頂点の数
vector<vector<int>> tree(v,vector<int>()); //木
vector<vector<int>> parents; //parents[i][j] := i の　2^j　上の祖先
vector<int> depth(v,0); //rootからの深さ

void init_dfs(int i,int before=-1,int d=0){
    parents[i][0] = before;
    depth[i] = d;
    for(int next:tree[i]){
        if(next == before) continue;
        init_dfs(next,i,d+1);
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
    rep(i,v){
        int p;
        cin >> p;
        rep(j,p){
            int c;
            cin >> c;
            tree[i].push_back(c);
            tree[c].push_back(i);
        }
    }
    LCAinit();

    int q;
    cin >> q;
    while(q--){
        int a,b;
        cin >> a >> b;
        cout << LCA(a,b) << endl;
    }

    return 0;
}