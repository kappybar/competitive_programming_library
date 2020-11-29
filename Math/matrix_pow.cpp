#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
typedef long long ll;
const int MOD = 1000000007;
//コーナーケースに注意！！！！
using vec = vector<ll> ;
using mat =  vector<vec>;

mat mul(mat &A, mat &B,int mod) {
        mat C(A.size(),vec(B[0].size()));
        for(int i=0;i<A.size();i++){
                for(int k=0;k<B.size();k++){
                        for(int j=0;j<B[0].size();j++){
                                C[i][j] = (C[i][j] + A[i][k]*B[k][j]) % mod;
                        }
                }
        }
        return C;
}

mat pow(mat A,ll n,int mod){
        mat B(A.size(), vec(A.size()));
        for(int i=0;i<A.size();i++) B[i][i] = 1;
        while(n > 0){
                if(n & 1) B = mul(B,A,mod);
                A = mul(A,A,mod);
                n >>= 1;
        }
        return B;
}

int main(){
        int n,k;
        cin >> n >> k;
        mat A(n,vec(n));
        rep(i,n)rep(j,n) cin >> A[i][j];
        mat B = pow(A,k,MOD);
        rep(i,n){
                rep(j,n){
                        cout << B[i][j] << " ";
                }
                cout << endl;
        }
        return 0;
}


//mulは行列の掛け算をする関数　MODも同時にとっている。
//powで行列の累乗をしている。 二重配列をmatとしてtypedefしている。　詳しくは蟻本p１８１を参照
//https://atcoder.jp/contests/dp/submissions/10116900

        
