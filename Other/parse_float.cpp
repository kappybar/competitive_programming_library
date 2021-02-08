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

long long str_int(const string& s){
    long long t = 1;
    long long res = 0;
    for(int i=(int)s.size()-1;i>=0;i--){
        res += (s[i]-'0') * t;
        t *= 10;
    }
    return res;
}

long long str_float_int(const string& s,int pow10){
    long long t = 1;
    for(int i=0;i<pow10;i++) t *= 10;

    int ind = -1;
    for(int i=0;i<(int)s.size();i++){
        if(s[i] == '.') ind = i;
    }

    if(ind == -1) return str_int(s) * t;
    long long res = str_int(s.substr(0,ind)) * t;
    string under_point = s.substr(ind+1);
    while((int)under_point.size() < pow10) under_point += "0";
    res += str_int(under_point);
    return res;
}

int main(){
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<P> two_five(n);
    rep(i,n){
        string s;
        cin >> s;
        a[i] = str_float_int(s,9);
        int t = 0,f = 0;
        while(a[i]%2 == 0) t++,a[i] /= 2;
        while(a[i]%5 == 0) f++,a[i] /= 5;
        two_five[i] = P{t,f};
    }
    sort(two_five.begin(),two_five.end());
    vector<vector<int>> five_cum(n,vector<int>(20,0));
    rep(i,n) five_cum[i][two_five[i].second] ++;
    for(int i=n-2;i>=0;i--)for(int j=0;j<20;j++) five_cum[i][j] += five_cum[i+1][j];

    ll ans = 0;
    rep(i,n){
        int left = -1,right = n;
        while(right - left > 1){
            int mid = (left + right)/2;
            if(two_five[mid].first + two_five[i].first < 18) left = mid;
            else right = mid;
        }
        if(right == n) continue;
        for(int j=max(0,18-two_five[i].second);j<20;j++){
            ans += five_cum[right][j];
        }
        if(two_five[i].first + two_five[i].first >= 18 && two_five[i].second + two_five[i].second >= 18) --ans;
    }
    ans /= 2;
    cout << ans << endl;
    return 0;
}