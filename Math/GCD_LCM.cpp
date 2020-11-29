#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
using ll =  long long ;
using P = pair<int,int> ;
const int INF = 1e9;
const int MOD = 1000000007;

ll gcd(ll i,ll j){
    if(j == 0) return i;
    return gcd(j,i%j);
}

ll lcm(ll i,ll j){
    return i / gcd(i,j) * j;
}

