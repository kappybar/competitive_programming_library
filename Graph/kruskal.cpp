#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
using ll =  long long ;
using P = pair<int,int> ;
const int INF = 1e9;
const int MOD = 1000000007;
int v = 10005,e = 100005;

struct edge{

    int from,to,cost;
    
    edge(int cost,int from,int to):cost(cost),from(from),to(to){}

    bool operator< (const edge &right){ return cost < right.cost;}
    bool operator> (const edge &right){ return cost > right.cost;}
    bool operator<= (const edge &right){ return cost <= right.cost;}
    bool operator>= (const edge &right){ return cost >= right.cost;}
};

vector<edge> EG;

struct Unionfind{
    vector<int> parents;
    int m;
    Unionfind(int n):parents(n,-1){
        m = n;
    }

    int find(int x){
        if(parents.at(x) < 0){
            return x;
        }else{
            parents.at(x) = find(parents.at(x));
            return parents.at(x);
        }
    }

    void unite(int x,int y){
        x = find(x);
        y = find(y);

        if(x==y) return;
        if(parents.at(x) > parents.at(x))swap(x,y);
        parents.at(x) += parents.at(y);
        parents.at(y) = x;
    }  

   int size(int x){
       return -parents.at(find(x));
   }

   bool same(int x,int y){
       return find(x) ==find(y);
   }

   vector<int> members(int x){
       int root = find(x);
       vector<int> A;
       for(int i=0;i<m;i++){
           if(find(i) ==root ){
               A.push_back(i);
           }
       }
      return A;
  }
};

int kruskal(){
    int res = 0;
    Unionfind uf(v);
    sort(EG.begin(),EG.end());
    for(edge ed:EG){
        if(uf.same(ed.from,ed.to)) continue;
        uf.unite(ed.from,ed.to);
        res += ed.cost;
    }
    return res;
}


int main(){
    cin >> v >> e;
    rep(i,e){
        int s,t,w;
        cin >> s >> t >> w;
        edge ed(w,s,t);
        EG.push_back(ed);
    }

    int cost = kruskal();
    cout << cost << endl;
    return 0;
}