#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int INF = 1e9;
const int MOD = 1000000007;


struct Sieve {
        int n;
        vector<int> f,primes;
        
        Sieve(int n=1):n(n),f(n+1){
            f[0] = f[1] = -1;
            for(long long i=2;i<=n;++i){
                if(f[i]) continue;
                primes.push_back(i);
                f[i] = i;
                for(long long j = i*i;j <= n;j += i) {
                    if(!f[j]) f[j] = i;
                }
            }
        }
        
        bool isPrime(int x){return f[x] == x;}
        
        vector<int> factorList(int x){
            vector<int> res;
            while(x != 1){
                res.push_back(f[x]);
                x /= f[x];
            }
            return res;
        }
        
        vector<pair<int,int>> factor(int x){
            vector<int> fl = factorList(x);
            if(fl.size() == 0) return {};
            vector<pair<int,int>> res(1,pair<int,int>(fl[0],0));
            for(int p:fl){
                if(res.back().first == p){
                    res.back().second ++;
                }else{
                    res.emplace_back(p,1);
                }
            }
            return res;
        }

        long long divisorCalc(long long x){
            long long res = 1;
            long long now = -1;
            long long nowCnt = 0;
            while(x != 1){
                if(now==f[x]) ++ nowCnt;
                else{
                    res *= nowCnt + 1;
                    now = f[x];
                    nowCnt = 1;
                }
                x /= f[x];
            }
            res *= nowCnt+1;
            return res;
        }
        
};

/*エラトステネスの篩　ついでに高速素因数分解もできる。　fはi以下の最小の素数を表していて、primes は素数を列挙している
isPrime で素数判定　factorListで素因数分解した結果の素数の集合がわかる。　factorでは素因数分解した結果の数がランググレンす圧縮された形でreturn 
される ex) factorList(12) = {2,2,3} factor(12) = {(2,2),(3,1)}。
divisorCalcで約数の個数を求める*/

int main() {
        Sieve sieve(1000005);
        int n;
        cin >> n;
        vector<int> a(n);
        rep(i,n) cin >> a.at(i);
        map<int,int> mp;
        rep(i,n){
                 auto f = sieve.factor(a[i]);
                for(auto p:f){
                        mp[p.first] = max(mp[p.first],p.second);
                }
        }
        
}
/*このように使う*/
/*https://atcoder.jp/contests/abc152/submissions/9686995*/
                                
                        