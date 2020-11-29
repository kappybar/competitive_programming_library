#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
using namespace std;
using ll = long long ;
using P = pair<int,int> ;
using pll = pair<long long,long long>;
constexpr int INF = 1e9;
constexpr long long LINF = 1e10;
constexpr int MOD = 1000000007;
constexpr double PI = 3.14159265358979323846;

// Cap int ,Cost long long
template<typename Cap,typename Cost>
struct mcf_graph{
    struct edge{
        int to;
        Cap cap;
        Cost cost;
        int rev;
    };
    int n;
    vector<vector<edge>> G;
    vector<Cost> dist;
    vector<int> prev_edge;
    vector<int> prev_vertex;

    mcf_graph(int n):n(n),G(n),dist(n,-1),prev_edge(n),prev_vertex(n){}

    void add_edge(int from,int to,Cap cap,Cost cost){
        G[from].push_back(edge{to,cap,cost,(int)G[to].size()});
        G[to].push_back(edge{from,0,-cost,(int)G[from].size()-1});
    }

    // min cost  s -> t (f flow)
    pair<Cap,Cost> min_cost_max_flow(int s,int t,Cap f){
        Cost res = 0;
        Cap f_ = f;
        while(f > 0){
            fill(dist.begin(),dist.end(),LINF);
            dist[s] = 0;
            bool update = true;
            while(update){
                update = false;
                for(int i=0;i<n;i++){
                    if(dist[i]>=LINF) continue;
                    for(int j=0;j<(int)G[i].size();j++){
                        edge &e = G[i][j];
                        if(e.cap > 0 && dist[e.to] > dist[i] + e.cost){
                            dist[e.to] = dist[i] + e.cost;
                            prev_vertex[e.to] = i;
                            prev_edge[e.to] = j;
                            update = true;
                        }
                    }
                }
            }

            if(dist[t] == LINF){
                return pair<Cap,Cost>{f_-f,res};
            }

            Cap d = f;
            for(int v=t;v!=s;v=prev_vertex[v]){
                d = min(d,G[prev_vertex[v]][prev_edge[v]].cap);
            }
            f -= d;
            res += d*dist[t];
            for(int v=t;v!=s;v=prev_vertex[v]){
                edge &e = G[prev_vertex[v]][prev_edge[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return pair<Cap,Cost>{f_,res};
    }

};

ll a[60][60];

int main(){
    int n,k;
    cin >> n >> k;
    rep(i,n)rep(j,n) cin >> a[i][j];
    int s = 2*n,t = 2*n+1;

    mcf_graph<int,ll> G(2*n+2);

    G.add_edge(s,t,n*k,LINF);

    rep(i,n){
        G.add_edge(s,i,k,0);
        G.add_edge(i+n,t,k,0);
    }

    rep(i,n)rep(j,n){
        G.add_edge(i,j+n,1,LINF-a[i][j]);
    }

    pair<int,ll> ans = G.min_cost_max_flow(s,t,n*k);

    cout << (ll)ans.first * LINF - ans.second << endl;

    vector<vector<char>> maze(n,vector<char>(n,'.'));

    rep(i,n){
        for(int j=0;j<(int)G.G[i].size();j++){
            if(G.G[i][j].to==s || G.G[i][j].to == t || G.G[i][j].to < n) continue;
            if(G.G[i][j].cap == 0) maze[i][G.G[i][j].to-n] = 'X';
        }
    }

    rep(i,n){
        rep(j,n){
            cout << maze[i][j];
        }
        cout << endl;
    }

    return 0;
}