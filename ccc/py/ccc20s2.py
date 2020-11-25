from sys import stdin
_all_data = stdin.read().split("\n")
_line = -1
def input():
    global _line
    _line += 1
    return _all_data[_line]

m = int(input())
n = int(input())

cellmap = {}
for row in range(m):
    for col, num in enumerate(input().split()):
        num = int(num)
        if num in cellmap:
            cellmap[num].append(row << 16 | col)
        else:
            cellmap[num] = [row << 16 | col]

from collections import deque
from sys import exit
visited = set()
q = deque()

s = (m - 1) << 16 | (n - 1)
q.append(s)
visited.add(s)

while q:
    cell = q.pop()
    if cell == 0:
        print("yes")
        exit()
    prod = ((cell >> 16) + 1) * ((cell & 0xFFFF) + 1)
    for c in cellmap.get(prod, ()):
        if c not in visited:
            visited.add(c)
            q.append(c)

print("no")
