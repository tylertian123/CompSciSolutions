import sys
_all_input = sys.stdin.read().split("\n")
_line = -1
def input():
    global _line
    _line += 1
    return _all_input[_line]

n, m = [int(i) for i in input().split(" ")]

ds = list(range(n))

def find(x):
    if ds[x] == x:
        return x
    root = x
    while ds[root] != root:
        root = ds[root]
    while ds[x] != root:
        ds[x], x = root, ds[x]
    return root

def union(x, y):
    ds[find(x)] = ds[find(y)]

edges = []
groups = n
for i in range(m):
    u, v = input().split(" ")
    u = int(u) - 1
    v = int(v) - 1
    if find(u) != find(v):
        edges.append(i + 1)
        union(u, v)
        groups -= 1
    if groups == 1:
        break

if groups == 1:
    print(*edges, sep="\n")
else:
    print("Disconnected Graph")
