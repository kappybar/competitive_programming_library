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


//有効グラフの接続行列 Bについて 
//方程式 Bx = c を解く。
template<typename T>
struct Incidence_matrix{
    struct edge{int id,to;};
    int n,m;
    vector<vector<edge>> G;
    vector<vector<edge>> revG;
    vector<T> res,cc;
    vector<int> seen;
    Incidence_matrix(int n):n(n),m(0){
        G.resize(n);
        revG.resize(n);
    }
    //有向
    void add_edge(int a,int b){
        G[a].push_back(edge{m,b});
        revG[b].push_back(edge{m,a});
        ++m;
    }
    pair<bool,vector<T>> Solve(const vector<T> &c){
        assert((int)c.size() == n);
        res.assign(m,T(0));
        seen.assign(n,-1);
        cc = c;
        for(int i=0;i<n;i++){
            if(seen[i] == 1) continue;
            T check = dfs(i);
            if(check != T(0)) return {false,{}}; //no solution
        }
        return {true,res};
    }
    T dfs(int i){
        seen[i] = 1;
        T r = cc[i];
        for(auto e:G[i]){
            if(seen[e.to] == 1) continue;
            T c_ = dfs(e.to);
            res[e.id] = c_;
            r += c_;
        }
        for(auto e:revG[i]){
            if(seen[e.to] == 1) continue;
            T c_ = dfs(e.to);
            res[e.id] = c_ * (-1);
            r += c_;
        }
        return r;
    }
};

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
    constexpr bool operator==(const ModInt& r){ return x == r.x;}
    constexpr bool operator!=(const ModInt& r){ return x != r.x;}
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

int main(){
    int n,m;
    cin >> n >> m;
    vector<int> a(m),b(m);
    Incidence_matrix<mint> G(n);
    vector<mint> c(n,0);
    rep(i,m){
        int aa,bb;
        cin >> aa >> bb;
        --aa;--bb;
        G.add_edge(aa,bb);
        c[aa] -= 1;
        a[i] = aa;
        b[i] = bb;
    }
    auto ans = G.Solve(c);
    if(!ans.first){
        cout << -1 << endl;
        return 0;
    }
    rep(i,m){
        if(ans.second[i] == 0) cout << a[i]+1 << " " << b[i]+1 << endl;
        else cout << b[i]+1 << " " << a[i]+1 << endl;
    }

    return 0;
}

