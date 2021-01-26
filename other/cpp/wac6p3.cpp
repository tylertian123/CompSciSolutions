#include <iostream>
#include <algorithm>

using ull = unsigned long long;

int len;
ull original[200000];
ull sorted[200000];

bool try_k(ull k) {
    int i = 0, j = 0;
    while (i < len) {
        // Find the end of the current group
        for (j = i + 1; j < len && sorted[j] - sorted[j - 1] <= k; j ++);
        // Check that all elements in the original array are a part of this group
        for (; i < j; i ++) {
            if (original[i] > sorted[j - 1]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> len;
    for (int i = 0; i < len; i ++) {
        std::cin >> original[i];
        sorted[i] = original[i];
    }
    std::sort(sorted, sorted + len);

    // Binary search over k
    ull start = 0, end = sorted[len - 1];
    ull result = end;
    while (start < end) {
        ull mid = (start + end) / 2;
        if (try_k(mid)) {
            result = mid;
            end = mid;
        }
        else {
            start = mid + 1;
        }
    }
    std::cout << result << "\n";
}
