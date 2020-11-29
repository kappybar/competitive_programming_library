#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
const int INF = 1e9;
const int MOD = 1000000007;
#define rep(i,n) for(int i=0;i<n;i++)


//1-indexedに注意！！！
struct BIT{
    private:
    int n,n_;
    vector<long long> bit;

    public:
    BIT(int n):n(n){
        bit.resize(n+1);
        n_ = 1;
        while(n_<=n) n_<<=1;
        n_ >>= 1;
    }
    //1-index
    long long sum(int i){
        long long res = 0;
        while(i > 0){
            res += bit[i];
            i -= i&-i;
        }
        return res;
    }
    //1-index
    void add(int i,long long val){
        while(i <= n){
            bit[i] += val;
            i += i&-i;
        }
    }
    //return 1-index
    int lowerbound(long long w){
        if(w <= 0) return 0;
        int x = 0;
        for(int k=n_;k>0;k>>=1){
            if(x+k<=n&&bit[x+k]<w){
                w -= bit[x+k];
                x += k;
            }
        }
        return x+1;
    }
};



int main(){
        int n;
        cin >> n;
        vector<int> a(n);
        rep(i,n) cin >> a.at(i);
        BIT bit(n);
        ll ans = 0;
        rep(i,n){
                ans += i-bit.sum(a.at(i));
                bit.add(a.at(i),1);
        }
        cout << ans << endl;
}
                        
                        
        