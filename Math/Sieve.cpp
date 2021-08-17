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
const int MOD = 1000000007;
//const int MOD = 998244353;
const double PI = 3.14159265358979323846;

struct Sieve {
    int n;
    vector<int> f,primes,mobius;
    
    Sieve(int n=1):n(n),f(n+1),mobius(n+1,1){
        f[0] = f[1] = -1;
        mobius[1] = 1;
        primes.reserve(n);
        for(long long i=2;i<=n;++i){
            if(f[i]) continue;
            primes.push_back(i);
            f[i] = i;
            mobius[i] = -1;
            for(long long j = 2*i;j <= n;j += i) {
                if(!f[j]) f[j] = i;
                if((j/i)%i == 0) mobius[j] = 0;
                else mobius[j] = -mobius[j];
            }
        }
    }
    
    bool isPrime(int x){return f[x] == x;}
    
    //高速素因数分解
    vector<pair<int,int>> factor(int x){
        vector<pair<int,int>> res;
        while(x > 1){
            int p = f[x];
            int c = 0;
            while(f[x] == p){
                ++c;
                x /= f[x];
            }
            res.emplace_back(p,c);
        }
        return res;
    }

    //高速約数列挙
    vector<int> divisor(int x){
        vector<int> res(1,1);
        auto pf = factor(x);
        for(auto [p,c]:pf) {
            int sz = (int)res.size();
            for(int i=0;i<sz;i++){
                int v = 1;
                for(int j=0;j<c;j++){
                    v *= p;
                    res.push_back(res[i] * v);
                }
            }
        }
        return res;
    }

    //約数の個数
    long long divisor_count(int x){
        auto pf = factor(x);
        long long res = 1;
        for(auto [p,c]:pf) res *= c+1;
        return res;
    }
};

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    rep(i,n) cin >> a[i];
    Sieve sieve(1000005);

    vector<int> cnt(1000005,0);
    bool pairwise = true;
    rep(i,n){
        auto pf = sieve.factor(a[i]);
        for(auto [a,b]:pf){
            cnt[a] ++;
            if(cnt[a] > 1) pairwise = false;
        }
    }

    if(pairwise){
        cout << "pairwise coprime" << endl;
    }else{
        int g = 0;
        rep(i,n) g = gcd(g,a[i]);
        if(g==1) cout << "setwise coprime" << endl;
        else cout << "not coprime" << endl;
    }
    return 0;
}