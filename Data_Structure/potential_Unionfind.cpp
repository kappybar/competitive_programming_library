#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
const int INF = 1e9;
const int MOD = 1000000007;
#define rep(i,n) for(int i=0;i<n;i++)

struct potential_Unionfind{
    vector<int> parents;
    vector<int> weights;
    int m;
    potential_Unionfind(int n):parents(n,-1){
        m = n;
        weights.resize(n);
    }

    int find(int x){
        if(parents[x] < 0) return x;
        else{
            int p = find(parents[x]);
            weights[x] += weights[parents[x]];
            return parents[x] = p;
        }
    }

    //weight[y] - weights[x] = wとなるようにuniteする。
    bool unite(int x,int y,int w){
        w += weight(x);
        w -= weight(y);
        x = find(x);
        y = find(y);
        if(x == y) return false;//もうすでに繋がれている頂点ならfalseを返す
        if(parents[x] > parents[y]) {swap(x,y); w = -w;}
        parents[x] += parents[y];
        parents[y] = x;
        weights[y] = w;
        return true;
    }

    bool same(int x,int y){
        return find(x) == find(y);
    }

    //weightsは各頂点から根までの距離
    int weight(int x){
        find(x);
        return weights[x];
    }

    //まずsame(x,y)で繋がっているかわからないと正しい答えは出てこない
    int diff(int x,int y){
         return weight(y) - weight(x);
    }


};

int main(){
    int n,q;
    cin >> n >> q;
    potential_Unionfind uf(n);
    rep(i,q){
        int c;
        cin >> c;
        if(c==0){
            int x,y,z;
            cin >> x >> y >> z;
            uf.unite(x,y,z);
        }else{
            int x,y;
            cin >> x >> y;
            int ans = uf.diff(x,y);
            if(!uf.same(x,y)) cout << '?' << endl;
            else cout << uf.diff(x,y) << endl;
        }
    }
    return 0;

}
