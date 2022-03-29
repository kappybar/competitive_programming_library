#include <bits/stdc++.h>

// only min, max
template<typename T>
struct SparseTable{
private:
    std::vector<std::vector<T>> table;
    std::vector<int> log_table;
public:
    SparseTable(const std::vector<T> &v) {
        int n = (int)v.size();
        log_table.assign(n+1, 0);
        for(int i = 2;i <= n; i++) log_table[i] = log_table[i >> 1] + 1;
        table.assign(log_table[n] + 1, std::vector<T>(n, 0));
        for(int i = 0;i < n; i++) table[0][i] = v[i];
        for(int i = 1;i <= log_table[n]; i++) {
            for(int j = 0;(j + (1 << (i - 1))) < n; j++) {
                table[i][j] = std::min(table[i-1][j], table[i-1][j + (1 << (i-1))] );
            }
        }
    }
    // [l,r)
    T query(int l, int r) {
        int len = r - l;
        return std::min(table[log_table[len]][l], table[log_table[len]][r - (1 << log_table[len])]);
    }
};
