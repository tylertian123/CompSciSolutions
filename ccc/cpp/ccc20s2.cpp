#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <stdint.h>

#define POS(row, col) (((row) << 16) | (col))
#define ROW(pos) ((pos) >> 16)
#define COL(pos) ((pos) & 0x0000FFFF)

typedef uint32_t position;

std::vector<position> cellmap[1000001];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int m, n;
    std::cin >> m >> n;
    for (int row = 0; row < m; row ++) {
        for (int col = 0; col < n; col ++) {
            int num;
            std::cin >> num;
            cellmap[num].push_back(POS(row, col));
        }
    }
    std::unordered_set<position> visited(1000);
    std::stack<position> stack;
    visited.insert(POS(m - 1, n - 1));
    stack.push(POS(m - 1, n - 1));

    while (!stack.empty()) {
        auto cell = stack.top();
        stack.pop();
        if (cell == POS(0, 0)) {
            std::cout << "yes" << std::endl;
            return 0;
        }
        int prod = (ROW(cell) + 1) * (COL(cell) + 1);
        for (auto &c : cellmap[prod]) {
            if (!visited.count(c)) {
                visited.insert(c);
                stack.push(c);
            }
        }
    }
    std::cout << "no" << std::endl;
}
