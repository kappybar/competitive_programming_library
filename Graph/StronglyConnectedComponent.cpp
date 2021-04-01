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
    vector<vector<int>> graph_dag;//scc後のgraph

    scc_graph(int n):n(n),graph(n),revgraph(n),seen(n,-1){}

    void add_edge(int from,int to){
        graph[from].push_back(to);
        revgraph[to].push_back(from);
    }

    vector<vector<int>> scc(bool make_graph_dag = false){
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

        if(make_graph_dag){
            graph_dag.resize(k);
            for(int i=0;i<n;i++){
                for(int j:graph[i]){
                    int new_i = seen[i];
                    int new_j = seen[j];
                    if(new_i == new_j) continue;
                    graph_dag[new_i].push_back(new_j);
                }
            }
            for(int i=0;i<k;i++){
                sort(graph_dag[i].begin(),graph_dag[i].end());
                graph_dag[i].erase(unique(graph_dag[i].begin(),graph_dag[i].end()),graph_dag[i].end());
            }
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

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    scc_graph G(n);
    rep(i,m){
        int a,b;
        scanf("%d%d",&a,&b);
        G.add_edge(a,b);
    }

    vector<vector<int>> ans = G.scc();

    printf("%d\n",(int)ans.size());
    rep(i,ans.size()){
        printf("%d ",(int)ans[i].size());
        rep(j,ans[i].size()){
            printf("%d ",ans[i][j]);
        }
        printf("\n");
    }

    return 0;
}