#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(NULL);
    int startX, startY, endX, endY, t;
    std::cin >> startX >> startY >> endX >> endY >> t;

    int total = std::abs(startX - endX) + std::abs(startY - endY);
    std::cout << (t >= total && (t - total) % 2 == 0 ? "Y" : "N") << std::endl;
}
