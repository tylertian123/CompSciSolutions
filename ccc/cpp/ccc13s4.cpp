#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>

std::vector<std::vector<int>> graph;

bool bfs(int start, int end) {
    bool *visited = new bool[graph.size()]();
    bool *queued = new bool[graph.size()]();
    std::queue<int> q;
    q.push(start);

    while(!q.empty()) {
        auto n = q.front();
        q.pop();
        visited[n] = true;

        if(n == end) {
            delete[] visited;
            delete[] queued;
            return true;
        }

        for(const int &child : graph[n]) {
            if(!visited[child] && !queued[child]) {
                queued[child] = true;
                q.push(child);
            }
        }
    }
    delete[] visited;
    delete[] queued;
    return false;
}

int main() {
    int n, m;
    std::scanf("%d%d", &n, &m);

    graph.resize(n);

    for(int i = 0; i < m; i ++) {
        int a, b;
        std::scanf("%d%d", &a, &b);

        graph[a - 1].push_back(b - 1);
    }

    int p, q;
    std::scanf("%d%d", &p, &q);
    p -= 1;
    q -= 1;

    bool taller = bfs(p, q);
    bool shorter = bfs(q, p);
    if(taller) {
        std::printf("yes\n");
    }
    else if(shorter) {
        std::printf("no\n");
    }
    else {
        std::printf("unknown\n");
    }
}
