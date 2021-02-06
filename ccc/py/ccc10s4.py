import sys
_all_data = sys.stdin.read().split('\n')
_line = -1
def _input():
    global _line
    _line += 1
    return _all_data[_line]
input = _input

edges = []
m = int(input())
edge_to_pen = {}
# Gross input format
for i in range(m):
    l = input().split(" ")
    e = int(l[0])
    for j in range(e):
        if j == e - 1:
            edge = (int(l[j + 1]), int(l[1]))
        else:
            edge = (int(l[j + 1]), int(l[j + 2]))
        # Ensure order
        if edge[0] > edge[1]:
            edge = (edge[1], edge[0])
        if edge in edge_to_pen:
            pen, cost = edge_to_pen.pop(edge)
            edges.append((cost, pen, i))
        else:
            edge_to_pen[edge] = (i, int(l[j + e + 1]))


def mst():
    # Apply Kruskal's algorithm
    ds = [i for i in range(m)]
    def find(x):
        if ds[x] != x:
            ds[x] = find(ds[x])
        return ds[x]
    def union(x, y):
        x = find(x)
        y = find(y)
        ds[x] = y
    edges.sort()
    total = 0
    n = m
    for w, a, b in edges:
        if find(a) != find(b):
            union(a, b)
            total += w
            n -= 1
    if n == 1:
        return total
    return 2 ** 32

a = mst()
# The "outside" pen, if this graph is disconnected
for pen, cost in edge_to_pen.values():
    edges.append((cost, pen, m))
m += 1
b = mst()
print(min(a, b))
