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

vector<int> ToplogicalSort(vector<vector<int>> &G,vector<int> &Indegree){
    int n = (int)G.size();
    vector<int> res(n);
    queue<int> q;
    for(int i=0;i<n;i++){
        if(Indegree[i] == 0){
            q.push(i);
        }
    }
    int i = 0;
    while(!q.empty()){
        int now = q.front();
        res[i++] = now;
        q.pop();
        for(int v:G[now]){
            --Indegree[v];
            if(Indegree[v] == 0) q.push(v);
        }
    }
    if(i==n) return res;
    else return {-1};
}

int main(){
    int v,e;
    cin >> v >> e;
    vector<vector<int>> G(v);
    vector<int> in(v,0);
    rep(i,e){
        int s,t;
        cin >> s >> t;
        G[s].push_back(t);
        ++in[t];
    }
    vector<int> res = ToplogicalSort(G,in);
    rep(i,v) cout << res[i] << endl;
    return 0;
}