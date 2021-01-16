#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int INF = 1e9;
const int MOD = 1000000007;

const int MAX = 1000000;
long long fac[MAX], finv[MAX], inv[MAX];


void COMinit() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++){
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}

// 二項係数
long long COM(int n, int k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

//順列を計算
long long PER(int n,int k){
        if(n < k) return 0;
        if(n < 0 || k < 0) return 0;
        return (fac[n] * finv[n-k]) % MOD;
}

//nが10**9でもkが小さかったら計算できるコンビネーション
long long COM_small_k(ll n,ll k){
        if(n < k) return 0;
        if(n < 0 || k < 0) return 0;
        k = min(k,n-k);
        ll res = 1;
        for(int i=1;i <= k;i++){
                res = (res * (n-i+1))%MOD;
        }
        
        res = (res * finv[k]) %MOD;
        return res;
}

//nが10**9でもrが小さかったら計算できる順列
long long PER_small_k(ll n,ll k){
    if(n < k) return 0;
    if(n < 0 || k < 0) return 0;
    ll res = 1;
    for(ll i=n;i>=n-k+1;i--){
        res = (res * i) % MOD;
    }
    return res;
}

/*繰り返し二乗法*/
long long modpow(long long x, long long n) {
    long long ret = 1;
    while (n > 0) {
        if (n & 1) ret = (ret * x) % MOD;  
        x = (x * x) % MOD;
        n >>= 1;  
    }
    return ret;
}


/*繰り返し二乗法でxのmod逆元を取る*/
long long inverse(long long x){
    return modpow(x,MOD-2);
}

//eulerの関数
// gcd(a,n) == 1で　a^k == 1 (mod n)になるk
long long phi(long long n){
    long long res = n;
    for(long long i=2;i*i<=n;i++){
        if(n%i==0){
            res /= i;
            res *= i-1;
            while(n%i==0) n/=i;
        }
    }
    if(n > 1){
        res /= n;
        res *= n-1;
    }
    return res;
}

//n ^ kをO(k)で計算する。
long long  power(int n,int k){
    long long res = 1;
    for(int i=0;i<k;i++) res = (res * n)%MOD;
    return res;
}


int main(){
    COMinit();
    int n,a,b;
    cin >> n >> a >> b;
    ll res = (modpow(2,n) - 1 + MOD) % MOD;
    res = (res - COM_small_k(n,a) + MOD) % MOD;
    res = (res - COM_small_k(n,b) + MOD) % MOD;
    cout << res << endl;
    return 0;
}