#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define chmin(x,y) x = min((x),(y))
#define chmax(x,y) x = max((x),(y))
#define popcount(x) __builtin_popcount(x)
using namespace std;
using ll = long long ;
using P = pair<int,int> ;
using pll = pair<long long,long long>;
const int INF = 1e9;
const long long LINF = 1e17;
const int MOD = 1000000007;
//const int MOD = 998244353;
const double PI = 3.14159265358979323846;

const int N = 65;
long long C[N][N];

void init(){
    for(int i=0;i<N;i++){
        for(int j=0;j<=i;j++){
            if(j==0) C[i][j] = 1;
            else if(i==j) C[i][j] = 1;
            else{
                C[i][j] = C[i-1][j] + C[i-1][j-1];
            }
        }
    }
    return;
}

int main(){
    int a,b;
    cin >> a >> b;
    ll k;
    cin >> k;
    init();

    string ans = "";
    int aa = a,bb = b;

    rep(i,a+b){
        ll p = C[aa+bb-1][bb];

        if(p < k){
            ans += "b";
            k -= p;
            bb--;
        }else{
            ans += "a";
            aa--;
        }
    }

    cout << ans << endl;

    return 0;
}