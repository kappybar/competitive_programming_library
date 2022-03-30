#include <bits/stdc++.h>

long long str_int(const std::string& s, int base=10) {
    long long res = 0;
    for(int i = 0;i < (int)s.size(); i++) {
        res = res * base + (s[i] - '0');
    }
    return res;
}

// parse s as number (double or long)
// return number * (base ^ pow_base)
// ex) str_float_int("0.45", 2, 10) = 0.45 * 10^2 = 45
long long str_float_int(const std::string& s, int pow_base, int base=10) {
    long long t = 1;
    for(int i = 0;i < pow_base; i++) t *= base;

    int ind = -1;
    for(int i = 0;i < (int)s.size(); i++) {
        if(s[i] == '.') ind = i;
    }

    if(ind == -1) return str_int(s, base) * t;
    long long res = str_int(s.substr(0, ind), base) * t;
    std::string under_point = s.substr(ind + 1);
    while((int)under_point.size() < pow_base) under_point += "0";
    res += str_int(under_point, base);
    return res;
}
