#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
typedef long long ll;
typedef pair<int,int> P;
const int INF = 1e9;
const int MOD = 1000000007;

int main(){
    /*manacherとは文字列sについてiを真ん中のidxとした最長回文の長さを求められるアルゴリズム
    https://snuke.hatenablog.com/entry/2014/12/02/235837*/
    string s;
    cin >> s;
    vector<int> R(s.size());
    int c = 0;
    for(int i=0;i<s.size();i++){
        int l = c - (i-c);
        if(i+R[l] < c+R[c]){
            R[i] = R[l];
        }
        else{
            int j = c + R[c] -i;
            while(i-j >= 0 && i+j < s.size() && s[i+j] == s[i-j]) j ++;
            R[i] = j;
            c = i;
        }
    }

    rep(i,s.size()) cout << R[i] << endl;
}