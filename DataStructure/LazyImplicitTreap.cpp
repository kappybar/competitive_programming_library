#include <bits/stdc++.h>

template<typename S, S (*op)(S, S), S (*e)(), typename F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct LazyImplicitTreap {
private:
    struct Node {
        S value, acc;
        F lazy;
        int priority, cnt, rev;
        std::unique_ptr<Node> lhs, rhs;

        Node(S value, S acc, F lazy, int priority, int cnt=1, int rev=0, std::unique_ptr<Node> lhs = nullptr, std::unique_ptr<Node> rhs = nullptr) 
            :value(value), acc(acc), lazy(lazy), priority(priority), cnt(cnt), rev(rev), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
    };
    std::unique_ptr<Node> root;
    std::random_device seed_gen;
    std::mt19937 rnd;

    int get_cnt(const std::unique_ptr<Node> &node) {
        return node ? node->cnt : 0;
    }

    void update_cnt(std::unique_ptr<Node> &node) {
        if (node) {
            node->cnt = get_cnt(node->lhs) + 1 + get_cnt(node->rhs);
        }
    }

    S get_acc(const std::unique_ptr<Node> &node) {
        return node ? node->acc : e();
    }

    void update_acc(std::unique_ptr<Node> &node) {
        if (node) {
            node->acc = op(get_acc(node->lhs), op(node->value, get_acc(node->rhs)));
        }
    }

    S eval(const std::unique_ptr<Node> &node) {
        return node->lazy == id() ? node->value : mapping(node->lazy, node->value);
    }

    void propagate(std::unique_ptr<Node> &node) {
        if (node) {
            if (node->rev) {
                node->rev = 0;
                node->lhs.swap(node->rhs);
                if (node->lhs) node->lhs->rev ^= 1;
                if (node->rhs) node->rhs->rev ^= 1;
            }
            if (node->lazy == id()) return;
            if (node->lhs) {
                node->lhs->lazy = composition(node->lhs->lazy, node->lazy);
                node->lhs->acc = mapping(node->lazy, node->lhs->acc);
            }
            if (node->rhs) {
                node->rhs->lazy = composition(node->rhs->lazy, node->lazy);
                node->rhs->acc = mapping(node->lazy, node->rhs->acc);
            }
            node->value = eval(node);
            node->lazy = id();
        }
        recalc(node);
    }

    void recalc(std::unique_ptr<Node> &node) {
        update_cnt(node);
        update_acc(node);
    }

    // split node[0, n) into node[0, key), node[key, n)
    void split(std::unique_ptr<Node> node, int key, std::unique_ptr<Node> &lhs, std::unique_ptr<Node> &rhs) {
        if (!node) {
            lhs.reset(nullptr);
            rhs.reset(nullptr);
            return;
        }
        propagate(node);
        int implicit_key = get_cnt(node->lhs);
        if (key < implicit_key + 1) {
            split(std::move(node->lhs), key, lhs, node->lhs);
            rhs = std::move(node);
        } else {
            split(std::move(node->rhs), key - implicit_key - 1, node->rhs, rhs);
            lhs = std::move(node);
        }
        recalc(lhs);
        recalc(rhs);
        return;
    }

    // node = merge(lhs, rhs)
    void merge(std::unique_ptr<Node> &node, std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs) {
        propagate(lhs);
        propagate(rhs);
        if (lhs && rhs) {
            if (lhs->priority > rhs->priority) {
                merge(lhs->rhs, std::move(lhs->rhs), std::move(rhs));
                node = std::move(lhs);
            } else {
                merge(rhs->lhs, std::move(lhs), std::move(rhs->lhs));
                node = std::move(rhs);
            }
        } else if (lhs) {
            node = std::move(lhs);
        } else if (rhs) {
            node = std::move(rhs);
        } else {
            node = nullptr;
        }
        recalc(node);
        return;
    }

    //    a[l], ..., a[m], ..., a[r-1]
    // -> a[m], ..., a[r-1], a[l], ... 
    void rotate(std::unique_ptr<Node> &node, int l, int m, int r) {
        std::unique_ptr<Node> node1 = nullptr, node2 = nullptr, node3 = nullptr, node4 = nullptr;
        split(std::move(node), l, node1, node2);
        split(std::move(node2), r - l, node2, node3);
        split(std::move(node2), m - l, node2, node4);
        merge(node, std::move(node4), std::move(node2));
        merge(node, std::move(node), std::move(node3));
        merge(node, std::move(node1), std::move(node));
        return;
    }

    //    a[l], ..., a[r-1]
    // -> a[r-1], ..., a[l]
    void reverse(std::unique_ptr<Node> &node, int l, int r) {
        std::unique_ptr<Node> node1 = nullptr, node2 = nullptr, node3 = nullptr;
        split(std::move(node), l, node1, node2);
        split(std::move(node2), r - l, node2, node3);

        node2->rev ^= 1;

        merge(node, std::move(node1), std::move(node2));
        merge(node, std::move(node), std::move(node3));
        return;
    }

    // insert item to index key
    void insert(std::unique_ptr<Node> &node, int key, std::unique_ptr<Node> item) {
        std::unique_ptr<Node> node1 = nullptr, node2 = nullptr;
        split(std::move(node), key, node1, node2);
        merge(node, std::move(node1), std::move(item));
        merge(node, std::move(node), std::move(node2));
        return;
    }    

    // erase node[key]
    void erase(std::unique_ptr<Node> &node, int key) {
        std::unique_ptr<Node> node1 = nullptr, node2 = nullptr, node3 = nullptr;
        split(std::move(node), key + 1, node1, node2);
        split(std::move(node1), key, node1, node3);
        merge(node, std::move(node1), std::move(node2));
        return;
    }

    // i \in [l, r) node[i] = mapping(f, node[i])
    void apply(std::unique_ptr<Node> &node, int l, int r, F f) {
        std::unique_ptr<Node> node1 = nullptr, node2 = nullptr, node3 = nullptr;
        split(std::move(node), l, node1, node2);
        split(std::move(node2), r - l, node2, node3);

        node2->lazy = composition(node2->lazy, f);
        node2->acc = mapping(f, node2->acc);

        merge(node, std::move(node1), std::move(node2));
        merge(node, std::move(node), std::move(node3));
        return;
    }

    // op(a[l], a[l+1], ... , a[r-1])
    S query(std::unique_ptr<Node> &node, int l, int r) {
        std::unique_ptr<Node> node1 = nullptr, node2 = nullptr, node3 = nullptr;
        split(std::move(node), l, node1, node2);
        split(std::move(node2), r - l, node2, node3);

        S res = node2->acc; 

        merge(node, std::move(node1), std::move(node2));
        merge(node, std::move(node), std::move(node3));
        return res;
    }

    // node[key] = value
    void set(std::unique_ptr<Node> &node, int key, S value) {
        std::unique_ptr<Node> node1 = nullptr, node2 = nullptr, node3 = nullptr;
        split(std::move(node), key + 1, node1, node2);
        split(std::move(node1), key, node1, node3);

        node3->value = value;

        merge(node, std::move(node1), std::move(node3));
        merge(node, std::move(node), std::move(node2));
        return;
    }

    void dump(std::unique_ptr<Node> &node) {
        if (!node) {
            return;
        }
        propagate(node);
        dump(node->lhs);
        std::cerr << node->value << " ";
        dump(node->rhs);
        return;
    }

public:
    LazyImplicitTreap(int n=0): LazyImplicitTreap(std::vector<S>(n, e())) {}
    LazyImplicitTreap(const std::vector<S> &v):root(nullptr), rnd(seed_gen()) {
        std::for_each(v.rbegin(), v.rend(), [&](S x){
            insert(0, x);
        });
    }

    
    // insert value to index key
    void insert(int key, S value) {
        assert(key <= size());
        std::unique_ptr<Node> item = std::make_unique<Node>(value, value, id(), rnd());
        insert(root, key, std::move(item));
    }

    // erase a[key]
    void erase(int key) {
        assert(key < size());
        erase(root, key);
    }

    //    a[l], ..., a[m], ..., a[r-1]
    // -> a[m], ..., a[r-1], a[l], ... 
    void rotate(int l, int m, int r) {
        assert(0 <= l && l <= m && m < r && r <= size());
        rotate(root, l, m, r);
    }

    //    a[l], ..., a[r-1]
    // -> a[r-1], ..., a[l]
    void reverse(int l, int r) {
        assert(0 <= l && l < r && r <= size());
        reverse(root, l, r);
    }

    // i \in [l, r) a[i] = mapping(f, a[i])
    void apply(int l, int r, F f) {
        assert(0 <= l && l < r && r <= size());
        apply(root, l, r, f);
    }

    // op(a[l], a[l+1], ..., a[r-1])
    S query(int l, int r) {
        assert(0 <= l && l < r && r <= size());
        return query(root, l, r);
    }

    // a[key]
    S get(int key) {
        assert(key < size());
        return query(root, key, key + 1);
    }

    // a[key] = value
    void set(int key, S value) {
        assert(key < size());
        set(root, key, value);
    }

    int size(void) {
        return get_cnt(root);
    }

    void dump(void) {
        dump(root);
        std::cerr << std::endl;
    }

};

