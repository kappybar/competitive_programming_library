#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
using ll =  long long ;
using P = pair<int,int> ;
const int INF = 1e9;
const int MOD = 1000000007;

//a*x + b*y =gcd(a,b)を満たすx、yをもとめる
pair<long long,long long> extgcd(long long a,long long b){
    long long s=a,sx=1,sy=0,t=b,tx=0,ty=1;
    while(s%t!=0){
        long long temp=s/t,u=s-t*temp,ux=sx-temp*tx,uy=sy-temp*ty;
        s=t;sx=tx;sy=ty;
        t=u;tx=ux;ty=uy;
    }
    return {tx,ty};
}

int main(){
    int a,b;
    cin >> a >> b;
    pair<int,int> res = extgcd(a,b);
    cout << res.first << " " << res.second << endl;
    return 0;
}