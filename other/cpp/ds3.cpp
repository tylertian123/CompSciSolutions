#include <iostream>
#include <algorithm>

int arr[100000];

int gcd(int a, int b) {
    if (b > a) {
        std::swap(a, b);
    }
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

constexpr int INF = 1000000001;
struct segment {
    int m;
    int g;
    int q;
} tree[1 << 18];

segment combine(segment left, segment right) {
    segment result;
    result.g = gcd(left.g, right.g);
    result.m = std::min(left.m, right.m);
    result.q = 0;
    if (left.q == -1) {
        result.q = right.q;
        return result;
    }
    if (right.q == -1) {
        result.q = left.q;
        return result;
    }
    if (left.g == result.g) {
        result.q += left.q;
    }
    if (right.g == result.g) {
        result.q += right.q;
    }
    return result;
}

segment make_tree(int node, int begin, int end) {
    if (begin + 1 == end) {
        return tree[node] = {arr[begin], arr[begin], 1};
    }
    int mid = (begin + end) / 2;
    return tree[node] = combine(make_tree(node * 2, begin, mid), make_tree(node * 2 + 1, mid, end));
}

segment query(int node, int begin, int end, int l, int r) {
    // Entirely outside this segment
    if (r <= begin || l >= end) {
        return {INF, 0, -1};
    }
    // Entirely contained
    if (l <= begin && r >= end) {
        return tree[node];
    }
    int mid = (begin + end) / 2;
    return combine(query(node * 2, begin, mid, l, r), query(node * 2 + 1, mid, end, l, r));
}

// Update the value in the base array
segment update(int node, int begin, int end, int pos, int val) {
    if (pos < begin || pos >= end) {
        return tree[node];
    }
    if (begin + 1 == end) {
        return tree[node] = {val, val, 1};
    }
    int mid = (begin + end) / 2;
    return tree[node] = combine(update(node * 2, begin, mid, pos, val), update(node * 2 + 1, mid, end, pos, val));
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; i ++) {
        std::cin >> arr[i];
    }

    make_tree(1, 0, n);
    char op;
    int l, r;
    for (int i = 0; i < m; i ++) {
        std::cin >> op >> l >> r;
        switch (op) {
        case 'C':
            update(1, 0, n, l - 1, r);
            break;
        case 'M':
            std::cout << query(1, 0, n, l - 1, r).m << "\n";
            break;
        case 'G':
            std::cout << query(1, 0, n, l - 1, r).g << "\n";
            break;
        case 'Q':
            std::cout << query(1, 0, n, l - 1, r).q << "\n";
            break;
        }
    }
}
