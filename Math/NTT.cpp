#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
using namespace std;
using ll = long long ;
using P = pair<int,int> ;
using pll = pair<long long,long long>;
constexpr int INF = 1e9;
constexpr long long LINF = 1e17;
constexpr int MOD = 998244353;
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

class NumberTheoreticalTransform{
    private:
    static void fft(vector<mint>& F){
        int fdeg = F.size();
        if(fdeg == 1) return;
        vector<mint> even,odd;
        for(int i = 0;i < fdeg/2;i++){
            even.push_back(F[i<<1]);
            odd.push_back(F[(i<<1)|1]);
        }
        fft(even);fft(odd);
        mint x = 1,zeta = mint(3).pow((MOD-1)/fdeg); // 3 is primitive root of MOD(998244353)
        for(int i=0;i<fdeg;i++){
            F[i] = even[i % (fdeg/2)] + x * odd[i % (fdeg/2)];
            x *= zeta;
        }
    }

    static void ifft(vector<mint>& F){
        int fdeg = F.size();
        if(fdeg == 1) return;
        vector<mint> even,odd;
        for(int i = 0;i < fdeg/2;i++){
            even.push_back(F[i<<1]);
            odd.push_back(F[i<<1|1]);
        }
        ifft(even),ifft(odd);
        mint x = 1,zeta = mint(3).pow((MOD-1)/fdeg).inv();
        for(int i=0;i<fdeg;i++){
            F[i] = even[i % (fdeg/2)] + x * odd[i % (fdeg/2)];
            x *= zeta;
        }
    }

    public:
    static vector<mint> multiply(vector<mint> F,vector<mint> G){
        int degree = 1;
        while(degree < (int)F.size() + (int)G.size() - 1) degree <<= 1;
        vector<mint> nF(degree,0),nG(degree,0);
        for(int i=0;i<(int)F.size();i++){
            nF[i] = F[i];
        }
        for(int i=0;i<(int)G.size();i++){
            nG[i] = G[i];
        }
        fft(nF),fft(nG);
        for(int i=0;i<degree;i++){
            nF[i] *= nG[i];
        }
        ifft(nF);
        vector<mint> ans((int)(F.size() + G.size() - 1),0);
        mint inv_degree = mint(degree).inv();
        for(int i = 0;i < (int)F.size() + (int)G.size() - 1;i++){
            ans[i] = (nF[i] * inv_degree).x;
        }
        return ans;
    }
};


int main(){
    int n,m;
    cin >> n >> m;
    vector<mint> a(n),b(m);
    rep(i,n) cin >> a[i];
    rep(i,m) cin >> b[i];
    vector<mint> C = NumberTheoreticalTransform::multiply(a,b);
    for(int i=0;i<n+m-1;i++){
        cout << C[i] << " ";
    }
    cout << endl;
    return 0;
}

