n, m, a, b = [int(i) for i in input().split()]

a -= 1 # Adjust to use zero-based indexing internally
b -= 1

# Create adjacency list
adj = [[] for _ in range(n)]

# Read and fill in adjacency list
for i in range(m):
    x, y = input().split()
    x = int(x) - 1 # Adjust for zero-based indexing
    y = int(y) - 1
    adj[x].append(y)
    adj[y].append(x)

from queue import Queue
q = Queue()
q.put(a)
# Visited set
v = set([a])

found = False

while not q.empty():
    n = q.get()
    if n == b:
        found = True
        break

    for c in adj[n]:
        if c not in v:
            v.add(c)
            q.put(c)

print("GO SHAHIR!" if found else "NO SHAHIR!")
