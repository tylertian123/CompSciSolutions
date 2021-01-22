#include <iostream>
#include <vector>
#include <cstddef>

using std::size_t;

void ds_make_sets(std::vector<int> &sets, std::vector<int> &ranks, int n) {
    sets.resize(n);
    ranks.resize(n, 0);
    for (size_t i = 0; i < sets.size(); i ++) {
        sets[i] = i;
    }
}

int ds_find(std::vector<int> &sets, std::vector<int> &ranks, int x) {
    if (sets[x] != x) {
        sets[x] = ds_find(sets, ranks, sets[x]);
    }
    return sets[x];
}

void ds_union(std::vector<int> &sets, std::vector<int> &ranks, int x, int y) {
    x = ds_find(sets, ranks, x);
    y = ds_find(sets, ranks, y);
    if (x == y) {
        return;
    }
    
    if (ranks[x] > ranks[y]) {
        sets[y] = x;
    }
    else {
        sets[x] = y;
        if (ranks[x] == ranks[y]) {
            ranks[y] ++;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q, x, y;
    char o;
    std::cin >> n >> q;

    std::vector<int> sets, ranks;
    ds_make_sets(sets, ranks, n);

    for (int i = 0; i < q; i ++) {
        std::cin >> o >> x >> y;
        if (o == 'A') {
            ds_union(sets, ranks, x - 1, y - 1);
        }
        else {
            std::cout << (ds_find(sets, ranks, x - 1) == ds_find(sets, ranks, y - 1) ? "Y\n" : "N\n");
        }
    }
}
