#include <stdio.h>
#include <queue>

using namespace std;

struct Pos {
    int x;
    int y;
    long d;
    long l;
    long r;
};

int main() {
    int size;
    scanf("%d\n", &size);

    bool **grid = new bool*[size];
    bool **visited = new bool*[size];
    for(int i = 0; i < size; i ++) {
        grid[i] = new bool[size];
        visited[i] = new bool[size];

        for(int j = 0; j < size; j ++) {
            char k;
            scanf(" %c", &k);
            grid[i][j] = k == '.';
            visited[i][j] = false;
        }
    }

    queue<Pos> next_pos;
    next_pos.push({0, 0, 0, 0, 0});

    Pos result = {0, 0, 0, 0, 0};
    bool found = false;

    while(!next_pos.empty()) {
        Pos &pos = next_pos.front();
        if(pos.x == size - 1 && pos.y == size - 1) {
            result = pos;
            found = true;
            break;
        }

        if(pos.y + 1 < size && !visited[pos.y + 1][pos.x] && grid[pos.y + 1][pos.x]) {
            visited[pos.y + 1][pos.x] = true;
            next_pos.push({pos.x, pos.y + 1, pos.d + 1, pos.l, pos.r});
        }
        if(pos.x - 1 >= 0 && !visited[pos.y][pos.x - 1] && grid[pos.y][pos.x - 1]) {
            visited[pos.y][pos.x - 1] = true;
            next_pos.push({pos.x - 1, pos.y, pos.d, pos.l + 1, pos.r});
        }
        if(pos.x + 1 < size && !visited[pos.y][pos.x + 1] && grid[pos.y][pos.x + 1]) {
            visited[pos.y][pos.x + 1] = true;
            next_pos.push({pos.x + 1, pos.y, pos.d, pos.l, pos.r + 1});
        }
        next_pos.pop();
    }

    printf("%ld\n", found ? result.d * result.d + result.l * result.l + result.r * result.r : -1);
}
