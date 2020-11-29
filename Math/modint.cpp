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

struct combination{
    int N;
    vector<mint> fac,finv,inverse;
    combination(int N):N(N){
        fac.resize(N+1);finv.resize(N+1);
        fac[0]=1;
        for(int i=1;i<=N;++i){fac[i]=fac[i-1]*i;}
        finv[N]=fac[N].inv();
        for(int i=N-1;i>=0;--i){finv[i]=finv[i+1]*(i+1);}
    }
    void inverse_build(){
        inverse.resize(N+1);
        inverse[1]=1;
        for(int i=2;i<=N;++i){inverse[i]=finv[i]*fac[i-1];}
    }
    mint c(int n,int k){
        if(n<k||n<0||k<0) return 0;
        return fac[n]*finv[n-k]*finv[k];
    }
    mint p(int n,int k){
        if(n<k||n<0||k<0) return 0;
        return fac[n]*finv[n-k];
    }
};

int main(){
    combination com(1000000);
    int x,y;
    cin >> x >> y;
    mint ans = 0;
    if(2*y-x<0||2*x-y<0);
    else if((2*y-x)%3 != 0 || (2*x-y)%3 != 0);
    else{
        int s = (2*x-y)/3;
        int t = (2*y-x)/3;
        ans = com.c(s+t,s);
    }
    cout << ans << endl;
    return 0;
}
