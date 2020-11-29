#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
using ll =  long long ;
using P = pair<int,int> ;
const ll INF = 1e12;
const int MOD = 1000000007;

int main(){
    int v,e;
    cin >> v >> e;
    vector<vector<ll>> dist(v,vector<ll>(v,INF));
    rep(i,v) dist[i][i] = 0;
    rep(i,e){
        int s,t,d;
        cin >> s >> t >> d;
        dist[s][t] = d;
    }

    //もし負の閉路がある場合はdist[i][k]tとdist[k][j]がINFがどうかわからない
    rep(k,v)rep(i,v)rep(j,v){
        if(dist[i][k] == INF || dist[k][j] == INF) continue;
        dist[i][j] = min(dist[i][j] , dist[i][k]+dist[k][j]);
    }

    rep(i,v){
        if(dist[i][i] < 0){
            cout << "NEGATIVE CYCLE" << endl;
            return 0;
        }
    }

    rep(i,v)rep(j,v){
        if(dist[i][j] >= INF) cout << "INF" ;
        else cout << dist[i][j] ;
        cout << (j==v-1 ? '\n' : ' ') ;
    }
    return 0;
}