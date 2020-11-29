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

//compress 1
template<typename T>
vector<T> compress(vector<T> &a){
    vector<T> val = a;
    int n = (int)a.size();
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    for(int i=0;i<n;i++){
        a[i] = lower_bound(val.begin(),val.end(),a[i]) - val.begin();
    }
    return val;
}

//compress 2
template<typename T>
vector<T> compress(vector<T> &p1,vector<T> &p2){
    vector<T> vals;
    int n = (int)p1.size();
    for(int i=0;i<n;i++){
        vals.push_back(p1[i]);
        vals.push_back(p1[i]+1);
        vals.push_back(p2[i]);
        vals.push_back(p2[i]+1);
    }
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    for(int i=0;i<n;i++){
        p1[i] = lower_bound(vals.begin(),vals.end(),p1[i]) - vals.begin();
        p2[i] = lower_bound(vals.begin(),vals.end(),p2[i]) - vals.begin();
    }
    return vals;
}

// p1 & p2 change into compress point 
// vals means original point before compressed
// so vals[p1[i]] & vals[p2[i]] means original points

int main(){
    int n;
    cin >> n;
    vector<ll> x1(n),x2(n),y1(n),y2(n);
    rep(i,n){
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    }
    vector<ll> x = compress(x1,x2);
    vector<ll> y = compress(y1,y2);
    int w = (int)x.size();
    int h = (int)y.size();
    vector<vector<int>> maze(h+1,vector<int>(w+1,0));
    rep(i,n){
        maze[y1[i]][x1[i]] ++;
        maze[y2[i]][x2[i]] ++;
        maze[y1[i]][x2[i]] --;
        maze[y2[i]][x1[i]] --;
    }
    rep(i,h+1){
        rep(j,w){
            maze[i][j+1]+=maze[i][j];
        }
    }
    rep(j,w+1){
        rep(i,h){
            maze[i+1][j]+=maze[i][j];
        }
    }
    ll ans = 0;
    rep(i,h-1)rep(j,w-1){
        if(maze[i][j]>0){
            ans += (y[i+1]-y[i])*(x[j+1]-x[j]);
        }
    }
    cout << ans << endl;
    return 0;
}