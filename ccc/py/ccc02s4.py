from copy import copy

# Read in max people at a time and length of queue
m = int(input())
n = int(input())
# Read in every person into tuples of (name, cross time)
q = [(input(), int(input())) for i in range(n)]

# Use an array to keep track of the known best configurations
# Since the people have to be in order, the minimum time and way to arrange
# people is solely dependent on where we start in the queue
# Since the queue is always 100 or less people long, an array is better than a dict
# This should store tuples of (total time, groups) just like the cross function's return
known = [None for i in range(n)]

# Calculates the best arrangement of people
# Returns a tuple of (total time, groups)
# where groups is an array of integers, each representing the number of people 
# in a given group in order; note that due to implementation is is reversed
# Takes in two args, start is the index of the queue to start at
# time is the amount of time that has already passed
def cross(start, time):
    # Check if config already known
    if known[start] != None:
        # If so use the known result
        # Note known stores the time it takes starting from this point and does not
        # take into account the time already elapsed
        # Therefore add time to it to get the total time
        return (time + known[start][0], known[start][1])
    # Check for base cases
    # If the number of people left is less than the limit, then everyone goes together
    if n - start <= m:
        # The total time it takes from here is the max over the rest of the queue
        # And there's only 1 group, with the same size as there are people left
        known[start] = (max(i[1] for i in q[start:]), [n - start])
        # As mentioned above add the already passed time to it
        return (time + known[start][0], known[start][1])
    
    # Otherwise recurse and try to find the best option
    min_config = [9999999999, None]
    # Stores the group size
    s = 0
    # Try all possible group sizes from here
    for i in range(1, m + 1):
        # Calculate the time for this group to cross
        t = max(i[1] for i in q[start:start+i])
        # Recursively call cross after this group crosses
        res = cross(start + i, time + t)
        # If the result we get is better than the previous ones
        if res[0] < min_config[0]:
            # Update the new best result and group size
            min_config = res
            s = i
    # Create the result
    # Note that since we have to append a group to the groups array,
    # but the original groups should not be modified, we need to make a copy
    res = (min_config[0], copy(min_config[1]))
    # Add the next group
    res[1].append(s)
    # Add it to the known scenarios
    # Note time is subtracted to get the amount of time it takes from here
    known[start] = (res[0] - time, res[1])
    return res

res = cross(0, 0)
print("Total Time:", res[0])
# Print out the people's names
j = 0
# Note the result from cross() is reversed
for i in reversed(res[1]):
    print(*(p[0] for p in q[j:j+i]))
    j += i

