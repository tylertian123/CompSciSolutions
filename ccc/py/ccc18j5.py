from queue import Queue

# Get the number of pages
pages = int(input())

# Create empty graph
graph = [ [] for i in range(pages) ]

# Record all ending pages
ending_pages = []

# Loop through each page input
for i in range(pages):
    # Get the input line
    line = input().split()

    # If this is an ending page then add it to the list and skip it
    if int(line[0]) == 0:
        ending_pages.append(i)
        continue
    
    # Otherwise add it to the adjacency list
    for j in range(1, len(line)):
        # Subtract 1 for zero-based indexing
        dest_page = int(line[j]) - 1
        graph[i].append(dest_page)

# Keep track of what to visit next
next = Queue()
# Keep track of what's already been visited
visited = [ False for i in range(pages) ]
# Keep track of what's already in the queue but not visited
queued = [ False for i in range(pages) ]
# Keep track of how we got to each page
parent = [ None for i in range(pages) ]
# Start on page 1 (index 0)
next.put(0)

# Perform BFS
while not next.empty():
    # Get the next page to visit
    current = next.get()
    # Mark the page as visited
    visited[current] = True
    # For each child
    for child in graph[current]:
        # If not visited and not already in queue
        if not visited[child] and not queued[child]:
            # Put the child in the queue
            next.put(child)
            # Record the child's parent
            parent[child] = current
            # Mark the child as in queue
            queued[child] = True

# See of all pages were visited
all_visited = True
for page in visited:
    # If any page was not visited then print N
    if not page:
        all_visited = False
        break

print("Y" if all_visited else "N")

# Find the shortest path
shortest = 999999999
# For each ending page
for page in ending_pages:
    # Make sure it's visited
    if not visited[page]:
        continue
    # Calculate the length
    # Note that every path has at least 1 page
    length = 1
    # While we're not on the starting page
    while page != 0:
        # Go back one edge
        page = parent[page]
        length += 1
    # Update shortest if needed
    if length < shortest:
        shortest = length

print(shortest)
