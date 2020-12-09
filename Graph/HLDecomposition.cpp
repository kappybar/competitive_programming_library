#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
using namespace std;
using ll = long long ;
using P = pair<int,int> ;
using pll = pair<long long,long long>;
constexpr int INF = 1e9;
constexpr long long LINF = 1e17;
constexpr int MOD = 1000000007;


struct HLDecomposition{
    int n;
    int hld_size;
    vector<vector<int>> tree;
    vector<int> size,depth,head,hld,pre,parent;
    HLDecomposition(int n):n(n),hld_size(0){ 
        tree.resize(n);
        size.resize(n); //部分木のサイズ
        head.resize(n); //各列の一番深さが浅い頂点
        hld.resize(n); // hldの一列に並べた
        pre.resize(n); // preorder
        depth.resize(n); 
        parent.resize(n); 
    }

    void add_edge(int a,int b){
        tree[a].push_back(b);
        tree[b].push_back(a);
        return;
    }

    void build(int root = 0){
        size_(root,-1);
        hld_(root,root,-1);
        return;
    }

    void hld_(int v,int h,int par){
        pre[v] = hld_size;
        hld[hld_size++] = v;
        head[v] = h;

        if((int)tree[v].size() == 1 && par != -1) return;
        hld_(tree[v][0],h,v);

        for(int i=1;i<(int)tree[v].size();i++){
            if(tree[v][i] == par) continue;
            hld_(tree[v][i],tree[v][i],v);
        }
        return;
    }

    int size_(int v,int par,int d=0){
        depth[v] = d;
        parent[v] = par;
        int sz = 1;
        int mx_sz = 0;
        for(int &c:tree[v]){
            if(par == c) continue;
            int s = size_(c,v,d+1);
            sz += s;
            if(s > mx_sz){
                swap(c,tree[v][0]);
                mx_sz = s;
            }
        }
        size[v] = sz;
        return size[v];
    }


    //uとvの間のpathのクエリ
    //[l,r]は配列hld上でのindexを表している。not verified
    vector<pair<int,int>> query(int u,int v){
        vector<pair<int,int>> res;
        while(head[v] != head[u]){
            if(depth[head[u]] > depth[head[v]]) swap(u,v);
            res.emplace_back(pre[head[v]],pre[v]);
            v = parent[head[v]];
        }
        res.emplace_back(min(pre[u],pre[v]),max(pre[u],pre[v]));
        return res;
    }

    //Lowest Common Ancester verified
    int LCA(int u,int v){
        while(head[v] != head[u]){
            if(depth[head[u]] > depth[head[v]]) swap(u,v);
            v = parent[head[v]];
        }
        if(depth[u] > depth[v]) swap(u,v);
        return u;
    }
};

int main(){
    int n;
    cin >> n;
    HLDecomposition T(n);
    rep(i,n-1){
        int x,y;
        cin >> x >> y;
        --x;--y;
        T.add_edge(x,y);
    }
    T.build();
    int q;
    cin >> q;
    rep(i,q){
        int a,b;
        cin >> a >> b;
        --a;--b;
        int lca = T.LCA(a,b);
        cout << T.depth[a] + T.depth[b] - 2*T.depth[lca] + 1 << '\n';
        //cout << a << " " << b << lca << endl;
    }
    return 0;
}