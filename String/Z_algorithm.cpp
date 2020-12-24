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

// Z_algorithm
// s[0:]とs[i:(n-1)]の接頭辞の共通部分の長さ
template<typename T>
vector<int> Zalgo(const T& s){//数列or文字列
    int n = (int)s.size();
    vector<int> Z(n);
    Z[0] = n;
    int i = 1,j = 0;
    while(i < n){
        while(i+j<n && s[j] == s[i+j]) ++j;
        Z[i] = j;
        if(j == 0){
            i++;
            continue;
        }
        int k = 1;
        while(i+k < n && k + Z[k] < j){
            Z[i+k] = Z[k];
            k++;
        }
        i += k;
        j -= k;
    }
    return Z;
};

int main(){
    int n;
    cin >> n;
    vector<int> a(2*n),b(n);
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> b[i];
    rep(i,n) a[i+n] = a[i];
    vector<int> ba;
    for(int i=0;i<n-1;i++){
        ba.push_back(b[i]^b[i+1]);
    }
    for(int i=0;i<2*n-1;i++){
        ba.push_back(a[i]^a[i+1]);
    }
    vector<int> ans = Zalgo(ba);
    for(int i=n-1;i<2*n-1;i++){
        if(ans[i]>=n-1) cout << i-(n-1) << " " << (a[i-(n-1)]^b[0]) << endl;
    }
    cout << endl;
}