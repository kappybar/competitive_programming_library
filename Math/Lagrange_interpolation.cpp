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

template<int mod> struct ModInt{
    long long x=0; 
    constexpr ModInt(long long x=0):x((x%mod+mod)%mod){}
    constexpr ModInt operator+(const ModInt& r)const{return ModInt(*this)+=r;}
    constexpr ModInt operator-(const ModInt& r)const{return ModInt(*this)-=r;}
    constexpr ModInt operator*(const ModInt& r)const{return ModInt(*this)*=r;}
    constexpr ModInt operator/(const ModInt& r)const{return ModInt(*this)/=r;}
    constexpr ModInt& operator+=(const ModInt& r){ if((x+=r.x)>=mod) x-=mod; return *this;}
    constexpr ModInt& operator-=(const ModInt& r){ if((x-=r.x)<0) x+=mod; return *this;}
    constexpr ModInt& operator*=(const ModInt& r){ if((x*=r.x)>=mod) x%=mod; return *this;}
    constexpr ModInt& operator/=(const ModInt& r){ return *this*=r.inv();}
    ModInt inv() const {
        long long s=x,sx=1,sy=0,t=mod,tx=0,ty=1;
        while(s%t!=0){
            long long temp=s/t,u=s-t*temp,ux=sx-temp*tx,uy=sy-temp*ty;
            s=t;sx=tx;sy=ty;
            t=u;tx=ux;ty=uy;
        }
        return ModInt(tx);
    }
    ModInt pow(long long n) const {
        ModInt a=1;
        ModInt b=*this;
        while(n>0){
            if(n&1) a*=b;
            b*=b;
            n>>=1;
        }
        return a;
    }
    friend constexpr ostream& operator<<(ostream& os,const ModInt<mod>& a) {return os << a.x;}
    friend constexpr istream& operator>>(istream& is,ModInt<mod>& a) {return is >> a.x;}
};
using mint = ModInt<MOD>;

//ラグランジュ補間
//f(x[i]) = y[i]のときに
//fの係数を返す
//O(n^2)
template<typename T>
vector<T> Lagrange_interpolation(vector<T> x,vector<T> y){
    int n = (int)x.size();
    vector<T> c(n,1);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) continue;
            c[i] *= (x[i]-x[j]);
        }
        c[i] = y[i] / c[i];
    }
    vector<T> dp(n+1,0);
    dp[0] = 1;
    for(int i=0;i<n;i++){
        vector<T> dp_new(n+1,0);
        for(int j=0;j<n;j++){
            if(j+1<n+1) dp_new[j+1] += dp[j];
            dp_new[j] -= x[i] * dp[j];
        }
        swap(dp,dp_new);
    }
    vector<T> res(n,0);
    for(int i=0;i<n;i++){
        T now = 0;
        for(int j=n;j>0;j--){
            now += dp[j];
            res[j-1] += c[i]*now;
            now *= x[i];
        }
    }
    return res;
}

//ラグランジュ補間
// f(x[i]) = y[i]のとき
// f(k)を求める。
// O(n^2)
template<typename T>
T Lagrange(vector<T> x,vector<T> y,T k){
    int n = (int)x.size();
    vector<T> c(n,1);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) continue;
            c[i] *= (x[i]-x[j]);
        }
        c[i] = y[i] / c[i];
    }
    vector<T> L(n+1),R(n+1);
    L[0] = R[n] = 1;
    for(int i=0;i<n;i++) L[i+1] = L[i] * (k-x[i]);
    for(int i=n-1;i>=0;i--) R[i] = R[i+1] * (k-x[i]);
    T res = 0;
    for(int i=0;i<n;i++) res += c[i] * L[i] * R[i+1];
    return res;
}

//ラグランジュ補間
// f(x) = y[0], f(x+d) = y[1],f(x+2*d)= y[2],...f(x+(n-1)*d) = y[n-1]のとき
// f(k)を求める。
// O(n)
template<typename T>
T Lagrange(T x,T d,vector<T> y,T k){
    int n = (int)y.size();
    T now = 1;
    vector<T> c(n,1);
    for(int i=1;i<n;i++){
        T a = d;
        a *= -i;
        now *= a;
    }
    for(int i=0;i<n;i++){
        c[i] = y[i] / now;
        if(i==n-1) continue;
        now /= d*(i-n+1);
        now *= d*(i+1);
    }
    vector<T> L(n+1),R(n+1);
    L[0] = R[n] = 1;
    for(int i=0;i<n;i++) L[i+1] = L[i] * (k-(x+d*i));
    for(int i=n-1;i>=0;i--) R[i] = R[i+1] * (k-(x+d*i));
    T res = 0;
    for(int i=0;i<n;i++) res += c[i] * L[i] * R[i+1];
    return res;
}

int main(){
    int n;
    cin >> n;
    vector<mint> a(n+1);
    rep(i,n+1) cin >> a[i];
    int t;
    cin >> t;
    mint tt = t;
    cout << Lagrange(mint(0),mint(1),a,tt) << endl;
    return 0;
}