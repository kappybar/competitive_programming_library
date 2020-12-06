#include<stdio.h>
#include<stdlib.h>

char s[1000005];
int s_[1000005];
int ans[1000005];
int lcp[1000005];
//S:0
//L:1

// n: strとresのサイズ
// res:　結果の配列
// resは全部0で渡してくれればいい
// str: 文字列の数字表記
// LMS_size: LMSのサイズ
// LMS: LMSのindex
// T: T[i] = 0(S),1(L)
// char_size: alphabet_size
void induced_sort(int n,int *res,int *str,int LMS_size,int *LMS,int *T,int char_size){
    int *ed = (int *)calloc(char_size+1,sizeof(int)); // それぞれの文字のバケツの後端
    int *st = (int *)calloc(char_size+1,sizeof(int)); //　それぞれの文字のバケツの前端
    if(ed == NULL || st == NULL){ res[0] = -1; return;} // 失敗
    for(int i=0;i<n;i++) ed[str[i]+1] ++;
    for(int i=1;i<=char_size;i++) ed[i] += ed[i-1];
    for(int i=1;i<=char_size;i++) st[i] = ed[i-1];//[st,ed)

    int *idx = (int *)calloc(char_size+1,sizeof(int)); // 今のindex
    if(idx == NULL) {res[0] = -1; return; } //失敗
    for(int i=0;i<=char_size;i++) idx[i] = ed[i];

    for(int i=LMS_size-1;i>=0;i--){
        int c = str[LMS[i]];
        res[--idx[c+1]] = LMS[i]; //LMSは後ろから詰める
    }
    for(int i=0;i<=char_size;i++) idx[i] = st[i];
    for(int i=0;i<n;i++){// Lを前から詰める
        if(res[i] == 0 || T[res[i]-1] == 0) continue; // 一個前がSだったらダメ
        int c = str[res[i]-1];
        res[idx[c+1]++] = res[i]-1;
    }
    for(int i=0;i<=char_size;i++) idx[i] = ed[i];
    for(int i=n-1;i>=0;i--){// Sを後ろから詰める
        if(res[i] == 0 || T[res[i]-1] == 1) continue; // 一個前がLだったらダメ
        int c = str[res[i]-1];
        res[--idx[c+1]] = res[i]-1;
    }
    free(st);
    free(ed);
    free(idx);
    return;
}

// n: resとstrのサイズ
// res:結果
// str:文字列の数値化
// char_size: alphabet_size
void sa_is(int n,int *res,int *str,int char_size){
    int *T = (int *)calloc(n,sizeof(int)); // T: T[i] = 0(S),1(L)
    int *LMS = (int *)calloc(n,sizeof(int)); // LMS index
    int *LMS_ = (int *)calloc(n,sizeof(int)); // LMS_[i] 1 if i index LMS, 0 not
    if(T == NULL || LMS == NULL || LMS_ == NULL){ res[0] = -1; return;}
    int LMS_size = 0;

    for(int i=n-2;i>=0;i--){
        if(str[i] < str[i+1]) T[i] = 0; // S
        else if(str[i] > str[i+1]) T[i] = 1;// L
        else T[i] = T[i+1];
    }

    for(int i=0;i<n;i++){
        if(T[i] == 0 && (i==0 || T[i-1] == 1)){
            LMS[LMS_size++] = i;
            LMS_[i] = 1;
        }
    }

    int *pre_sa = (int *)calloc(n,sizeof(int));
    if(pre_sa == NULL) {res[0] = -1; return;}
    induced_sort(n,pre_sa,str,LMS_size,LMS,T,char_size);
    if(pre_sa[0]==-1) {res[0] = -1; return;}

    int *orderedLMS = (int *)calloc(LMS_size,sizeof(int));
    if(orderedLMS == NULL){res[0] = -1; return;}
    int index = 0;
    for(int i=0;i<n;i++){
        if(LMS_[pre_sa[i]] == 1) orderedLMS[index++] = pre_sa[i];
    }

    pre_sa[orderedLMS[0]] = 0;
    int rank = 0;
    for(int i=0;i<LMS_size-1;i++){
        int diff = 0;// diff false
        int j = 0;
        int s = orderedLMS[i];
        int t = orderedLMS[i+1];
        while(s+j < n && t+j < n){
            if(str[s+j] != str[t+j] || LMS_[s+j] != LMS_[t+j]){
                diff = 1;
                break;
            }
            if(j>0 && LMS_[s+j]) break;
            ++j;
        }
        if(diff == 1) pre_sa[orderedLMS[i+1]] = ++rank;
        else pre_sa[orderedLMS[i+1]] = rank;
    }

    int* new_str = (int *)calloc(LMS_size+1,sizeof(int));
    if(new_str == NULL) {res[0] = -1; return;}
    index = 0;
    for(int i=0;i<n;i++){
        if(LMS_[i] == 1) new_str[index++] = pre_sa[i]+1;
    }
    free(LMS_);
    free(pre_sa);

    int *new_sa = (int *)calloc(LMS_size+1,sizeof(int));
    if(new_sa == NULL) {res[0] = -1; return;}

    if(rank+1 == LMS_size){
        for(int i=0;i<LMS_size;i++) new_sa[i] = orderedLMS[i];
    }else{
        new_str[LMS_size] = 0;
        sa_is(LMS_size+1,new_sa,new_str,rank+2);
        if(new_sa[0]==-1){res[0] = -1; return;}

        for(int i=0;i<LMS_size;i++){
            new_sa[i] = LMS[new_sa[i+1]];
        }
    }

    free(orderedLMS);
    free(new_str);

    induced_sort(n,res,str,LMS_size,new_sa,T,char_size);
    free(T);
    free(LMS);
    free(new_sa);
    return;
}

void lcp_construction(int n,int* s,int* sa,int* lcp){
    int* rank = (int *)malloc(sizeof(int) * n);
    for(int i=0;i<n;i++) rank[sa[i+1]] = i;
 
    int h = 0;
    lcp[0] = h;
    for(int i=0;i<n;i++){
        if(rank[i] == n-1) lcp[rank[i]] = 0;
        else{
            int j = sa[rank[i]+1+1];
            if(h>0) --h;
            while(i+h<n&&j+h<n){
                if(s[i+h]!=s[j+h]) break;
                ++h;
            }
            lcp[rank[i]] = h;
        }
    }
    return;
}



int main(){
    scanf("%s",s);
    int n = 0;
    while(s[n] != '\0') n++;
    s[n++] = 0;
    for(int i=0;i<n;i++) s_[i] = s[i];

    sa_is(n,ans,s_,128);
    --n;
    lcp_construction(n,s_,ans,lcp);
    long long res = (long long)(n)*(n+1)/2;
    for(int i=0;i<n;i++) res -= lcp[i];
    printf("%lld\n",res);
    return 0;
}