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

// Mo algorithm 
// change add function and del function

int main(){
    int n;
    scanf("%d",&n);
    int q;
    scanf("%d",&q);
    vector<int> c(n);
    rep(i,n) scanf("%d",&c[i]),--c[i];
    vector<int> l(q),r(q);
    rep(i,q){
        scanf("%d %d",&l[i],&r[i]);
        --l[i];
    }

    int sq = sqrt(n);
    vector<int> qi(q,0);
    for(int i=0;i<q;i++) qi[i] = i;
    sort(qi.begin(),qi.end(),[&](const int &i,const int &j){
        if(l[i] / sq != l[j] / sq) return l[i] < l[j];
        if((l[i] / sq)%2 == 1) return r[i] > r[j];
        return r[i] < r[j];
    });

    vector<int> cnt(n,0);
    int ans = 0;

    auto add = [&](int id){
        //if(id<0 ||id>=n) return;
        if(cnt[c[id]]==0) ++ans;
        ++cnt[c[id]];
    };

    auto del = [&](int id){
        //if(id<0 ||id>=n) return;
        if(cnt[c[id]]==1) --ans;
        --cnt[c[id]];
    };

    
    vector<int> queryans(q);
    int nl = 0,nr = 0;
    for(int i:qi){
        //cout << nl << " " << nr  << endl;
        while(nl > l[i]) --nl,add(nl);
        while(nr < r[i]) add(nr),++nr;
        while(nl < l[i]) del(nl),++nl;
        while(nr > r[i]) --nr,del(nr);

        queryans[i] = ans;
    }

    rep(i,q) printf("%d\n",queryans[i]);
    return 0;
}