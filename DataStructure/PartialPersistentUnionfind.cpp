#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define chmin(x,y) x = min((x),(y))
#define chmax(x,y) x = max((x),(y))
#define popcount(x) __builtin_popcount(x)
using namespace std;
using ll = long long ;
using P = pair<int,int> ;
using pll = pair<long long,long long>;
const int INF = 1e9;
const long long LINF = 1e17;
//const int MOD = 1000000007;
const int MOD = 998244353;
const double PI = 3.14159265358979323846;

struct PartialPersistentUnionfind{
    int n;
    int now;
    vector<int> par;
    vector<int> time;
    vector<vector<pair<int,int>>> sz;

    PartialPersistentUnionfind(int n)
        :n(n),
         now(0),
         par(n,-1),
         time(n,INF),
         sz(n,vector<pair<int,int>>(1,{0,1})) {}

    int find(int x,int t) {
        if (t < time[x]) return x;
        return find(par[x],t);
    }

    int unite(int x,int y) {
        ++now;
        x = find(x,now);
        y = find(y,now);
        if (x == y) return now;
        if (par[x] > par[y]) swap(x,y);
        par[x] += par[y];
        par[y] = x;
        time[y] = now;
        sz[x].emplace_back(now,-par[x]);
        return now;
    }

    int size(int x,int t) {
        int p = find(x,t);
        int left = 0,right = (int)sz[p].size();
        while (right - left > 1) {
            int mid = (left + right) / 2;
            if (sz[p][mid].first <= t) left = mid;
            else right = mid;
        }
        return sz[p][left].second;
    }

    bool same(int x,int y,int t) {
        return find(x,t) == find(y,t);
    }
};

int main() {
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int,ll>> edge(m);
    rep(i,m){
        int a,b;
        ll c;
        cin >> a >> b >> c;
        --a;--b;
        edge[i] = {i,a,b,c};
    }
    sort(edge.begin(),edge.end(),[](auto l,auto r){
        return get<3>(l) < get<3>(r);
    });
    PartialPersistentUnionfind uf(n);

    vector<int> t(n);
    vector<int> tid(n);
    vector<int> in(m,-1);
    vector<P> ab(m);
    vector<ll> weight(m);
    int ind = 0;
    ll ans = 0;
    rep(i,m){
        auto [id,a,b,c] = edge[i];
        weight[id] = c;
        ab[id] = {a,b};
        if(uf.same(a,b,uf.now)) continue;
        tid[ind] = id;
        t[ind++] = uf.unite(a,b);
        ans += c;
        in[id] = 1;
    }

    int q;
    cin >> q;
    while(q--){
        int k;
        cin >> k;
        vector<int> v(k);
        rep(i,k) cin >> v[i],--v[i];
        bool ok = true;
        for(int i:v){
            auto [a,b] = ab[i];
            int left = -1,right = n;
            while(right - left > 1){
                int mid = (left + right)/2;
                if(uf.same(a,b,t[mid])) right = mid;
                else left = mid;
            }
            if(weight[tid[right]] != weight[i]) ok = false;
        }
        cout << (ok?"YES":"NO") << endl;
    }


    return 0;
}