"""
Python solution for DMOJ Back From Summer '19 P2 - Straying from God's Light

Note: The algorithm presented in this solution is correct, but this TLEs in the later test cases.
See the C++ implementation of this same algorithm for something that will pass the judge.
"""

import sys
_all_data = sys.stdin.read().split('\n')
_line = -1
def _input():
    global _line
    _line += 1
    return _all_data[_line]
input = _input

size = int(input())

# Read in the grid
# This will make a 2d array with Trues for locations we can go
# and False otherwise
grid = [[c == '.' for c in input()] for i in range(size)]

from queue import Queue
# Use a queue to keep track of what to visit next
next_pos = Queue()
# Another 2d array to keep track of what we visited
visited = [[False for i in range(size)] for i in range(size)]
# Every element in the queue consists of two tuples - 
# The location and another tuple containing the steps (D, L, R)
next_pos.put(((0, 0), (0, 0, 0)))

result = None

while not next_pos.empty():
    # Move to the next position
    pos, steps = next_pos.get()
    # See if this is the destination
    if pos == (size - 1, size - 1):
        result = steps
        break
    
    # Otherwise try moving D L R
    # Move down
    # Check for: in bounds, not visited and visitable
    if pos[1] + 1 < size and not visited[pos[1] + 1][pos[0]] and grid[pos[1] + 1][pos[0]]:
        # Add to queue
        next_pos.put(((pos[0], pos[1] + 1), (steps[0] + 1, steps[1], steps[2])))
        visited[pos[1] + 1][pos[0]] = True
    # Move left
    if pos[0] - 1 >= 0 and not visited[pos[1]][pos[0] - 1] and grid[pos[1]][pos[0] - 1]:
        next_pos.put(((pos[0] - 1, pos[1]), (steps[0], steps[1] + 1, steps[2])))
        visited[pos[1]][pos[0] - 1] = True
    # Move right
    if pos[0] + 1 < size and not visited[pos[1]][pos[0] + 1] and grid[pos[1]][pos[0] + 1]:
        next_pos.put(((pos[0] + 1, pos[1]), (steps[0], steps[1], steps[2] + 1)))
        visited[pos[1]][pos[0] + 1] = True

# Result should be the steps at this point or None if not possible
print(result[0] ** 2 + result[1] ** 2 + result[2] ** 2 if result != None else -1)
