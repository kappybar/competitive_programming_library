#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
const ll INF = INT_MAX;
const int MOD = 1000000007;
#define rep(i,n) for(int i=0;i<n;i++)

//非再帰セグ木

struct Segmenttree{
    int n;
    vector<long long> node;

    Segmenttree(vector<long long> v){
        n = (int)(v.size());
        node.resize(2*n);
        for(int i=0;i<n;i++) node[i+n] = v[i];
        for(int i=n-1;i>=0;i--) node[i] = node[i<<1] + node[i<<1|1];
    }
    //i番目の要素にxを足す
    void update(int i,long long x){
        i += n;
        node[i] += x;
        while(i>1){
            i >>= 1;
            node[i] = node[i<<1] + node[i<<1|1];
        }
    }
    //[l,r)の要素の和を求める
    long long query(int l,int r){
        long long res = 0;
        l += n; r += n;
        while(l<r){
            if(l&1) res += node[l++];
            if(r&1) res += node[--r];
            l >>= 1; r >>= 1;
        }
        return res;
    }
    //i番目の要素にアクセス
    long long getval(int i){
        return node[i+n];
    }
};

//1-index SegmentTree は 
/*        001
      010    011
    100 101 110 111

    一つ上は i>>1で得ることができる。つまりbitの一番下の桁以外の部分を共有しているindexの要素を加えたものだと見ることができる。
*/

int main(){
    int n,q;
    cin >> n >> q;
    Segmenttree seg(vector<ll>(n,0));
    while(q--){
        int t,x,y;
        cin >> t >> x >> y;
        if(t==0){
            --x;
            seg.update(x,y);
        }else{
            --x;--y;
            cout << seg.query(x,y+1) << endl;
        }
    }
    return 0;
}
