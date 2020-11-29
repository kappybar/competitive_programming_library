#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
typedef long long ll;

vector<ll> getPrimes(ll x){
        vector<ll> res;
        for(ll i = 2; i * i <= x;i++){
                if(x%i ==0){
                        res.push_back(i);
                        while(x%i ==0) x /= i;
                }
        }
        if( x > 1) res.push_back(x);
        return res;
}
//10**9くらいの数の素因数の約数を求める。
//iはlong long じゃないといけない


vector<pair<long long,int>> getPrimes_(ll x){
        vector<pair<long long,int>> res;
        for(ll i = 2; i * i <= x;i++){
                if(x%i ==0){
                        res.push_back(make_pair(i,0));
                        while(x%i ==0) x /= i,res.back().second++;
                }
        }
        if( x > 1) res.push_back(make_pair(x,1));
        return res;
}
//こっちはpair型の{素因数、数}の組を返す

vector<ll> diviser_all(ll x){
        vector<ll> res;
        for(ll i = 1;i*i <=x;i++){
                if(x%i == 0){
                        res.push_back(i);
                        if(i*i==x);
                        else res.push_back(x/i);
                }
        }
        return res;
}
//約数のvectorを返す

int main(){
        int n;
        cin >> n;
        vector<ll> ans1;
        ans1 = getPrimes(n);
        for(ll i:ans1) cout << i << " ";
        cout << endl;

        vector<pair<long long,int>> ans2;
        ans2 = getPrimes_(n);
        for(auto p:ans2) cout << p.first << " " << p.second << endl;

        diviser_all(0,1,ans2);
        sort(prime.begin(),prime.end());
        for(ll p:prime) cout << p << endl;

        return 0;
}