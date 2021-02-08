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

template<int char_size,int base>
struct Trie{
    struct Node{
        vector<int> children; //子の頂点番号、存在しないなら-1
        vector<int> accept;   //末端がこの頂点になる語の番号
        int c;                //文字
        Node(int c):c(c){
            children.assign(char_size,-1);
        }
    };

    vector<Node> trie;
    int root;
    int sum;

    Trie():root(0),sum(0){
        trie.push_back(Node(-1)); // 空文字
    }

    //文字列挿入
    void insert(const string &s){
        int node = 0;
        for(int i=0;i<(int)s.size();i++){
            int c = (int)(s[i] - base);
            int &nxt = trie[node].children[c];
            if(nxt == -1){
                nxt = (int)trie.size();
                trie.push_back(Node(c));
                node = nxt;
            }else{
                node = nxt;
            }
        }
        trie[node].accept.push_back(sum++);
    }

    //文字列検索
    bool search(const string &s,bool prefix = false){
        int node = 0;
        for(int i=0;i<(int)s.size();i++){
            int c = (int)(s[i] - base);
            int nxt = trie[node].children[c];
            if(nxt == -1) return false;
            node = nxt;
        }
        return prefix ? true : (int)(trie[node].accept.size()) > 0;
    }

    //sをprefixにもつ文字があるかどうか
    bool search_prefix(const string &s){
        return search(s,true);
    }

    //挿入した文字列の数
    int count_word() const {return sum;}
    //挿入した頂点の数
    int count_vertex() const {return (int)trie.size();}
    inline const Node& operator[](int i)const{ return trie[i];} 
};

int main(){
    int n;
    cin >> n;
    Trie<26,'a'> tr;
    rep(i,n){
        string s;
        cin >> s;
        reverse(s.begin(),s.end());
        tr.insert(s);
    }
    int v = tr.count_vertex();

    ll ans = 0;
    vector<vector<int>> dp(v,vector<int>(26,-1));
    vector<int> cnt(v,-1);
    auto dfs = [&](auto&& dfs,int i) -> void{
        if(dp[i][0] != -1) return;
        vector<int> tmp(26,0);
        cnt[i] = 0;
        rep(j,26) dp[i][j] = 0;
        for(int j=0;j<26;j++){
            if(tr[i].children[j] == -1) continue;
            int vv = tr[i].children[j];
            dfs(dfs,vv);
            rep(k,26) dp[i][k] += dp[vv][k];
            cnt[i] += cnt[vv];

            tmp[tr[vv].c] += tr[vv].accept.size();
        }
        rep(j,26){
            if(tmp[j] == 1) ans += dp[i][j]-1;
        }
        if((int)tr[i].accept.size() > 0) ++cnt[i];
        if(tr[i].c != -1){
            dp[i][tr[i].c] += cnt[i] - dp[i][tr[i].c];
        }
        return;
    };
    dfs(dfs,0);
    cout << ans << endl;
    return 0;
}