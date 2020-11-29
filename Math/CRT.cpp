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

inline long long mod(long long x,long long m){
    x %= m;
    if(x < 0) x += m;
    return x;
}

long long gcd(long long i,long long j){
    if(j == 0) return i;
    return gcd(j,i%j);
}

//a*x + b*y =gcd(a,b)を満たすx、yをもとめる
pair<long long,long long> extgcd(long long a,long long b){
    if(b == 0) return {1,0};
    pair<long long,long long> res = extgcd(b,a%b);
    long long x = res.first;
    long long y = res.second;
    return {y,x - (a/b) * y};
}

pair<long long,long long> CRT(long long b1,long long m1,long long b2,long long m2){
    pair<long long,long long> pq = extgcd(m1,m2);
    long long p = pq.first;
    long long q = pq.second;
    long long d = gcd(m1,m2);
    if((b2 - b1) % d != 0) return make_pair(0,-1);
    long long m =  m1 * (m2 / d);          //lcm(m1,m2)
    long long tmp = ((b2 - b1) / d * p) % (m2/d);
    long long r = mod(b1 + m1 * tmp, m);
    return make_pair(r,m);
}

int main(){
    ll X,Y;
    cin >> X >> Y;
    rep(i,2){
        ll x,y;
        cin >> x >> y;
        pll ans = CRT(X,Y,x,y);
        if(ans.second == -1){
            cout << -1 << endl;
            return 0;
        }
        X = ans.first;
        Y = ans.second;
        //cout <<  X  << " " << Y << endl;
    }
    if(X ==0){
        cout << Y << endl;
    }else{
        cout << X << endl;
    }
    return 0;
}

/*
x % m1 == b1 && x % m2 == b2 
<=>  x % lcm(m1,m2)( == m) == r
を満たすを求める。
rはつまり上の二式をみたす最小の数
中国剰余定理　Chinese Remaninder Theorem
*/
