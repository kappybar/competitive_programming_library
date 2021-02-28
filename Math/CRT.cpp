#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define chmin(x,y) x = min((x),(y));
#define chmax(x,y) x = max((x),(y));
using namespace std;
using ll = long long ;
using P = pair<int,int> ;
using pll = pair<long long,long long>;
const int INF = 1e9;
const long long LINF = 9e18;
const int MOD = 1000000007;
//const int MOD = 998244353;
const double PI = 3.14159265358979323846;

long long gcd(long long i,long long j){
    if(j == 0) return i;
    return gcd(j,i%j);
}

long long lcm(long long i,long long j){
    return i / gcd(i,j) * j;
}

long long extgcd(long long a,long long b,long long &x,long long &y){
    if(b == 0){// gcd(a,b) * 1 + 0 * 0 = gcd(a,b);
        x = 1;
        y = 0;
        return a;
    }
    long long x2,y2;
    long long g = extgcd(b,a%b,x2,y2);
    x = y2;
    y = x2 - (a/b) * y2;
    return g;
}

pair<long long,long long> crt(const vector<long long> &r,const vector<long long> &m){
    assert(r.size() == m.size());
    int n = (int)r.size();

    long long r0 = 0,m0 = 1;// x = 0 (mod 1)
    for(int i=0;i<n;i++){
        assert(1 <= m[i]);
        long long r1 = r[i];
        long long m1 = m[i];

        r1 %= m1;
        if(r1 < 0) r1 += m1;

        if(m0 < m1){
            swap(r0,r1);
            swap(m0,m1);
        }

        if(m0 % m1 == 0){
            if(r0 % m1 != r1) return {0,0};//解なし
            continue;
        }

        long long g,im,tmp;
        g = extgcd(m0,m1,im,tmp);
        if((r1 - r0) % g != 0)  return {0,0};//解なし

        long long u1 = m1 / g;
        long long x = ((((r1 - r0) / g) % u1) * im) % u1;

        r0 += x * m0;
        m0 *= u1;
        if(r0 < 0) r0 += m0;
    }
    return {r0,m0};
}

void solve(){
    ll n,s,k;
    cin >> n >> s >> k;
    ll g = gcd(k,n);
    if(s % g != 0) cout << -1 << endl;
    else{
        k /= g;
        s /= g;
        n /= g;
        ll x,y;
        extgcd(k,n,x,y);
        ll ans = -s * x;
        ans %= n;
        if(ans < 0) ans += n;
        cout << ans << endl;
    }
}

int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}