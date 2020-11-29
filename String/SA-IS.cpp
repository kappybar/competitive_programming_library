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

vector<int> induced_sort(vector<int> s,int alphabet_size=26){
    int n = (int)s.size();
    if(n==1){
        vector<int> res(1,0);
        return res;
    }
    s.push_back(0); // dummy char

    vector<int> cnt(alphabet_size+1,0); // the number of alphabet size
    cnt[0] = 1; // dummy char
    vector<int> t(n+1); // L:1 S:0
    t[n] = 0;
    for(int i=n-1;i>=0;i--){
        if(s[i] < s[i+1]) t[i] = 0;
        else if(s[i] > s[i+1]) t[i] = 1;
        else t[i] = t[i+1];
        cnt[s[i]] ++;
    }
    vector<int> sa(n+1,-1),st(alphabet_size+1,0),ed(alphabet_size+1,0),current_idx(alphabet_size+1,0);

    for(int i=0;i<=alphabet_size;i++) ed[i] = cnt[i];
    for(int i=0;i<alphabet_size;i++) ed[i+1] += ed[i];
    for(int i=1;i<=alphabet_size;i++) st[i] = ed[i-1];
    for(int i=0;i<=alphabet_size;i++) current_idx[i] = ed[i];
    
    vector<int> lms(n+1,0); // lms:1
    vector<int> lms_index; // lms index
    for(int i=1;i<=n;i++){ // lms index -> insert
        if(t[i] == 0 && t[i-1] == 1){
            lms[i] = 1;
            lms_index.push_back(i);
            int now_alphabet = s[i];
            sa[--current_idx[now_alphabet]] = i;
        }
    }

    for(int i=0;i<=alphabet_size;i++) current_idx[i] = st[i];
    for(int i=0;i<=n;i++){
        if(sa[i] == -1 || sa[i] == 0) continue;
        if(t[sa[i] - 1] == 1){
            int now_alphabet = s[sa[i]-1];
            sa[current_idx[now_alphabet]++] = sa[i]-1;
        }
    }

    for(int i=0;i<=alphabet_size;i++) current_idx[i] = ed[i];
    for(int i=n;i>=0;i--){
        if(sa[i] == -1 || sa[i] == 0) continue;
        if(t[sa[i]-1] == 0){
            int now_alphabet = s[sa[i]-1];
            sa[--current_idx[now_alphabet]] = sa[i]-1;
        }
    }


    int cnt_ = 0;
    int order = 0;
    vector<int> now;
    vector<int> lms_(n+1,0);
    for(int i=0;i<=n;i++){
        if(lms[sa[i]] == 1){
            ++cnt_;
            int id_ = sa[i];
            vector<int> now_ = {s[id_++]};
            while(id_ <= n && lms[id_] == 0){
                now_.push_back(s[id_++]);
            }
            if(id_<=n) now_.push_back(s[id_]);

            if(now == now_){
                lms_[sa[i]] = order;
            }else{
                lms_[sa[i]] = ++order;
                swap(now,now_);
            }
        }
    }

    vector<int> rec_sa;
    for(int i=0;i<=n;i++){
        if(lms_[i] > 0){
            rec_sa.push_back(lms_[i]);
        }
    }
    vector<int> lms_suffix_array;

    if(order == cnt_){
        lms_suffix_array.resize(order);
        int c = 0;
        for(int i=0;i<=n;i++){
            if(lms[sa[i]] == 1){
                lms_suffix_array[c++] = sa[i];
            }
        }
    }else{
        lms_suffix_array = induced_sort(rec_sa,(int)rec_sa.size()+1);
        for(int i=0;i<lms_suffix_array.size();i++) lms_suffix_array[i] = lms_index[lms_suffix_array[i]];
    }

    fill(sa.begin(),sa.end(),-1);
    for(int i=0;i<=alphabet_size;i++) current_idx[i] = ed[i];
    reverse(lms_suffix_array.begin(),lms_suffix_array.end());

    for(int i:lms_suffix_array){ // lms index -> insert
        int now_alphabet = s[i];
        sa[--current_idx[now_alphabet]] = i;
    }

    for(int i=0;i<=alphabet_size;i++) current_idx[i] = st[i];
    for(int i=0;i<=n;i++){
        if(sa[i] == -1 || sa[i] == 0) continue;
        if(t[sa[i] - 1] == 1){
            int now_alphabet = s[sa[i]-1];
            sa[current_idx[now_alphabet]++] = sa[i]-1;
        }
    }

    for(int i=0;i<=alphabet_size;i++) current_idx[i] = ed[i];
    for(int i=n;i>=0;i--){
        if(sa[i] == -1 || sa[i] == 0) continue;
        if(t[sa[i]-1] == 0){
            int now_alphabet = s[sa[i]-1];
            sa[--current_idx[now_alphabet]] = sa[i]-1;
        }
    }

    vector<int> res(n);
    for(int i=0;i<n;i++) res[i] = sa[i+1];
    return res;
}

vector<int> SA_IS(string str){
    vector<int> s((int)str.size(),0);
    for(int i=0;i<(int)str.size();i++) s[i] = str[i]-'a'+1;
    return induced_sort(s);
}

vector<int> lcp_construction(vector<int> s,vector<int> sa){
    int n = (int)s.size();
    vector<int> rank(n),lcp(n);
    rep(i,n) rank[sa[i]] = i;

    int h = 0;
    lcp[0] = h;
    for(int i=0;i<n;i++){
        if(rank[i] == n-1) lcp[rank[i]] = 0;
        else{
            int j = sa[rank[i]+1];
            if(h>0) --h;
            while(i+h<n&&j+h<n){
                if(s[i+h]!=s[j+h]) break;
                ++h;
            }
            lcp[rank[i]] = h;
        }
    }

    return lcp;
}


int main(){
    string str;
    cin >> str;
    int n = str.size();
    vector<int> s(n);
    rep(i,n) s[i] = str[i]-'a'+1;
    vector<int> sa = SA_IS(str);
    vector<int> lcp = lcp_construction(s,sa);
    ll ans = (ll)n*((ll)n+1)/2;
    rep(i,n){
        ans -= lcp[i];
    }
    cout << ans << endl;
    return 0;
}