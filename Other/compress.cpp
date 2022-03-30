#include <bits/stdc++.h>

// compress 1
template<typename T>
std::vector<T> compress(std::vector<T> &a) {
    std::vector<T> val = a;
    int n = (int)a.size();
    sort(val.begin(), val.end());
    val.erase(std::unique(val.begin(), val.end()), val.end());
    for(int i = 0;i < n; i++) {
        a[i] = std::lower_bound(val.begin(), val.end(), a[i]) - val.begin();
    }
    return val;
}

// compress 2
template<typename T>
std::vector<T> compress(std::vector<T> &p1, std::vector<T> &p2) {
    std::vector<T> vals;
    for(int i = 0;i < (int)p1.size(); i++) {
        vals.push_back(p1[i]);
        vals.push_back(p1[i] + 1);
    }
    for(int i = 0;i < (int)p2.size(); i++) {
        vals.push_back(p2[i]); 
        vals.push_back(p2[i] + 1);
    }
    sort(vals.begin(), vals.end());
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
    for(int i = 0;i < (int)p1.size(); i++) {
        p1[i] = std::lower_bound(vals.begin(), vals.end(), p1[i]) - vals.begin();
    }
    for(int i = 0;i < (int)p2.size(); i++) {
        p2[i] = std::lower_bound(vals.begin(), vals.end(), p2[i]) - vals.begin();
    }
    return vals;
}

// p1 & p2 change into compress point 
// vals means original point before compressed
// so vals[p1[i]] & vals[p2[i]] means original points

