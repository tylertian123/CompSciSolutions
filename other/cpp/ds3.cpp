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

constexpr int ARR_LEN = 1 << (17 + 1);
constexpr int INF = 1000000001;
int min_tree[ARR_LEN];
int gcd_tree[ARR_LEN];
int q_tree[ARR_LEN];

int combine_q_tree(int left, int right, int left_gcd, int right_gcd) {
    // Compare the GCDs of the children
    // If the two GCDs are equal, then the overall GCD remains the same
    // so sum the two values
    if (left_gcd == right_gcd) {
        return left + right;
    }
    // If the two GCDs aren't the same, compare the overall GCD to the two
    // If the answer is nonzero, then all values in the segment have values n * gcd
    // In other words no value is less than the segment's GCD
    // When combining two segments, the overall GCD can only go down
    // So if the new GCD goes below both old GCDs, the answer is 0.
    
    // If the new GCD is equal to the one from the left or right half then keep that value
    int new_gcd = gcd(left_gcd, right_gcd);
    if (new_gcd == left_gcd) {
        return left;
    }
    if (new_gcd == right_gcd) {
        return right;
    }
    return 0;
}

int make_min_tree(int node, int begin, int end) {
    if (begin + 1 == end) {
        return min_tree[node] = arr[begin];
    }
    int mid = (begin + end) / 2;
    return min_tree[node] = std::min(make_min_tree(node * 2, begin, mid), make_min_tree(node * 2 + 1, mid, end));
}

int make_gcd_tree(int node, int begin, int end) {
    if (begin + 1 == end) {
        return gcd_tree[node] = arr[begin];
    }
    int mid = (begin + end) / 2;
    return gcd_tree[node] = gcd(make_gcd_tree(node * 2, begin, mid), make_gcd_tree(node * 2 + 1, mid, end));
}

int make_q_tree(int node, int begin, int end) {
    if (begin + 1 == end) {
        return q_tree[node] = 1;
    }
    int mid = (begin + end) / 2;
    return q_tree[node] = combine_q_tree(make_q_tree(node * 2, begin, mid), make_q_tree(node * 2 + 1, mid, end), gcd_tree[node * 2], gcd_tree[node * 2 + 1]);
}

int query_min_tree(int node, int begin, int end, int l, int r) {
    // Entirely outside this segment
    if (r <= begin || l >= end) {
        return INF;
    }
    // Entirely contained
    if (l <= begin && r >= end) {
        return min_tree[node];
    }
    int mid = (begin + end) / 2;
    return std::min(query_min_tree(node * 2, begin, mid, l, r), query_min_tree(node * 2 + 1, mid, end, l, r));
}

int query_gcd_tree(int node, int begin, int end, int l, int r) {
    // Entirely outside this segment
    if (r <= begin || l >= end) {
        return 0;
    }
    // Entirely contained
    if (l <= begin && r >= end) {
        return gcd_tree[node];
    }
    int mid = (begin + end) / 2;
    return gcd(query_gcd_tree(node * 2, begin, mid, l, r), query_gcd_tree(node * 2 + 1, mid, end, l, r));
}

int query_q_tree(int node, int begin, int end, int l, int r, int &gcd_out) {
    // Entirely outside this segment
    if (r <= begin || l >= end) {
        return -1;
    }
    // Entirely contained
    if (l <= begin && r >= end) {
        gcd_out = gcd_tree[node];
        return q_tree[node];
    }
    int mid = (begin + end) / 2;
    int left_gcd, right_gcd;
    int left = query_q_tree(node * 2, begin, mid, l, r, left_gcd);
    int right = query_q_tree(node * 2 + 1, mid, end, l, r, right_gcd);
    if (left == -1) {
        gcd_out = right_gcd;
        return right;
    }
    if (right == -1) {
        gcd_out = left_gcd;
        return left;
    }
    gcd_out = gcd(left_gcd, right_gcd);
    return combine_q_tree(left, right, left_gcd, right_gcd);
}

int update_min_tree(int node, int begin, int end, int pos, int val) {
    if (pos < begin || pos >= end) {
        return min_tree[node];
    }
    if (begin + 1 == end) {
        return min_tree[node] = val;
    }
    int mid = (begin + end) / 2;
    return min_tree[node] = std::min(update_min_tree(node * 2, begin, mid, pos, val), update_min_tree(node * 2 + 1, mid, end, pos, val));
}

int update_gcd_tree(int node, int begin, int end, int pos, int val) {
    if (pos < begin || pos >= end) {
        return gcd_tree[node];
    }
    if (begin + 1 == end) {
        return gcd_tree[node] = val;
    }
    int mid = (begin + end) / 2;
    return gcd_tree[node] = gcd(update_gcd_tree(node * 2, begin, mid, pos, val), update_gcd_tree(node * 2 + 1, mid, end, pos, val));
}

int update_q_tree(int node, int begin, int end, int pos, int val) {
    if (pos < begin || pos >= end) {
        return q_tree[node];
    }
    if (begin + 1 == end) {
        return q_tree[node] = 1;
    }
    int mid = (begin + end) / 2;
    return q_tree[node] = combine_q_tree(update_q_tree(node * 2, begin, mid, pos, val), update_q_tree(node * 2 + 1, mid, end, pos, val), gcd_tree[node * 2], gcd_tree[node * 2 + 1]);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; i ++) {
        std::cin >> arr[i];
    }

    make_min_tree(1, 0, n);
    make_gcd_tree(1, 0, n);
    make_q_tree(1, 0, n);
    char op;
    int l, r;
    for (int i = 0; i < m; i ++) {
        std::cin >> op >> l >> r;
        switch (op) {
        case 'C':
            update_min_tree(1, 0, n, l - 1, r);
            update_gcd_tree(1, 0, n, l - 1, r);
            update_q_tree(1, 0, n, l - 1, r);
            break;
        case 'M':
            std::cout << query_min_tree(1, 0, n, l - 1, r) << "\n";
            break;
        case 'G':
            std::cout << query_gcd_tree(1, 0, n, l - 1, r) << "\n";
            break;
        case 'Q':
            // Last parm used as dummy
            std::cout << query_q_tree(1, 0, n, l - 1, r, l) << "\n";
            break;
        }
    }
}
