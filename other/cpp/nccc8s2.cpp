#include <iostream>
#include <algorithm>
#include <numeric>

constexpr long long m = 1000000007;

long long freq[26];
char str[100001];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin.getline(str, 100001);

    std::fill(freq, freq + 26, 1);
    for (char *c = str; *c; c++) {
        freq[*c - 'a']++;
    }
    std::cout << std::reduce(freq, freq + 26, 1, [](auto a, auto b) { return a * b % m; }) << "\n";
}
