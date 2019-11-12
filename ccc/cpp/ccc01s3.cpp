#include <stdio.h>
#include <vector>
#include <queue>

std::vector<int> graph[26];

bool visit(int p0, int p1) {
    std::queue<int> q;
    q.push(0);
    bool visited[26] = { 0 };
    visited[0] = true;

    while(!q.empty()) {
        int n = q.front();
        q.pop();

        if(n == 1) {
            return true;
        }

        for(int i : graph[n]) {
            if(!(n == p0 && i == p1) && !(n == p1 && i == p0) && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    return false;
}

int main() {
    while(true) {
        char a, b;
        scanf(" %c %c", &a, &b);

        if(a == '*') {
            break;
        }

        graph[a - 'A'].push_back(b - 'A');
        graph[b - 'A'].push_back(a - 'A');
    }

    std::vector<int> road_a;
    std::vector<int> road_b;

    for(int a = 0; a < 26; a ++) {
        for(int b : graph[a]) {
            if(b > a) {
                if(!visit(a, b)) {
                    road_a.push_back(a);
                    road_b.push_back(b);
                }
            }
        }
    }

    for(int i = 0; i < road_a.size(); i ++) {
        printf("%c%c\n", road_a[i] + 'A', road_b[i] + 'A');
    }
    printf("There are %lu disconnecting roads.\n", road_a.size());
}
