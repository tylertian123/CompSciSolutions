"""
Python solution for CCC '03 S4 - Floor Plan
"""


# Input hack for faster input reading
# Read in all input at once and buffer it
import sys
_all_data = sys.stdin.read().split('\n')
_line = -1
def _input():
    global _line
    _line += 1
    return _all_data[_line]
# Reassign input() to return from our buffered input
input = _input

from queue import Queue
# Read flooring and size of plan
f = int(input())
r = int(input())
c = int(input())

# Read plan
plan = [input() for i in range(r)]
# Create empty 2d array to mark which squares have been visited
visited = [[False for i in range(c)] for i in range(r)]

rooms = []
# This returns the size of the room the specified square is in
# Also sets the contents of the visited array
def fill_room(row, col):
    # Keep track of the size
    size = 0
    # Standard BFS
    q = Queue()
    q.put((row, col))
    visited[row][col] = True
    
    while not q.empty():
        n = q.get()
        # Increment size for each square
        size += 1
        # Try going up, down, left and right
        for p in [(n[0] - 1, n[1]), (n[0] + 1, n[1]), (n[0], n[1] - 1), (n[0], n[1] + 1)]:
            # Verify in bounds, not visited and not wall
            if p[0] >= 0 and p[0] < r and p[1] >= 0 and p[1] < c and not visited[p[0]][p[1]] and plan[p[0]][p[1]] == '.':
                q.put(p)
                visited[p[0]][p[1]] = True
    return size

# Go through every single square
for i in range(0, r):
    for j in range(0, c):
        # If the square is not a wall and has not been visited
        if not visited[i][j] and plan[i][j] == '.':
            # Visit the room that square is in
            rooms.append(fill_room(i, j))
# Sort the rooms in descending order
rooms.sort(reverse = True)
t = 0
for size in rooms:
    # For each room in order, if there's enough flooring
    # add to room count and decrease flooring
    if f >= size:
        f -= size
        t += 1
    # Otherwise stop
    else:
        break
# DMOJ Note: if there's only 1 room, print "room" instead of "rooms"
print(t, "rooms," if t != 1 else "room,", f, "square metre(s) left over")
