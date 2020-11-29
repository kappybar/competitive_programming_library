#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
const int INF = 1e9;
const int MOD = 1000000007;
#define rep(i,n) for(int i=0;i<n;i++)

struct Unionfind{
    vector<int> parents;
    int n;
    Unionfind(int n):n(n),parents(n,-1){ }

    int find(int x){
        if(parents[x] < 0) return x;
        else return parents[x] = find(parents[x]);
    }

    void unite(int x,int y){
        x = find(x);
        y =  find(y);

        if(x==y) return;
        if(parents[x] > parents[y]) swap(x,y);
        parents[x] += parents[y];
        parents[y] = x;
    }  

   int size(int x){
       return -parents[find(x)];
   }

   bool same(int x,int y){
       return find(x)==find(y);
   }

   vector<int> members(int x){
       int root = find(x);
       vector<int> member;
       for(int i=0;i<n;i++){
           if(find(i)==root ){
               member.push_back(i);
           }
       }
      return member;
  }

  int group_cnt(){
      int c = 0;
      rep(i,n){
          if(parents[i] < 0) ++c;
      }
      return c;
  }
};

int main(){
    int n,q;
    cin >> n >> q;
    Unionfind uf(n);
    rep(i,q){
        int c,x,y;
        cin >> c >> x >> y;
        if(c==0) uf.unite(x,y);
        else{
            if(uf.same(x,y)) cout << 1 << endl;
            else cout << 0 << endl;
        }
    }
    return 0;
}
