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


template<typename T>
struct Matrix{
    int n,m;
    vector<vector<T>> Mat;
    Matrix(int n,int m,T val = 0):n(n),m(m){
        Mat.assign(n,vector<T>(m,val));
    }
    Matrix(vector<vector<T>> Mat):Mat(Mat){
        n = (int)Mat.size();
        m = (int)(Mat[0].size());
    }
    inline const vector<T> &operator[](int i)const{ return Mat[i];}
    inline vector<T> &operator[](int i){ return Mat[i];}
};

template<typename T>
Matrix<T> mul(Matrix<T> &A, Matrix<T> &B) {
    assert(A.m == B.n);
    Matrix<T> C(A.n,B.m);
    for(int i=0;i<A.n;i++){
        for(int k=0;k<B.n;k++){
            for(int j=0;j<B.m;j++){
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

template<typename T>
Matrix<T> matpow(Matrix<T> &A,long long n){
    assert(A.n == A.m);
    Matrix<T> B(A.n,A.n);
    for(int i=0;i<A.n;i++) B[i][i] = 1;
    while(n > 0){
        if(n & 1) B = mul(B,A);
        A = mul(A,A);
        n >>= 1;
    }
    return B;
}

template<typename T>
struct Vector{
    int n;
    vector<T> Vec;
    Vector(int n,T val = 0):n(n){
        Vec.assign(n,val);
    }
    Vector(vector<T> Vec):Vec(Vec){
        int n = (int)Vec.size();
    }
    inline const T &operator[](int i)const{ return Vec[i];}
    inline T &operator[](int i){ return Vec[i];}
};

template<typename T>
Vector<T> mul(Matrix<T> &A,Vector<T> &x){
    assert(A.m == x.n);
    Vector<T> Ax(A.n);
    for(int i=0;i<A.n;i++){
        for(int j=0;j<x.n;j++){
            Ax[i] = Ax[i] + A[i][j] * x[j]; 
        }
    }
    return Ax;
}

int main(){
    ll n;
    cin >> n;
    mint six_inv = mint(1)/mint(6);
    Matrix<mint> mat(6,6);
    rep(i,5) mat[i][i+1] = 1;
    rep(i,6) mat[5][i] = six_inv;
    Vector<mint> vec(6);
    vec[0] = 1;
    for(int i=1;i<6;i++){
        for(int j=1;j<=6;j++){
            if(i-j<0) break;
            vec[i] += vec[i-j];
        }
        vec[i] *= six_inv;
    }
    mat = matpow(mat,n);
    vec = mul(mat,vec);
    cout << vec[0] << endl;
    return 0;
}