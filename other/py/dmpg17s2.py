"""
Python solution for DMPG '17 S2 - Anime Conventions
"""

n, q = [int(i) for i in input().split()]

# Create our disjoint sets
# s[i] is the parent of i
# if s[i] == i, then i is the root of its own set
s = [i for i in range(n)]

# Disjoint sets find algorithm
# Return the root of the set containing x
def find(x):
    # Only check if x is not already the root
    if s[x] != x:
        # Path compression (flattening)
        # Set x's parent to the root of x's set
        # This speeds up future lookups
        s[x] = find(s[x])
    return s[x]

# Disjoint sets union algorithm
# Merges the sets of x and y
def union(x, y):
    # Find the root of the two sets
    x_root = find(x)
    y_root = find(y)
    # Check if the root is identical
    # If it is, they're already in the same set, so skip
    if x_root == y_root:
        return
    # Otherwise set y's root's parent to x's root
    s[y_root] = x_root

for i in range(q):
    op, x, y = input().split()
    x = int(x)
    y = int(y)
    if op == 'A':
        union(x - 1, y - 1)
    else:
        # Two cities are connected if they're in the same set
        # Two elements are in the same set if their roots are the same
        print("Y" if find(x - 1) == find(y - 1) else "N")
