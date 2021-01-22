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

    int n, m, u, v;
    std::cin >> n >> m;
    std::vector<int> edges;

    std::vector<int> sets, ranks;
    ds_make_sets(sets, ranks, n);

    for (int i = 0; i < m; i ++) {
        std::cin >> u >> v;
        u --;
        v --;
        if (ds_find(sets, ranks, u) != ds_find(sets, ranks, v)) {
            ds_union(sets, ranks, u, v);
            edges.push_back(i + 1);
            if (--n == 1) {
                break;
            }
        }
    }
    
    if (n != 1) {
        std::cout << "Disconnected Graph\n";
    }
    else {
        for (int i : edges) {
            std::cout << i << "\n";
        }
    }
}
