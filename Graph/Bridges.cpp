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
int v = 100005,e;
int c = 0;
vector<vector<int>> graph(v,vector<int>());
vector<bool> seen(v,false);
vector<int> ord(v);
vector<int> low(v);
vector<P> bridges;

void dfs(int i,int par=-1){
    seen[i] = true;
    ord[i] = low[i] = c++;

    for(int j:graph[i]){
        if(!seen[j]){
            dfs(j,i);
            low[i] = min(low[i],low[j]);
            if(ord[i] < low[j]) bridges.push_back(P(min(i,j),max(i,j)));
        }else if(j!=par){
            low[i] = min(low[i],ord[j]);
        }
    }

    return;
}

int main(){
    cin >> v >> e;
    rep(i,e){
        int s,t;
        cin >> s >> t;
        graph[s].push_back(t);
        graph[t].push_back(s);
    }
    dfs(0);
    sort(bridges.begin(),bridges.end());
    for(P p:bridges){
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}