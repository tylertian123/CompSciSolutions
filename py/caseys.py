# Read in money
money = int(input())
# Read in count
count = int(input())
# Read in all menu items
# Each menu item is a tuple of a name and a price
menu = []
for i in range(count):
    name, p = input().split()
    menu.append((name, int(p)))

# This array keeps track of all solutions to be printed later
solutions = []
# This set keeps track of which states have been visited
# This avoids duplicate states and speeds up execution (DP)
solved = set()
def solve(state, money):
    # Convert the state to a tuple so we can put it in a set
    state_t = tuple(state)
    # Check if we already came across this state
    if state_t in solved:
        return
    if money == 0:
        # If we have a solution, make a copy of the state and add it 
        # to the solutions list, and finally mark the current state as visited
        solution = state.copy()
        solutions.append(solution)
        solved.add(state_t)
    else:
        # If we still have money then iterate through every menu item
        for index, item in enumerate(menu):
            # If we can afford the item:
            if item[1] <= money:
                # Update the state
                state[index] += 1
                # Recursively call solve with the new state and price
                solve(state, money - item[1])
                # Reset the state
                # This way we don't need to make expensive copies
                state[index] -= 1
    # When everything is done mark the state as solved
    solved.add(state_t)

solve([0] * count, money)

# Print all solutions
if len(solutions) > 0:
    for solution in solutions:
        print("--------------------")
        for index, menu_item in enumerate(menu):
            # For every menu item in a solution
            # Print it if the count is greater than zero
            if solution[index] > 0:
                print(menu_item[0], "\tx", solution[index])
    print("--------------------")
else:
    print("How was your dinner?")

