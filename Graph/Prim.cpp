#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
using ll =  long long ;
using P = pair<int,int> ;
const int INF = 1e9;
const int MOD = 1000000007;
int v = 10005,e = 100005;
vector<vector<P>> graph(v,vector<P>());
vector<bool> has_connected(v,false);

int prim(){
    int res = 0;
    priority_queue<P,vector<P>,greater<P>> pq;
    pq.push(P(0,0));
    while(!pq.empty()){
        P now = pq.top();
        pq.pop();
        int c,k;
        tie(c,k) = now;
        if(has_connected[k]) continue;
        res += c;
        has_connected[k] = true;
        for(P next:graph[k]){
            if(has_connected[next.second]) continue;
            pq.push(next);
        }
    }
    return res;
}

int main(){
    cin >> v >> e;
    rep(i,e){
        int s,t,w;
        cin >> s >> t >> w;
        graph[s].push_back(P(w,t));
        graph[t].push_back(P(w,s));
    }

    int cost = prim();
    cout << cost << endl;
    return 0;
}