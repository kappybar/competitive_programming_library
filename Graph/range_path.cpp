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



struct range_path{
    using pli = pair<long long,int>;
    int n; 
    int N;
    int V;
    vector<vector<pli>> Graph;
    range_path(int n):n(n){
        N=1;
        while(N<n) N*=2;
        Graph.resize(3*N-2);
        V=3*N-2;
        for(int i=0;i<N-1;++i){
            Graph[i].emplace_back(0,2*i+1);
            Graph[i].emplace_back(0,2*i+2);
            Graph[2*i+N-1].emplace_back(0,i+2*N-1);
            Graph[2*i+N].emplace_back(0,i+2*N-1);
        }
    }
    void add_edge_from(int k,int l,int r,int p,int q,int v){
        if(r <= p || q <= l) return;
        if(l <= p && q <= r) Graph[3*N-3-k].emplace_back(0LL,v);
        else{
            add_edge_from(2*k+2,l,r,p,(p+q)/2,v);
            add_edge_from(2*k+1,l,r,(p+q)/2,q,v);
        }
    }
    void add_edge_to(int k,int L,int R,int p,int q,int v){
        if(R <= p || q <= L) return;
        if(L <= p && q <= R) Graph[v].emplace_back(0LL,k);
        else{
            add_edge_to(2*k+1,L,R,p,(p+q)/2,v);
            add_edge_to(2*k+2,L,R,(p+q)/2,q,v);
        }
    }
    //[l,r) -> [L,R)
    void add_edge(int l,int r,int L,int R,long long cost){
        if(l>=r||L>=R) return;
        Graph.emplace_back();
        Graph.emplace_back();
        V+=2;
        add_edge_from(0,l,r,0,N,V-2);
        add_edge_to(0,L,R,0,N,V-1);
        Graph[V-2].emplace_back(cost,V-1);
    }
    vector<long long> Dijkstra(int start){
        vector<long long> shortest(V,-1);
        priority_queue<pli,vector<pli>,greater<pli>> pq;
        pq.push(pli(0,start+N-1));
        while(!pq.empty()){
            long long d = pq.top().first;
            int v = pq.top().second;
            pq.pop();
            if(shortest[v]>=0) continue;
            shortest[v] = d;
            for(pli next:Graph[v]){
                if(shortest[next.second]>=0) continue;
                pq.push(pli(d+next.first,next.second));
            }
        }
        vector<long long> res(n);
        rep(i,n) res[i] = shortest[i+N-1];
        return res;
    }
};


int main(){
    int n,m;
    cin >> n >> m;
    range_path G(n);
    rep(i,m){
        int l,r,c;
        cin >> l >> r >> c;
        --l;--r;
        G.add_edge(l,r+1,l,r+1,c);
    }
    vector<ll> d = G.Dijkstra(0);
    cout << d[n-1] << endl;
    return 0;
}