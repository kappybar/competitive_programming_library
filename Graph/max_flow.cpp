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

template<typename T> 
struct max_flow_graph{
    struct edge{
        int to,rev;
        T cap;
    };
    int n;
    vector<vector<edge>> G;
    vector<int> level;
    vector<int> iter;

    max_flow_graph(int n):n(n),G(n),level(n),iter(n){}

    void add_edge(int from,int to,T cap){
        G[from].push_back(edge{to,(int)(G[to].size()),cap});
        G[to].push_back(edge{from,(int)(G[from].size()-1),0});
    }

    void bfs(int s){
        fill(level.begin(),level.end(),-1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(edge &e:G[v]){
                if(e.cap <= 0 || level[e.to] >= 0) continue;
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }

    T dfs(int v,int t,T f){
        if(v==t) return f;

        for(int &i=iter[v];i<(int)G[v].size();i++){
            edge &e = G[v][i];
            if(e.cap <= 0 || level[v] >= level[e.to]) continue;
            T d = dfs(e.to,t,min(f,e.cap));
            if(d>0){
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }

        return 0;
    }

    T max_flow(int s,int t){
        T flow = 0;
        while(1){
            bfs(s);
            if(level[t]<0) return flow;
            fill(iter.begin(),iter.end(),0);
            T f;
            while((f = dfs(s,t,INF)) > 0){
                flow += f;
            }
        }
    }
};

vector<int> dx = {0,0,1,-1};
vector<int> dy = {1,-1,0,0};

int main(){
    int n,m;
    cin >> n >> m;
    max_flow_graph<int> G(n*m+2);
    auto id = [&](int i,int j){return i+j*n;};
    vector<string> maze(n);
    rep(i,n) cin >> maze[i];
    int s = n*m;
    int t = n*m+1;
    rep(i,n)rep(j,m){
        if(maze[i][j]=='#') continue;

        if((i+j)%2==0) G.add_edge(s,id(i,j),1);
        else G.add_edge(id(i,j),t,1);

        rep(k,4){
            int new_i = i + dx[k];
            int new_j = j + dy[k];
            if(new_i<0||n<=new_i||new_j<0||m<=new_j) continue;
            if(maze[new_i][new_j]=='#') continue;

            if((i+j)%2==0) G.add_edge(id(i,j),id(new_i,new_j),1);
        }
    }
    cout << G.max_flow(s,t) << endl;

    rep(i,n)rep(j,m){
        if(maze[i][j]!='.' || (i+j)%2 == 1) continue;
        for(int k=0;k<G.G[id(i,j)].size();k++){
            if(G.G[id(i,j)][k].cap==0){
                if(G.G[id(i,j)][k].to==s || G.G[id(i,j)][k].to == t) continue;
                int ii = G.G[id(i,j)][k].to % n;
                int jj = G.G[id(i,j)][k].to / n;
                if(maze[ii][jj]!='.') continue;
                if(ii==i+1){
                    maze[i][j] = 'v';
                    maze[ii][jj] = '^';
                }else if(ii==i-1){
                    maze[i][j] = '^';
                    maze[ii][jj] = 'v';
                }else if(jj==j+1){
                    maze[i][j] = '>';
                    maze[ii][jj] = '<';
                }else{
                    maze[i][j] = '<';
                    maze[ii][jj] = '>';
                }
                break;
            }
        }
    }

    rep(i,n){
        cout << maze[i] << endl;
    }
    return 0;
}