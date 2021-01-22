"""
Minimum-Spanning Tree problem with Kruskal's algorithm and Clustering.

PROBLEM STATEMENT
Given n points on a plane and an integer k, compute the largest possible value of d such that the
given points can be partitioned into k non-empty subsets in such a way that the distance between any
two points from different subsets is at least d.

INPUT FORMAT
The first line contains the number n of points. Each of the following n lines defines a point (xi, yi).
The last line contains the number k of clusters.

CONSTRAINTS
2 <= k <= n <= 200; −10^3 <= xi, yi <= 10^3 are integers. All points are pairwise different.

OUTPUT FORMAT
Output the largest value of d. The absolute value of the difference between the answer of your program
and the optimal value should be at most 10^−6. To ensure this, output your answer with at least seven
digits after the decimal point (otherwise your answer, while being computed correctly, can turn out to
be wrong because of rounding issues).

SAMPLE 1.
Input:
    8
    3 1
    1 2
    4 6
    9 8
    9 9
    8 9
    3 11
    4 12
    4
Output:
    5.000000000

SAMPLE 2.
Input:
    12
    7 6
    4 3
    5 1
    1 7
    2 7
    5 7
    3 3
    7 8
    2 8
    4 4
    6 7
    2 6
    3
Output:
    2.828427124746
"""

from math import sqrt

def dist(a, b):
    return sqrt((a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2)

points = [[int(i) for i in input().split()] for _ in range(int(input()))]
k = int(input())

from typing import List

# Disjoint sets algorithm
# See https://en.wikipedia.org/wiki/Disjoint-set_data_structure
def ds_make(n: int) -> List[int]:
    """
    Make n subsets containing the numbers 0 to n - 1.
    """
    # The value of element i is the parent of that set
    # If parent is itself then it's the root
    return [i for i in range(n)]

def ds_find(s: List[int], x: int) -> int:
    """
    Find the subset containing x in s.
    """
    if s[x] != x:
        # Apply path compression
        s[x] = ds_find(s, s[x])
    return s[x]

def ds_union(s: List[int], x: int, y: int) -> None:
    """
    Merge the two subsets x and y in s.
    """
    xr = ds_find(s, x)
    yr = ds_find(s, y)
    s[yr] = xr

# Use Kruskal's algorithm
from itertools import combinations
# Disjoint sets data structure keeping track of trees
s = ds_make(len(points))
# Number of groups
g = len(points)
# List of (dist, a, b) used to find the next shortest edge
q = []
# Add all "edges"
for a, b in combinations(range(len(points)), 2):
    q.append((dist(points[a], points[b]), a, b))
q.sort()

for d, a, b in q:
    if ds_find(s, a) != ds_find(s, b):
        # If we already have the required number of groups
        # *and* that this edge connects two different groups
        # take it as the result and exit
        if g == k:
            result = d
            break
        ds_union(s, a, b)
        # Every time two trees are merged the number of groups decreases by 1
        g -= 1
        # Note even though here g might equal k, we should not break immediately
        # instead loop until we find an edge that connects two different groups

# Format to 9 decimal places
print(f"{result:.9f}")
