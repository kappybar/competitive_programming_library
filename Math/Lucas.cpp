int Lucas(int n,int k){
    if((n & k) == k) return 1;
    return 0;
}

// Lucasの定理
// mod2で　combination(n,k) をもとめる。