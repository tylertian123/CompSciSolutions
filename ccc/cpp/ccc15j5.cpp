/*
 * C++ solution for CCC '15 J5 - Pi-day
 */
#include <unordered_map>
#include <stdio.h>
#include <stdint.h>

std::unordered_map<uint32_t, int> known;

/**
 * n - Number of pieces left
 * k - Number of people left
 * m - Min number of pieces to give out
 */
int pie(int n, int k, int m) {
    // Check if distribution is at all possible
    if (n / k < m) {
        return 0;
    }
    // Base cases, as mentioned in the question description
    if (k == 1 || k == n) {
        return 1;
    }
    uint32_t key = n << 16 | k << 8 | m;
    auto it = known.find(key);
    if (it != known.end()) {
        return it->second;
    }
    // Try every possible number of pieces to give out
    int sum = 0;
    for (int p = m; p < n + 1; p ++) {
        // Give out p pieces
        // (n - p) pieces still left, (k - 1) people still left, and a min of p must be given to the next person
        int ways = pie(n - p, k - 1, p);
        // If distribution is no longer possible, we gave out too many pieces
        // Skip trying the rest
        if (!ways) {
            break;
        }
        sum += ways;
    }
    known.insert(std::make_pair(key, sum));
    return sum;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d\n", pie(n, k, 1));
}
