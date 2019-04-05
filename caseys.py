money = int(input())

count = int(input())
menu = []
for i in range(count):
    name, p = input().split()
    menu.append((name, int(p)))

solutions = []
solved = set()
def solve(state, money):
    state_t = tuple(state)
    if state_t in solved:
        return
    if money == 0:
        solution = state.copy()
        solutions.append(solution)
        solved.add(state_t)
    else:
        for index, item in enumerate(menu):
            if item[1] <= money:
                state[index] += 1
                solve(state, money - item[1])
                state[index] -= 1
    solved.add(state_t)

solve([0] * count, money)

if len(solutions) > 0:
    for solution in solutions:
        print("--------------------")
        for index, menu_item in enumerate(menu):
            if solution[index] > 0:
                print(menu_item[0], "\tx", solution[index])
    print("--------------------")
else:
    print("How was your dinner?")

