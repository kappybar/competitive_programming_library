#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
using ll =  long long ;
using P = pair<int,int> ;
const ll INF = 1e12;
const int MOD = 1000000007;
const ll LINF = 1e18;

ll v = 1005,e;
vector<vector<pair<ll,ll>>> graph(v,vector<pair<ll,ll>>());
vector<ll> shortest(v,INF);

//ベルマンフォードもし負の閉路があったらfalseをかえす
bool bellmanford(ll start){
    shortest[start] = 0;
    int cnt = 0;
    while(1){
        bool update = false;
        for(int i=0;i<v;i++){
            if(shortest[i] == INF) continue;
            for(pair<ll,ll> edge:graph[i]){
                if(shortest[edge.second] > shortest[i] + edge.first){
                    shortest[edge.second] = shortest[i] + edge.first;
                    update = true;
                }
            }
        }
        if(!update) break;
        cnt ++;
        if(cnt > v) return false;
    }
    return true;
}

int main(){
    int start;
    cin >> v >> e >> start ;
    rep(i,e){
        int s,t,d;
        cin >> s >> t >> d;
        graph[s].push_back(make_pair(d,t));
    }

    if(!bellmanford(start)){
        cout << "NEGATIVE CYCLE" << endl;
        return 0;
    }

    rep(i,v){
        if(shortest[i] == INF) cout << "INF" << endl;
        else cout << shortest[i] << endl;
    }
}

//ベルマンフォードには注意が必要！！！！
/*score attack & coin respawn でも登場　閉路があっても 0->n への閉路だけが関係する場合がある。
この時に閉路の判定は異なる。loopを多めに回してv回以上の時に更新された頂点は閉路に関係する頂点なので　-LINFにする。
そうしてv回以上のときにshortest[v-1]が更新されたらvに繋がる閉路があるという事。
*/

ll v = 1005,e;
vector<vector<pair<ll,ll>>> graph(v,vector<pair<ll,ll>>());
vector<ll> shortest(v,LINF);

//ベルマンフォードもし負の閉路があったらfalseをかえす
bool bellmanford(ll start){
    shortest[start] = 0;
    int cnt = 0;
    while(1){
        bool update = false;
        bool goal = false;
        for(int i=0;i<v;i++){
            if(shortest[i] == LINF) continue;
            for(pair<ll,ll> edge:graph[i]){
                if(shortest[edge.second] > shortest[i] + edge.first){
                    if(cnt < v) shortest[edge.second] = shortest[i] + edge.first;
                    else shortest[edge.second] = -LINF;
                    update = true;
                    if(edge.second==v-1){
                        goal = true;
                    }
                }
            }
        }
        if(!update) break;
        cnt ++;
        if(cnt >= v && goal){
            return false;
        }
        if(cnt > 3*v){
            return true;
        }
    }
    return true;
}

int main(){
    cin >> v >> e;
    rep(i,e){
        int a,b;
        ll c;
        cin >> a >> b >> c;
        --a;--b;
        graph[a].push_back(pll{-c,b});
    }

    if(bellmanford(0)){
        cout << -shortest[v-1] << endl;
    }else{
        cout << "inf" << endl;
    }

    return 0;
}