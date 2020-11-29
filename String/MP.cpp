#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
typedef long long ll;
typedef pair<int,int> P;
const int INF = 1e9;
const int MOD = 1000000007;

int main(){
    /*MPとは文字列Sが与えられた時に全てのiについて文字列s[0,i-1]の接頭辞と接尾辞がどれくらい一致しているかを記録していくアルゴリズム
    参考　https://snuke.hatenablog.com/entry/2014/12/01/235807*/
    string S;
    cin >> S;
    vector<int> a(S.size()+1);
    a[0] = -1;
    int j = -1;
    for(int i=0;i<S.size();i++){
        while(j >= 0 && S[i] != S[j]) j = a[j];
        j ++;
        a[i+1] = j;
    }

    rep(i,(int)S.size()+1) cout << a[i] << endl;
}