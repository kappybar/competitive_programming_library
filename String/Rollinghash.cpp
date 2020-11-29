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

struct Rollinghash{
    string S;
    int n;
    vector<unsigned long long int> powb1;
    vector<unsigned long long int> powb2;
    vector<unsigned long long int> H1;
    vector<unsigned long long int> H2;
    const unsigned long long int B1 = 1000007;
    const unsigned long long int B2 = 1000009;
    const unsigned long long int M1 = 1000000007;
    const unsigned long long int M2 = 1000000009;

    Rollinghash(string S):S(S){
        n=(int)(S.size());
        H1.resize(n+1);
        H2.resize(n+1);
        powb1.resize(n+1);
        powb2.resize(n+1);
        init();
    }
    void init(){
        unsigned long long int p1 = 1;
        unsigned long long int p2 = 1;
        powb1[0] = p1;
        powb2[0] = p2;
        H1[0] = 0;
        H2[0] = 0;
        for(int i=1;i<=n;i++){
            powb1[i] = (powb1[i-1]*B1)%M1;
            powb2[i] = (powb2[i-1]*B2)%M2;
        }
        for(int i=1;i<=n;i++){
            H1[i] = (H1[i-1]*B1 + S[i-1])%M1;
            H2[i] = (H2[i-1]*B2 + S[i-1])%M2;
        }
    }
    //[l,r)
    pair<unsigned long long int,unsigned long long int> hash(const int& l,const int& r){ 
        return make_pair( (H1[r] - (H1[l] * powb1[r-l])%M1 + M1)%M1,(H2[r] - (H2[l] * powb2[r-l])%M2 + M2)%M2 );
    }
}; 

int main(){
    string T,P;
    cin >> T >> P;
    if((int)(T.size()) < (int)(P.size())){
        return 0;
    }

    Rollinghash Rt(T),Rp(P);
    int m = P.size();

    for(int i=0;i<T.size();i++){
        if(Rt.hash(i,i+m)==Rp.hash(0,m)){
            cout << i << endl;
        }
    }

    return 0;
}