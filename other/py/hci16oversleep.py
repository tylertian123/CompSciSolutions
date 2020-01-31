"""
Python solution for Oversleep (https://dmoj.ca/problem/hci16oversleep)
"""

from sys import stdin
_all_input = stdin.read().split("\n")
_line = -1
def input():
    global _line
    _line += 1
    return _all_input[_line]

n, m = [int(i) for i in input().split()]

grid = [input() for i in range(n)]

start = None
for i, row in enumerate(grid):
    if "s" in row:
        start = (i, row.index("s"))

from queue import Queue
q = Queue()
q.put((start, 0))
v = set()
v.add(start)

total = 0

while not q.empty():
    pos, time = q.get()
    
    if grid[pos[0]][pos[1]] == 'e':
        total = time
        break
    
    for row, col in ((-1, 0), (1, 0), (0, -1), (0, 1)):
        row += pos[0]
        col += pos[1]
        t = (row, col)
        if row >= 0 and row < n and col >= 0 and col < m and grid[row][col] != 'X' and t not in v:
            v.add(t)
            q.put((t, time + 1))

# Subtract 1 since going from the last path square to the destination doesn't count
print(total - 1)
