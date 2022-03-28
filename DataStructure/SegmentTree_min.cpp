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

struct Segmenttree{
    int n;
    vector<long long> node;

    Segmenttree(vector<long long> v){
        n = (int)(v.size());
        node.resize(2*n);
        for(int i=0;i<n;i++) node[i+n] = v[i];
        for(int i=n-1;i>=0;i--) node[i] = min(node[i<<1],node[i<<1|1]);
    }
    //i番目の要素をxに変更する
    void update(int i,long long x){
        i += n;
        node[i] = x;
        while(i>1){
            i >>= 1;
            node[i] = min(node[i<<1],node[i<<1|1]);
        }
    }
    //[l,r)の要素のminを求める
    long long query(int l,int r){
        long long res = LINF;
        l += n; r += n;
        while(l<r){
            if(l&1) res = min(res,node[l++]);
            if(r&1) res = min(res,node[--r]);
            l >>= 1; r >>= 1;
        }
        return res;
    }
    //i番目の要素にアクセス
    long long getval(int i){
        return node[i+n];
    }
};

// 要素を変えるときは必ず update !!!!!!!!!!!!!!! log(n)かける絶対!!!!??!?!

int main(){
    int n,q;
    cin >> n >> q;
    Segmenttree seg(vector<ll>(n,INT_MAX));
    while(q--){
        int t,x,y;
        cin >> t >> x >> y;
        if(t==0){
            seg.update(x,y);
        }else{
            cout << seg.query(x,y+1) << endl;
        }
    }
    return 0;
}