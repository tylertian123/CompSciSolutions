# Read in all 3 rules
rules = [input().split() for i in range(3)]
# Read in the next line
temp = input().split()
# Separate it into the number of steps, the initial state and the final state
steps = int(temp[0])
initial = temp[1]
final = temp[2]

# Applies the given rule to s at the index.
def apply_rule(s, rule, index):
    # Test if the string is long enough to apply the rule at the given index
    if index + len(rule[0]) > len(s):
        return False
    # If the string is long enough, loop through every character and see if they all match
    for i in range(0, len(rule[0])):
        if s[i + index] != rule[0][i]:
            return False
    # If all tests have passed, return the replaced string
    return s[:index] + rule[1] + s[index + len(rule[0]):]

# Keep a set of all string-steps tuples that failed
failed = set()
def sub(init, steps):
    # If the current state is known to fail return None
    if (init, steps) in failed:
        return None
    # If we reached the goal, return an empty array to signify that the result was found
    if init == final and steps == 0:
        return []
    # Otherwise if we run out of steps, add it to the fail set and return None
    elif steps == 0:
        failed.add((init, steps))
        return None
    # For every rule
    for rule_index, rule in enumerate(rules):
        # For every index that the rule can possibly be applied to
        for i in range(len(init)):
            # Try to apply the rule
            r = apply_rule(init, rule, i)
            # If the rule can be applied
            if r != False:
                # Take the string after the rule was applied and recursively call sub with 1 less step
                res = sub(r, steps - 1)
                # If the attempt was a success, append a tuple representing the last step we took to the result and return it
                if res != None:
                    res.append((rule_index + 1, i + 1, r))
                    return res
    # If nothing works, add it to the fail set and return None
    failed.add((init, steps))
    return None

result = sub(initial, steps)
# Note that the result is reversed as the step that was applied first actually gets put last in the array
result.reverse()
for step in result:
    print(step[0], step[1], step[2])

