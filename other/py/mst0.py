"""
Minimum-Spanning Tree problem with Prim's algorithm.

PROBLEM STATEMENT
Given n points on a plane, connect them with segments of minimum total length such that there is a
path between any two points.

INPUT FORMAT
The first line contains the number n of points. Each of the following n lines defines a point (xi, yi).

CONSTRAINTS
1 <= n <= 200; −10^3 <= xi, yi <= 10^3 are integers. All points are pairwise different, no three
points lie on the same line.

OUTPUT FORMAT
Output the minimum total length of segments. The absolute value of the difference
between the answer of your program and the optimal value should be at most 10^−6. To ensure this, 
output your answer with at least seven digits after the decimal point (otherwise your answer, while
being computed correctly, can turn out to be wrong because of rounding issues).

SAMPLE 1.
Input:
    4
    0 0
    0 1
    1 0
    1 1
Output:
    3.000000000

SAMPLE 2.
Input:
    5
    0 0
    0 2
    1 1
    3 0
    3 2
Output:
    7.064495102
"""

from math import sqrt, inf

def dist(a, b):
    return sqrt((a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2)

points = [tuple(int(i) for i in input().split()) for _ in range(int(input()))]

# Total edge weight
w = 0
# Dict of points -> min distance to the point
dists = {}
# Add all points except for one into the queue
ipts = iter(points)
pt = next(ipts) # skip first entry
for p in ipts:
    dists[p] = dist(p, pt)
# Prim's algorithm
while dists:
    # Find point with minimum distance
    d = inf
    p = None
    for k, v in dists.items():
        if v < d:
            d = v
            p = k
    dists.pop(p)
    w += d
    # Update distances
    for k in dists.keys():
        d = dist(p, k)
        if d < dists[k]:
            dists[k] = d
# Format to 9 decimal places
print(f"{w:.9f}")
