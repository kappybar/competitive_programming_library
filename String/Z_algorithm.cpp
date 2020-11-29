#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
typedef long long ll;
typedef pair<int,int> P;
const int INF = 1e9;
const int MOD = 1000000007;

int main(){
    /*Z-algorithm 文字列sについて各iについてsとs[i:]の最長共通接頭辞の長さを記録した配列をつくる。
    https://snuke.hatenablog.com/entry/2014/12/03/214243*/

    string s;
    cin >> s;
    vector<int> A(s.size(),0);

    int c = 0;
    for(int i=1;i<s.size();i++){
        if(i + A[i-c] < c + A[c]){
            A[i] = A[i-c];
        }
        else{
            int j = max(0,c+A[c]-i);
            while(i+j < s.size() && s[j] == s[i+j]) j ++;
            A[i] = j;
            c = i;
        }
    }
    A[0] = s.size();
    rep(i,s.size()) cout << A[i] << endl;
}