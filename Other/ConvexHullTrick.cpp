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


// ConvecHullTrick
// MonotoneX = true でqueryのxが単調増加してる
//
// add()    ax+bを加える。　     aは単調減少するように与える
// query(x) min{ ax+b }を求める。
template<typename T>
struct ConvexHullTrick{
    deque<pair<T,T>> lines;  //傾きが単調減少しているように並べる
    bool MonotoneX;          //クエリのxは単調増加ならtrue
    ConvexHullTrick(bool MonotoneX = false):MonotoneX(MonotoneX){}

    // l1.first > l2.first > l3.first
    // l2が不要なら true l2が必要なら false
    bool check(pair<T,T> l1,pair<T,T> l2,pair<T,T> l3){
        return (l2.first - l1.first)*(l3.second - l2.second) >= (l2.second - l1.second)*(l3.first - l2.first);
    }

    //後ろにax+bを追加
    //傾きが単調減少な順に与えられることを仮定
    void add(T a,T b){
        pair<T,T> line(a,b);
        while((int)lines.size() >= 2 && check(*(lines.end() - 2),lines.back(),line) ){
            lines.pop_back();
        }
        lines.push_back(line);
        return;
    }

    // f_i(x)
    T f(int i,T x){
        assert(0 <= i && i < (int)lines.size());
        return lines[i].first * x + lines[i].second;
    }

    // 最小になるもの
    T query(T x){
        if(MonotoneX){
            while((int)lines.size() >= 2){
                T a0 = f(0,x);
                T a1 = f(1,x);
                if(a0 < a1) break;
                lines.pop_front();
            }
            return f(0,x);
        }else{
            int left = -1,right = (int)lines.size() - 1;
            while(right - left > 1){
                int mid = (left + right)/2;
                if(f(mid,x) < f(mid+1,x)) right = mid;
                else left = mid;
            }
            return f(right,x);
        }
    }
};

int main(){
    ll n,c;
    cin >> n >> c;
    vector<ll> h(n);
    rep(i,n) cin >> h[i];
    vector<ll> dp(n,0);
    ConvexHullTrick<ll> cht(false);
    dp[0] = 0;
    cht.add(-2*h[0],h[0]*h[0] + dp[0]);
    for(int i=1;i<n;i++){
        dp[i] = cht.query(h[i]) + h[i]*h[i] + c;
        cht.add(-2*h[i],h[i]*h[i] + dp[i]);
    }
    cout << dp[n-1] << endl;
    return 0;
}