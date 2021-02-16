#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <string.h>

struct trip {
    int a;
    int b;
    int k;
} trips[100000];
std::vector<int> graph[100000];
std::pair<int, int> roads[100000];
int pop[100000];
std::vector<int> destroy[100000];

bool destroyed[100000];
int results[100000];

int depth[100000];
int parent[100000];
std::vector<int> parent_table[100000];
std::vector<int> pop_table[1000000];

int ds[100000];

void ds_init(int n) {
    for (int i = 0; i < n; i ++) {
        ds[i] = i;
    }
}

int ds_find(int a) {
    if (ds[a] != a) {
        ds[a] = ds_find(ds[a]);
    }
    return ds[a];
}

void ds_union(int a, int b) {
    a = ds_find(a);
    b = ds_find(b);
    ds[a] = b;
}

void make_tables(int root = 0) {
    std::queue<int> next;
    next.push(root);
    parent[root] = -1;
    depth[root] = 0;    
    while (!next.empty()) {
        int node = next.front();
        next.pop();
        // Iterate all connected nodes
        for (int child : graph[node]) {
            // Skip the one we came from
            if (child == parent[node]) {
                continue;
            }
            next.push(child);
            parent[child] = node;
            depth[child] = depth[node] + 1;

            // Initialize sparse table entry
            int d = depth[child];
            int log2 = 0;
            for (; (d >>= 1) != 0; log2 ++);
            parent_table[child].resize(log2 + 1);
            pop_table[child].resize(log2 + 1);
            // First parent
            parent_table[child][0] = node;
            // Max of populations of 1 parent
            pop_table[child][0] = pop[node];
            // Fill in the rest of the table
            for (int i = 0; i < log2; i ++) {
                int iparent = parent_table[child][i];
                // Find parent at 2x depth
                parent_table[child][i + 1] = parent_table[iparent][i];
                // Max of 2x depth
                pop_table[child][i + 1] = std::max(pop_table[child][i], pop_table[iparent][i]);
            }
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        std::swap(a, b);
    }
    if (depth[a] != depth[b]) {
        // Get a and b to the same depth
        // Iterate powers of 2 from biggest
        for (int i = parent_table[a].size() - 1; i >= 0; i --) {
            if (i >= parent_table[a].size()) {
                continue;
            }
            if (depth[parent_table[a][i]] >= depth[b]) {
                a = parent_table[a][i];
            }
        }
    }
    if (a == b) {
        return a;
    }
    // Move both nodes up at the same time
    for (int i = parent_table[a].size() - 1; i >= 0; i --) {
        if (i >= parent_table[a].size()) {
            continue;
        }
        if (parent_table[a][i] != parent_table[b][i]) {
            a = parent_table[a][i];
            b = parent_table[b][i];
        }
    }
    return parent[a];
}

int search_power_of_two(int, int, int, int*, int*, int);

int solve(int a, int b, int k) {
    if (pop[a] >= k) {
        return a;
    }
    int l = lca(a, b);
    // Search from a to lca
    // Should stop just before the solution if one exists
    for (int i = parent_table[a].size() - 1; i >= 0; i --) {
        // Check for valid index and if it goes past the lca
        if (i >= parent_table[a].size() || depth[parent_table[a][i]] <= depth[l]) {
            continue;
        }
        // Past the solution
        if (pop_table[a][i] >= k) {
            continue;
        }
        a = parent_table[a][i];
    }
    // Some edge cases
    if (l != a && pop[parent[a]] >= k) {
        return parent[a];
    }
    if (pop[l] >= k) {
        return l;
    }
    // Binary search powers of 2
    int power = parent_table[b].size();
    int ans = -1;
    while (b != l) {
        int newans = search_power_of_two(b, l, k, &b, &power, power - 1);
        if (newans != -1) {
            ans = newans;
        }
    }
    return ans;
}

// Searches the longest path with a power of 2
// Sets end to past the end of the range searched
// Sets power to the largest power of 2 checked
int search_power_of_two(int b, int l, int k, int *end, int *power, int i) {
    bool set_return = false;
    for (; i >= 0; i --) {
        if (i >= parent_table[b].size() || depth[parent_table[b][i]] <= depth[l]) {
            continue;
        }
        if (!set_return) {
            set_return = true;
            *power = i;
            *end = parent[parent_table[b][i]];
        }
        // Solution exists somewhere in this power of 2
        if (pop_table[b][i] >= k) {
            if (i == 0) {
                return parent[b];
            }
            else {
                // Move to the top half if solution is in it
                if (pop_table[parent_table[b][i - 1]][i - 1] >= k) {
                    b = parent_table[b][i - 1];
                }
                // Otherwise we can do nothing and just let i decrease
            }
        }
    }
    if (!set_return) {
        *end = parent[b];
    }
    if (pop[b] >= k) {
        return b;
    }
    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q, r;
    std::cin >> n >> q >> r;
    for (int i = 0; i < n; i ++) {
        std::cin >> pop[i];
    }
    for (int i = 0; i < n - 1; i ++) {
        std::cin >> roads[i].first >> roads[i].second;
        roads[i].first --;
        roads[i].second --;
        graph[roads[i].first].push_back(roads[i].second);
        graph[roads[i].second].push_back(roads[i].first);
    }
    for (int i = 0; i < r; i ++) {
        int x, y;
        std::cin >> x >> y;
        x --;
        y --;
        destroy[x].push_back(y);
        destroyed[y] = true;
    }
    for (int i = 0; i < q; i ++) {
        std::cin >> trips[i].a >> trips[i].b >> trips[i].k;
        trips[i].a --;
        trips[i].b --;
    }

    // Initialization
    ds_init(n);
    for (int i = 0; i < n - 1; i ++) {
        if (!destroyed[i]) {
            ds_union(roads[i].first, roads[i].second);
        }
    }
    make_tables();

    // Solve in reverse
    for (int i = q - 1; i >= 0; i --) {
        for (int road : destroy[i]) {
            ds_union(roads[road].first, roads[road].second);
        }
        if (ds_find(trips[i].a) != ds_find(trips[i].b)) {
            results[i] = -1;
        }
        else {
            int solution = solve(trips[i].a, trips[i].b, trips[i].k);
            results[i] = solution == -1 ? -1 : solution + 1;
        }
    }
    for (int i = 0; i < q; i ++) {
        std::cout << results[i] << "\n";
    }
}
