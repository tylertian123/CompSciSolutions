#include <iostream>
#include <unordered_map>
#include <stdint.h>

constexpr int RXN_LEN = 5;
const int rxns[RXN_LEN][4] = {
    {2, 1, 0, 2},
    {1, 1, 1, 1},
    {0, 0, 2, 1},
    {0, 3, 0, 0},
    {1, 0, 0, 1},
};

uint32_t state(int a, int b, int c, int d) {
    return (a << 24) | (b << 16) | (c << 8) | d;
}

std::unordered_map<uint32_t, bool> known;

bool can_win(int a, int b, int c, int d) {
    uint32_t s = state(a, b, c, d);
    auto res = known.find(s);
    if (res != known.end()) {
        return res->second;
    }
    for (int i = 0; i < RXN_LEN; i ++) {
        if (rxns[i][0] <= a && rxns[i][1] <= b && rxns[i][2] <= c && rxns[i][3] <= d) {
            if (!can_win(a - rxns[i][0], b - rxns[i][1], c - rxns[i][2], d - rxns[i][3])) {
                return known[s] = true;
            }
        }
    }
    return known[s] = false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, a, b, c, d;
    std::cin >> n;
    for (int i = 0; i < n; i ++) {
        std::cin >> a >> b >> c >> d;
        std::cout << (can_win(a, b, c, d) ? "Patrick\n" : "Roland\n");
    }
}
