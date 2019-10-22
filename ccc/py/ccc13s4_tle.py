"""
Python solution for CCC '13 J4 - Who is Taller?

Note: The algorithm presented in this solution is correct, but this TLEs in the later test cases.
See the C++ implementation of this same algorithm for something that will pass the judge.
"""

from queue import Queue
n, m = input().split()
n = int(n)
m = int(m)

graph = [[] for i in range(n)]

for i in range(m):
    people = input().split()
    graph[int(people[0]) - 1].append(int(people[1]) - 1)

p, q = input().split()
p = int(p) - 1
q = int(q) - 1

def bfs(graph, start, end):
    visited = [False for i in range(len(graph))]
    queued = [False for i in range(len(graph))]
    q = Queue()
    q.put(start)

    while not q.empty():
        n = q.get()
        visited[n] = True

        if n == end:
            return True

        for child in graph[n]:
            if not visited[child] and not queued[child]:
                queued[child] = True
                q.put(child)
    return visited[end]

taller = bfs(graph, p, q)
shorter = bfs(graph, q, p)

print("yes" if taller else "no" if shorter else "unknown")
