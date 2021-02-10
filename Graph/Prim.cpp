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

template<typename T>
struct Prim_graph{
    using pp = pair<T,int>;
    int n;
    vector<vector<pp>> G;
    Prim_graph(int n):n(n){
        G.resize(n);
    }
    //無向
    void add_edge(int a,int b,T w){
        G[a].push_back(pp{w,b});
        G[b].push_back(pp{w,a});
    }
    T prim(int s = 0){
        vector<int> has_connected(n,-1);
        T res = 0;
        priority_queue<pp,vector<pp>,greater<pp>> pq;
        pq.push(P(0,s));
        while(!pq.empty()){
            T d = pq.top().first;
            int v = pq.top().second;
            pq.pop();
            if(has_connected[v] != -1) continue;
            has_connected[v] = 1;
            res += d;
            for(auto next:G[v]){
                if(has_connected[next.second] != -1) continue;
                pq.push(next);
            }
        }
        return res;
    }
};

int main(){
    int n,m;
    cin >> n >> m;
    Prim_graph<ll> G(n);
    rep(i,m){
        int a,b,r;
        cin >> a >> b >> r;
        G.add_edge(a,b,r);
    }
    int cost = G.prim();
    cout << cost << endl;
    return 0;
}