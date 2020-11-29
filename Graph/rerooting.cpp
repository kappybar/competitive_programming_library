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

int n;
vector<int> tree[200005];
combination com(200005);

struct DP{
    mint dp;
    int t;
    DP(mint dp=1,int t=0):dp(dp),t(t){}
    DP operator+(const DP& a) const {
        return DP(dp*a.dp*com.c(t+a.t,t),t+a.t);
    }
    DP addroot() const {
        return DP(dp,t+1);
    }
};

vector<DP> dp[200005];
DP ans[200005];

DP dfs1(int i,int before=-1){
    DP dpi;
    dp[i] = vector<DP>(tree[i].size());
    rep(j,tree[i].size()){
        if(tree[i][j] == before) continue;
        dp[i][j] = dfs1(tree[i][j],i);
        dpi = dpi + dp[i][j];
    }
    return dpi.addroot();
}

void dfs2(int i,int before=-1,DP dpp=DP()){
    int deg = tree[i].size();
    rep(j,deg) if(tree[i][j] == before) dp[i][j] = dpp;

    vector<DP> dpleft(deg+1),dpright(deg+1);
    rep(j,deg) dpleft[j+1] = dpleft[j] + dp[i][j];
    for(int j=deg-1;j>=0;j--) dpright[j] = dpright[j+1] + dp[i][j];

    ans[i] = dpleft[deg].addroot();

    rep(j,deg){
        if(tree[i][j] == before) continue;
        DP d = dpleft[j] + dpright[j+1];
        dfs2(tree[i][j],i,d.addroot());
    }
}


int main(){
    cin >> n;
    rep(i,n-1){
        int a,b;
        cin >> a >> b;
        --a;--b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    dfs1(0);
    dfs2(0);
    rep(i,n) cout << ans[i].dp << endl;
}