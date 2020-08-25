"""
Python solution for CCC '07 J5 - Keep on Truckin'
"""

m_init = [0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000]

min_dist = int(input())
max_dist = int(input())
n = int(input())

# Read in additional motels and sort array
motel = sorted(m_init + [int(input()) for _ in range(n)])

# Cache results
results = [None for _ in motel]
# Base case: Last motel has only 1 option
results[-1] = 1
def options(m):
    if results[m] is not None:
        return results[m]
    # Sum all available options
    s = 0
    for i in range(m + 1, len(motel)):
        d = motel[i] - motel[m]
        # Skip if unreachable
        if d < min_dist:
            continue
        if d > max_dist:
            break
        s += options(i)
    results[m] = s
    return s

print(options(0))
