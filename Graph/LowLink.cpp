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

//橋、関節点を検出
struct LowLink{
    int n;
    int c;
    vector<vector<int>> graph;
    vector<int> ord,low;
    vector<bool> seen;
    vector<int> Art;//関節点index
    vector<pair<int,int>> bridges;//橋index
    LowLink(int n):n(n){
        graph.resize(n);
        ord.resize(n);
        low.resize(n);
        seen.assign(n,false);
        c=0;
    }
    void add_edge(int a,int b){
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    void dfs(int i,int p=-1){
        seen[i] = true;
        ord[i] = low[i] = c++;
        int cnt = 0;
        for(int j:graph[i]){
            if(!seen[j]){
                dfs(j,i);
                ++cnt;
                low[i] = min(low[i],low[j]);
                if(p != -1 && ord[i] <= low[j]) Art.push_back(i);
                if(ord[i] < low[j]) bridges.emplace_back(min(i,j),max(i,j));
            }else if(j != p){
                low[i] = min(low[i],ord[j]);
            }
        }
        if(p == -1 && cnt > 1) Art.push_back(i);
        return;
    }
    //関節点 橋をもとめる
    void main(){
        c = 0;
        dfs(0);
        sort(Art.begin(),Art.end());
        Art.erase(unique(Art.begin(),Art.end()),Art.end());
        sort(bridges.begin(),bridges.end());
        bridges.erase(unique(bridges.begin(),bridges.end()),bridges.end());
        return ;
    }
    //関節点
    vector<int> Articulation(){
        if(c==0) main();
        return Art;
    }
    //橋
    vector<pair<int,int>> Bridge(){
        if(c==0) main();
        return bridges;
    }
};

int main(){
    int v,e;
    cin >> v >> e;
    LowLink G(v);
    rep(i,e){
        int a,b;
        cin >> a >> b;
        G.add_edge(a,b);
    }
    vector<P> ans = G.Bridge();
    for(auto a:ans) cout << a.first << " " << a.second << endl;
    return 0;
}