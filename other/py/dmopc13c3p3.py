"""
Python solution for DMOPC '13 Contest 3 Problem 3 - Crossing Field

Submit with PyPy 3 to avoid TLE.
"""
import sys
_lines = sys.stdin.read().split("\n")
_line = -1
def input():
    global _line
    _line += 1
    return _lines[_line]

n, h = input().split()
n = int(n)
h = int(h)

grid = [[int(i) for i in input().split()] for _ in range(n)]
target = (n - 1, n - 1)

from queue import Queue
q = Queue()
v = set([(0, 0)])
q.put((0, 0))

yes = False

while not q.empty():
    s = q.get()
    if s == target:
        yes = True
        break
    e = grid[s[0]][s[1]]

    l = (s[0] - 1, s[1])
    r = (s[0] + 1, s[1])
    u = (s[0], s[1] - 1)
    d = (s[0], s[1] + 1)

    if s[0] > 0 and l not in v and abs(grid[s[0] - 1][s[1]] - e) <= h:
        v.add(l)
        q.put(l)
    if s[0] < n - 1 and r not in v and abs(grid[s[0] + 1][s[1]] - e) <= h:
        v.add(r)
        q.put(r)
    if s[1] > 0 and u not in v and abs(grid[s[0]][s[1] - 1] - e) <= h:
        v.add(u)
        q.put(u)
    if s[1] < n - 1 and d not in v and abs(grid[s[0]][s[1] + 1] - e) <= h:
        v.add(d)
        q.put(d)

print("yes" if yes else "no")
