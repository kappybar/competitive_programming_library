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
        int par;              //親の頂点番号
        vector<int> children; //子の頂点番号、存在しないなら-1
        vector<int> accept;   //末端がこの頂点になる語の番号
        int c;                //文字
        Node(int par,int c):par(par),c(c){
            children.assign(char_size,-1);
        }
    };

    vector<Node> trie;
    int root;
    int sum;

    Trie():root(0),sum(0){
        trie.push_back(Node(-1,-1)); // 空文字
    }

    //文字列挿入
    void insert(const string &s){
        int node = 0;
        for(int i=0;i<(int)s.size();i++){
            int c = (int)(s[i] - base);
            int &nxt = trie[node].children[c];
            if(nxt == -1){
                nxt = (int)trie.size();
                trie.push_back(Node(node,c));
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
    vector<int> ind;

    rep(i,v){
        if((int)tr[i].accept.size() > 0) ind.push_back(i);
    }

    rep(i,n){
        set<int> suffix;
        int idx = ind[i];
        while(idx >= 0){
            rep(i,26){
                if(suffix.count(i) == 0) continue;
                int vv = tr[idx].children[i];
                if(vv == -1) continue;
                if((int)tr[vv].accept.size() > 0) ans ++;
            }
            suffix.insert(tr[idx].c);
            idx = tr[idx].par;
        }
    }
    cout << ans-(ll)n << endl;
    return 0;
}