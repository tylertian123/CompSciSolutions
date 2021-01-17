from sys import stdin
input = stdin.readline

inf = 1000000000

n = int(input())
t = int(input())
g = [[0] * n for _ in range(n)]
p = [inf] * n
for _ in range(t):
    x, y, c = input().split(" ")
    x = int(x) - 1
    y = int(y) - 1
    c = int(c)
    g[x][y] = c
    g[y][x] = c
k = int(input())
for _ in range(k):
    z, pz = input().split(" ")
    p[int(z) - 1] = int(pz)
d = int(input()) - 1

import heapq as hq
mc = inf
heap = []
v = [False] * n
distance = [inf] * n
distance[d] = 0

hq.heappush(heap, (0, d))
while heap:
    shipping, city = hq.heappop(heap)
    if v[city]:
        continue
    if shipping > mc:
        break
    v[city] = True
    mc = min(shipping + p[city], mc)
    for x, c in enumerate(g[city]):
        if not c:
            continue
        if not v[x] and shipping + c < distance[x]:
            distance[x] = shipping + c
            hq.heappush(heap, (shipping + c, x))

print(mc)
