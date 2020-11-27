"""
Python solution for CCC '15 J5 - Pi-day
"""

n = int(input())
k = int(input())

known = {}

def pie(n, k, m):
    """
    n - Number of pieces of pie left
    k - Number of mathematicians left
    m - Number of pieces the last mathematician got - minimum number of pieces to distribute
    """
    # Check if distribution is possible at all
    if n // k < m:
        return 0
    # Base cases, as provided by the problem itself
    if k == n or k == 1:
        return 1
    # All quantities are <= 255, so pack into a 32-bit integer for more efficient hashing
    key = n << 16 | k << 8 | m
    if key in known:
        return known[key]
    # Try giving all possible numbers of pieces of pie
    total = 0
    for p in range(m, n + 1):
        # Give p pieces
        # (n - p) pieces left, (k - 1) people left in line
        # and a minimum of p pieces for the next person
        ways = pie(n - p, k - 1, p)
        # If distribution not possible than we gave out too many pieces
        # No point in trying the rest
        if ways == 0:
            break
        total += ways
    known[key] = total
    return known[key]

print(pie(n, k, 1))
