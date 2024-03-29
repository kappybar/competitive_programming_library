#include <bits/stdc++.h>


// basic parsing

// true   if s[i++] == c
// false  otherwise
bool consume(const std::string &s, int &i, char c) {
    if (s[i] != c) return false;
    i++;
    return true;
}

void expect(const std::string &s, int &i, char c) {
    assert(s[i] == c);
    i++;
    return; 
}

int number(const std::string &s, int &i);
int factor(const std::string &s, int &i); 
int mul(const std::string &s, int &i);   
int expr(const std::string &s, int &i);


// number = [0 - 9]*
int number(const std::string &s, int &i) {
    int res = 0;

    while (isdigit(s[i])) {
        res = 10 * res + (s[i] - '0');
        i++;
    }

    return res;
}

// factor = "(" expr ")" | number
int factor(const std::string &s, int &i) {
    if (consume(s, i, '(')) {
        int res = expr(s, i);
        expect(s, i, ')');
        return res;
    }
    return number(s, i);
}


// mul = factor ("*" factor | "/" factor )* 
int mul(const std::string &s, int &i) {
    int res = factor(s, i);

    while (1) {
        if (consume(s, i, '*')) {
            res *= factor(s, i);
            continue;
        } 
        if (consume(s, i, '/')) {
            res /= factor(s, i);
            continue;
        } 
        break;
    }

    return res;
}

// expr = mul ("+" mul | "-" mul)* 
int expr(const std::string &s, int &i) {
    int res = mul(s, i);

    while (1) {
        if (consume(s, i, '+')) {
            res += mul(s, i);
            continue;
        } 
        if (consume(s, i, '-')) {
            res -= mul(s, i);
            continue;
        } 
        break;
    }

    return res;
}

