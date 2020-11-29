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

struct myComplex{
    double a = 0,b = 0;
    myComplex(double a,double b):a(a),b(b){}
    myComplex(double num){
        a = num;
    }
    inline myComplex& operator*=(const myComplex &r){
        double A = a * r.a - b * r.b;
        b = a * r.b + b * r.a;
        a = A;
        return *this;
    }
    inline myComplex& operator+=(const myComplex & r){
        a += r.a; 
        b += r.b;
        return *this;
    }
    inline myComplex operator*(const myComplex &r) const{
        myComplex res(*this);
        return res *= r;
    }
    inline myComplex operator+(const myComplex &r) const{
        myComplex res(*this);
        return res += r;
    }
};

class FastFourierTransform{
    private:
    static void fft(vector<myComplex>& F){
        int fdeg = F.size();
        if(fdeg == 1) return;
        vector<myComplex> even,odd;
        for(int i = 0;i < fdeg/2;i++){
            even.push_back(F[i<<1]);
            odd.push_back(F[(i<<1)|1]);
        }
        fft(even);fft(odd);
        myComplex x = 1,zeta = myComplex(cos(2*PI/fdeg),sin(2*PI/fdeg));
        for(int i=0;i<fdeg;i++){
            F[i] = even[i % (fdeg/2)] + x * odd[i % (fdeg/2)];
            x *= zeta;
        }
    }

    static void ifft(vector<myComplex>& F){
        int fdeg = F.size();
        if(fdeg == 1) return;
        vector<myComplex> even,odd;
        for(int i = 0;i < fdeg/2;i++){
            even.push_back(F[i<<1]);
            odd.push_back(F[i<<1|1]);
        }
        ifft(even),ifft(odd);
        myComplex x = 1,zeta = myComplex(cos(-2*PI/fdeg),sin(-2*PI/fdeg));
        for(int i=0;i<fdeg;i++){
            F[i] = even[i % (fdeg/2)] + x * odd[i % (fdeg/2)];
            x *= zeta;
        }
    }

    public:
    template<class T>
    static vector<long long> multiply(vector<T> F,vector<T> G){
        int degree = 1;
        while(degree < (int)F.size() + (int)G.size() - 1) degree <<= 1;
        vector<myComplex> nF(degree,0),nG(degree,0);
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
        vector<long long> ans((int)(F.size() + G.size() - 1),0);
        for(int i = 0;i < (int)F.size() + (int)G.size() - 1;i++){
            ans[i] = (long long)((nF[i].a / degree) + 0.5);
        }
        return ans;
    }
};


int main(){
    int n;
    cin >> n;
    vector<int> a(n+1),b(n+1);
    a[0] = b[0] = 0;
    rep(i,n) cin >> a[i+1] >> b[i+1];
    vector<ll> C = FastFourierTransform::multiply(a,b);
    for(int i=1;i<=2*n;i++){
        cout << C[i] << endl;
    }
    return 0;
}


/*
多項式の乗算がn*log(n)で行うことができる。分割統治
*/