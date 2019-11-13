"""
Python solution for CCC '05 S4 - Pyramid Messaging Scheme
"""

# Input hack for faster input reading
# Read in all input at once and buffer it
# This is also needed later since we need to look ahead
import sys
_all_data = sys.stdin.read().split("\n")
_line = -1
def _input():
    global _line
    _line += 1
    return _all_data[_line]
# Reassign input() to return from our buffered input
input = _input

# Prints time saved for every case
def main():
    # Get number of messages
    n = int(input())
    # The last message is always sent to the "head zombie"
    home = _all_data[_line + n]
    # Current node
    current = home
    # Use a dict from strings to lists of strings for our adjacency list
    graph = { current: [] }
    for i in range(n):
        s = input()
        # For each line of input:
        # If it's not in the graph, then there's a 1-way connection between
        # the current zombie and the one sent to
        if s not in graph:
            # Add that connection
            graph[current].append(s)
            # Also put the zombie the message was sent to into the graph
            graph[s] = []
        # If it's already in the graph, then it's a reply message
        # Therefore ignore it
        # We can safely do this because the graph is a tree
        
        # Now we're at a different zombie
        current = s
    
    # After the tree is constructed, try to find its depth
    deepest = 0
    # Use a simple recursive dfs
    def dfs(start, depth):
        depth += 1
        nonlocal deepest
        # Keep track of the max depth
        if depth > deepest:
            deepest = depth
        for s in graph[start]:
            dfs(s, depth)
    dfs(home, -1)
    # The amount of time it takes using the new method is always equal to
    # twice the max depth of the tree, since there's a message and a reply
    print((n - deepest * 2) * 10)
        

for i in range(int(input())):
    main()
