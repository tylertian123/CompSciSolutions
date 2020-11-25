#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>

int main() {
    unsigned int n, l, s;
    scanf("%d %d %d", &n, &l, &s);
    std::vector<std::pair<int, int>> levels;
    levels.push_back(std::make_pair(l, 0));

    for (int i = 0; i < n; i ++) {
        int a, b, s;
        scanf("%d %d %d", &a, &b, &s);
        --a;
        levels.push_back(std::make_pair(a, s));
        levels.push_back(std::make_pair(b, -s));
    }
    std::sort(levels.begin(), levels.end());

    int candy = 0, level = 0, house = 0;
    for (const auto &change : levels) {
        if (level < s) {
            candy += change.first - house;
        }
        level += change.second;
        house = change.first;
    }
    printf("%d\n", candy);
}
