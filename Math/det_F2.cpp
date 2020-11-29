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


// F_2 上で行列式を求める

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
using mint = ModInt<2>;

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

mint det(vector<vector<mint>> mat){
    int n = (int)mat.size();
    mint ans = 1;
    for(int i=0;i<n;i++){
        if(mat[i][i].x == 0){
            bool change = false;
            for(int j=i+1;j<n;j++){
                if(mat[j][i].x != 0){
                    swap(mat[i],mat[j]);
                    ans *= -1;
                    change = true;
                    break;
                }
            }
            if(!change) return 0;
        }
        for(int j=i+1;j<n;j++){
            mint r = mat[j][i] / mat[i][i];
            for(int k=i;k<n;k++){
                mat[j][k] -= mat[i][k] * r;
            }
        }
        ans *= mat[i][i];
    }
    return ans;
}

int main(){
    int n;
    cin >> n;
    vector<vector<mint>> mat(n,vector<mint>(n,0));

    rep(i,n){
        string s;
        cin >> s;
        rep(j,n) mat[i][j] = s[j] - '0';
    }

    mint res = det(mat);

    if(res.x == 0) cout << "Even" << endl;
    else cout << "Odd" << endl;

    return 0;
}