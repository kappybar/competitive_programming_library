#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
using namespace std;
using ll = long long ;
using P = pair<int,int> ;
using pll = pair<long long,long long>;
constexpr int INF = 1e9;
constexpr long long LINF = 1e17;
constexpr int MOD = 1000000007;

int v = 100005;
int e;
vector<vector<pll>> graph(v,vector<pll>());

vector<ll>  Dijkstra(int start){
    vector<bool> seen(v,false);
    vector<ll> shortest(v,LINF);
    priority_queue<pll,vector<pll>,greater<pll>> pq;
    pq.push(pll(0,start));

    while(!pq.empty()){
        ll dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        if(seen[node]) continue;

        shortest[node] = dist;
        seen[node] = true;

        for(pll next:graph[node]){
            int next_node = next.second;
            ll next_cost = next.first;
            if(seen[next_node]) continue;
            pq.push(pll(next_cost + dist,next_node));
        }
    }

    return shortest;
}

int main(){
    int start;
    cin >>  v >> e >> start;
    rep(i,e){
        int s,t,d;
        cin >> s >> t >> d;
        graph[s].push_back(pll(d,t));
    }

    vector<ll> ans = Dijkstra(start);

    rep(i,v){
        if(ans[i]==LINF) cout << "INF" << endl;
        else cout << ans[i] << endl;
    }

    return 0;
}