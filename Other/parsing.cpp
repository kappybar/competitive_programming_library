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
const double PI = 3.14159265358979323846;

//ライブラリではない
//構文解析

using State = string::const_iterator;
int number(State &begin); //数
int factor(State &begin); //() or 数
int term(State &begin);   //* or /
int expression(State &begin); //四則演算

//数
int number(State &begin) {
	int res = 0;

	while(isdigit(*begin)) {
		res *= 10;
		res += *begin - '0';
		begin++;
	}

	return res;
}

// () or 数
int factor(State &begin) {
	if(*begin == '(') {
		begin ++;
		int res = expression(begin);
		begin ++;
		return res;
	} else {
		return number(begin);
	}
}

// * or /
int term(State &begin) {
	int res = factor(begin);
	
	while(1){
		if(*begin == '*'){
			begin ++;
			res *= factor(begin);
		}else if(*begin == '/'){
			begin ++;
			res /= factor(begin);
		} else {
			break;
		}
	}

	return res;
}

// + or -
int expression(State &begin) {
	int res = term(begin);

	while(1){
		if(*begin == '+') {
			begin ++;
			res += term(begin);
		}else if(*begin == '-') {
			begin ++;
			res -= term(begin);
		} else {
			break;
		}
	}

	return res;
}


int main(){
	int n;
	cin >> n;
	cin.ignore();

	while(n--){
		string s;
		getline(cin,s);

		State tmp = s.begin();
		cout << expression(tmp) << endl; 
	}
	return 0;
}
