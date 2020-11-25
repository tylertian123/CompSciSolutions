from collections import deque
import sys
_all_input = sys.stdin.read()
_line = -1
def input():
    global _line
    _line += 1
    return _all_input[_line]

n, l, s = input().split()
n = int(n)
l = int(l)
s = int(s)

levels = deque()
for _ in range(n):
    a, b, s = input().split()
    a = int(a)
    b = int(b)
    s = int(s)
