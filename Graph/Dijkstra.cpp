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


//add_edge(a,b,d)でa->bにdの長さの辺を張る
//Dijkstra(s)でsからの最短経路を求める。
template<typename T>
struct Dijkstra_graph{
    using pp = pair<T,int>;
    int n;
    vector<vector<pp>> Graph;
    Dijkstra_graph(int n):n(n){
        Graph.resize(n);
    }
    void add_edge(int a,int b,T weight){
        Graph[a].push_back(pp{weight,b});
    }
    vector<T> Dijkstra(int start){
        vector<T> dist(n,LINF);
        priority_queue<pp,vector<pp>,greater<pp>> pq;
        pq.push(pp{0,start});
        dist[start] = 0;
        while(!pq.empty()){
            int v = pq.top().second;
            T d = pq.top().first;
            pq.pop();
            if(dist[v]<d) continue;
            for(pp nxt:Graph[v]){
                if(dist[nxt.second]<=dist[v]+nxt.first) continue;
                dist[nxt.second] = dist[v] + nxt.first;
                pq.push(pp{dist[nxt.second],nxt.second});
            }
        }
        return dist;
    }
};

int main(){
    int v,e,r;
    cin >> v >> e >> r;
    Dijkstra_graph<ll> G(v);
    rep(i,e){
        int s,t;
        ll d;
        cin >> s >> t >> d;
        G.add_edge(s,t,d);
    }
    vector<ll> d = G.Dijkstra(r);
    rep(i,v){
        if(d[i] >= LINF) cout << "INF" << endl;
        else cout << d[i] << endl;
    }
    return 0;
}