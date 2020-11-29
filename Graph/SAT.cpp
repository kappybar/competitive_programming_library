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


//StronglyConnectedCompoinent
struct scc_graph{
    int n;
    vector<vector<int>> graph;
    vector<vector<int>> revgraph;
    vector<int> postorder;
    vector<int> seen;

    scc_graph(int n):n(n),graph(n),revgraph(n),seen(n,-1){}

    void add_edge(int from,int to){
        graph[from].push_back(to);
        revgraph[to].push_back(from);
    }

    vector<vector<int>> scc(){
        fill(seen.begin(),seen.end(),-1);
        for(int i=0;i<n;i++){
            if(seen[i]<0) dfs(i);
        }
        fill(seen.begin(),seen.end(),-1);

        int k = 0;
        for(int i=(int)postorder.size()-1;i>=0;i--){
            if(seen[postorder[i]]<0) revdfs(postorder[i],k++);
        }

        vector<vector<int>> scc_groups(k);
        for(int i=0;i<n;i++){
            scc_groups[seen[i]].push_back(i);
        }

        return scc_groups;
    }

    void dfs(int i){
        seen[i] = 1;
        for(int j:graph[i]){
            if(seen[j]>=0) continue;
            dfs(j);
        }
        postorder.push_back(i);
    }

    void revdfs(int i,int k){
        seen[i] = k;
        for(int j:revgraph[i]){
            if(seen[j]>=0) continue;
            revdfs(j,k);
        }
    }
};

//twosat
struct twosat{
    int n;
    scc_graph G;
    vector<bool> answers;
    twosat(int n):n(n),G(2*n),answers(n,false){}

    void add_clause(int i,bool f,int j,bool g){
        if(f&&g)  { G.add_edge(i+n,j); G.add_edge(j+n,i);  }
        else if(g){ G.add_edge(i,j);   G.add_edge(j+n,i+n);}
        else if(f){ G.add_edge(j,i);   G.add_edge(i+n,j+n);}
        else      { G.add_edge(i,j+n); G.add_edge(j,i+n);  }
    }

    bool satisfiable(){
        G.scc();
        rep(i,n){
            if(G.seen[i] == G.seen[i+n]) return false;
        }
        rep(i,n){
            if(G.seen[i] > G.seen[i+n]) answers[i] = true;
        }
        return true;
    }

    vector<bool> answer(){ return answers;}
};


int main(){
    int n,d;
    scanf("%d%d",&n,&d);
    vector<int> x(n),y(n);
    rep(i,n){
        scanf("%d%d",&x[i],&y[i]);
    }
    twosat ts(n);
    rep(i,n)rep(j,i){
        if(abs(x[i]-x[j])<d){
            ts.add_clause(i,false,j,false);
        }
        if(abs(x[i]-y[j])<d){
            ts.add_clause(i,false,j,true);
        }
        if(abs(y[i]-x[j])<d){
            ts.add_clause(i,true,j,false);
        }
        if(abs(y[i]-y[j])<d){
            ts.add_clause(i,true,j,true);
        }
    }

    if(!ts.satisfiable()){
        cout << "No" << endl;
        return 0;
    }

    cout << "Yes" << endl;
    vector<bool> ans = ts.answer();

    for(int i=0;i<n;i++){
        if(ans[i]) cout << x[i] << endl;
        else cout << y[i] << endl;
    }
    return 0;
}