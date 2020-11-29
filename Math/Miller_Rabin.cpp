#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
using ll =  long long ;
using P = pair<int,int> ;
using pll = pair<ll,ll>;
const ll INF = 1e18;
const int MOD = 1000000007;
using u128 = __uint128_t;

u128 modpow(u128 x, u128 n,u128 mod) {
    u128 ret = 1;
    while (n > 0) {
        if (n & 1) ret = (ret * x) % mod;  
        x = (x * x) % mod;
        n >>= 1;  
    }
    return ret;
}


bool Miller_Rabin(u128 x){
    if(x == 0) return false;
    if(x == 1) return false;
    if(x == 2) return true;
    if(x%2 == 0) return false;

    u128 d = x - 1;
    while(d%2 == 0) d /= 2;

    random_device rand;
    mt19937 mt(rand());
    uniform_int_distribution<u128> random_maker(1,x-1);
    
    for(int i = 0;i < 100; ++i){
        u128 p = random_maker(mt);
        u128 a = modpow(p,d,x);
        u128 s = d;

        while(s != x-1 && a != 1 && a != x-1){ 
            a = (a * a)%x;
            s <<= 1;
        }

        if(a != x-1 && s%2 == 0) return false;

    }
    return true;
}

int main(){
    int n;
    cin >> n;
    while(n--){
        ll x; cin >> x; cout << x << " " ;
        cout << (Miller_Rabin(x) ? 1 : 0) << endl; 
    }
    return 0;
}