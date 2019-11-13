import sys
_all_data = sys.stdin.read().split('\n')
_line = -1
def _input():
    global _line
    _line += 1
    return _all_data[_line]
input = _input

from queue import Queue

f = int(input())
r = int(input())
c = int(input())

plan = [input() for i in range(r)]
visited = [[False for i in range(c)] for i in range(r)]

rooms = []

def fill_room(row, col):
    size = 0
    q = Queue()
    q.put((row, col))
    visited[row][col] = True
    
    while not q.empty():
        n = q.get()
        size += 1
        for p in [(n[0] - 1, n[1]), (n[0] + 1, n[1]), (n[0], n[1] - 1), (n[0], n[1] + 1)]:
            if p[0] >= 0 and p[0] < r and p[1] >= 0 and p[1] < c and not visited[p[0]][p[1]] and plan[p[0]][p[1]] == '.':
                q.put(p)
                visited[p[0]][p[1]] = True
    return size

for i in range(0, r):
    for j in range(0, c):
        if not visited[i][j] and plan[i][j] == '.':
            rooms.append(fill_room(i, j))
rooms.sort(reverse = True)
t = 0
for size in rooms:
    if f >= size:
        f -= size
        t += 1
    else:
        break

print(t, "rooms," if t != 1 else "room,", f, "square metre(s) left over")
