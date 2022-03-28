
#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define popcount(x) __builtin_popcountll(x)
using namespace std;
using ll = long long;
using P = pair<int,int>;
using pll = pair<long long,long long>;
const int inf = 1e9+10;
const long long INF = 4e18;
const int MOD = 1000000007;
//const int MOD = 998244353;
const double PI = 3.14159265358979323846;
template<class T, class K>bool chmax(T &a, const K b) { if (a<b) { a=b; return true; } return false; }
template<class T, class K>bool chmin(T &a, const K b) { if (b<a) { a=b; return true; } return false; }
#ifdef LOCAL_
#define debug(var)  do{std::cerr << "\033[1;36m" << #var << ": \033[0m";view(var);std::cerr << std::endl;}while(0)
template<typename T> void view(T e){std::cerr << e;}
template<typename T, typename K> void view(pair<T, K> e){std::cerr << "("; view(e.first); std::cerr << ", "; view(e.second); std::cerr << ")";}
template<typename T> void view(const set<T> &st){ std::cerr << "\n";for(const auto& e : st){view(e); std::cerr << " ";}}
template<typename T, typename K> void view(const map<T, K> &mp){ std::cerr << "\n";for(const auto& [k, v]: mp){std::cerr << "("; view(k); std::cerr << ", "; view(v); std::cerr << ") ";}}
template<typename T, typename K> void view(const unordered_map<T, K> &mp){ std::cerr << "\n";for(const auto& [k, v]: mp){std::cerr << "("; view(k); std::cerr << ", "; view(v); std::cerr << ") ";}}
template<typename T> void view(const std::vector<T>& v){std::cerr << "\n";for(const auto& e : v){ view(e); std::cerr << " "; }}
template<typename T> void view(const std::vector<std::vector<T>>& vv){std::cerr << "\n";int cnt = 0;for(const auto& v : vv){cerr << cnt << "th : "; view(v); cnt++; std::cerr << std::endl;}}
#else
#define debug(...) (void(0))
#endif
