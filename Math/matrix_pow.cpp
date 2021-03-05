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
        while(n>0){
            if(n&1) a*=*this;
            *this*=*this;
            n>>=1;
        }
        return a;
    }
    friend constexpr ostream& operator<<(ostream& os,const ModInt<mod>& a) {return os << a.x;}
    friend constexpr istream& operator>>(istream& is,ModInt<mod>& a) {return is >> a.x;}
};
using mint = ModInt<MOD>;
using vec = vector<mint> ;
using mat = vector<vec>;

mat mul(mat &A, mat &B) {
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<(int)A.size();i++){
        for(int k=0;k<(int)B.size();k++){
            for(int j=0;j<(int)B[0].size();j++){
                C[i][j] = C[i][j] + A[i][k]*B[k][j];
            }
        }
    }
    return C;
}

mat matpow(mat A,ll n){
    mat B(A.size(), vec(A.size()));
    for(int i=0;i<(int)A.size();i++) B[i][i] = 1;
    while(n > 0){
        if(n & 1) B = mul(B,A);
        A = mul(A,A);
        n >>= 1;
    }
    return B;
}


int main(){
    int k,m;
    cin >> k >> m;
    ll n;
    cin >> n;
    vector<int> p(m),q(m),r(m);
    rep(i,m) cin >> p[i] >> q[i] >> r[i];
    rep(i,m) --p[i],--q[i],--r[i];

    auto id = [&](int a,int b){return a+b*k;};
    int t = k*k;
    mat A(t,vector<mint>(t,0));
    rep(i,m){
        A[id(p[i],q[i])][id(q[i],r[i])] = 1;
    }

    A = matpow(A,n-2);

    mint ans = 0;
    rep(i,k)rep(j,k){
        ans += A[id(0,i)][id(j,0)];
    }
    cout << ans << endl;


    return 0;
}