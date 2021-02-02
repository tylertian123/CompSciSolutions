import sys
_all_data = sys.stdin.read().split('\n')
_line = -1
def _input():
    global _line
    _line += 1
    return _all_data[_line]
input = _input

n, m = input().split(" ")
n = int(n)
m = int(m)
graph = [[] for _ in range(n)]
for _ in range(m):
    a, b, t = input().split(" ")
    a = int(a)
    b = int(b)
    t = int(t)
    graph[a].append((b, t))
    graph[b].append((a, t))

import heapq as hq
from math import inf
import itertools
def dijkstra(start: int):
    min_cost = [inf] * n
    heap = []
    hq.heappush(heap, (0, start))
    min_cost[start] = 0
    while heap:
        cost, node = hq.heappop(heap)
        if cost > min_cost[node]:
            continue
        for child, w in graph[node]:
            if cost + w < min_cost[child]:
                min_cost[child] = cost + w
                hq.heappush(heap, (cost + w, child))
    return min_cost

print(max(i + j for i, j in itertools.islice(zip(dijkstra(0), dijkstra(n - 1)), 1, n - 1)))

