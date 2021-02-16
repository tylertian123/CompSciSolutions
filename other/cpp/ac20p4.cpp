#include <iostream>
#include <utility>
#include <algorithm>
#include <string.h>

bool graph[3000][3000];
std::pair<int, int> edges[3000];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < m; i ++) {
        std::cin >> edges[i].first >> edges[i].second;
        edges[i].first --;
        edges[i].second --;
        graph[edges[i].first][edges[i].second] = true;
        graph[edges[i].second][edges[i].first] = true;
    }

    // Find cycles of length 3
    int best[4] = {3001, 3001, 3001, 3001};
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            if (i == edges[j].first || i == edges[j].second) {
                continue;
            }
            if (graph[i][edges[j].first] && graph[i][edges[j].second]) {
                int current[3] = {i, edges[j].first, edges[j].second};
                std::sort(current, current + 3);
                if (std::lexicographical_compare(current, current + 3, best, best + 3)) {
                    memcpy(best, current, sizeof(current));
                }
            }
        }
    }
    if (best[0] != 3001) {
        std::cout << 3 << "\n" << best[0] + 1 << " " << best[1] + 1 << " " << best[2] + 1 << "\n";
        return 0;
    }

    for (int i = 0; i < m; i ++) {
        for (int j = 0; j < m; j ++) {
            if (i == j) {
                continue;
            }
            if (edges[i].first != edges[j].first && edges[i].first != edges[j].second && edges[i].second != edges[j].first && edges[i].second != edges[j].second) {
                int current[4] = {edges[i].first, edges[i].second, edges[j].first, edges[j].second};
                std::sort(current, current + 4);
                if (std::lexicographical_compare(current, current + 4, best, best + 4)) {
                    memcpy(best, current, sizeof(current));
                }
            }
        }
    }
    if (best[0] != 3001) {
        std::cout << 4 << "\n" << best[0] + 1 << " " << best[1] + 1 << " " << best[2] + 1 << " " << best[3] + 1 << "\n";
        return 0;
    }
    std::cout << -1 << "\n";
}
