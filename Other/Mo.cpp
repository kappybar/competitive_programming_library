#include <bits/stdc++.h>

// Mo algorithm 

// T ans;
// void add(int i);
// void del(int i);

template<typename T, void (*add)(int), void (*del)(int)>
struct Mo {
private:
    int n, q;
    std::vector<int> l, r;

public:
    Mo(int n):n(n), q(0) {
        l.reserve(n);
        r.reserve(n);
    }

    // [left, right)
    void add_query(int left, int right) {
        q++;
        l.push_back(left);
        r.push_back(right);
        return;
    }

    std::vector<T> answer(void) {
        int sq = std::sqrt(n);

        std::vector<int> qi(q, 0);
        std::iota(qi.begin(), qi.end(), 0);
        std::vector<int> lblock(q);
        for (int i = 0;i < q; i++) lblock[i] = l[i] / sq;
        sort(qi.begin(), qi.end(), [&](const int &i, const int &j) {
            if (lblock[i] != lblock[j]) return l[i] < l[j];
            if (lblock[i] % 2 == 1) return r[i] > r[j];
            return r[i] < r[j];
        });

        std::vector<T> queryans(q);
        int nl = 0, nr = 0;
        for(int i : qi) {
            while(nl > l[i]) add(--nl);
            while(nr < r[i]) add(nr++);
            while(nl < l[i]) del(nl++);
            while(nr > r[i]) del(--nr);

            queryans[i] = ans;
        }

        return queryans;
    } 

};

