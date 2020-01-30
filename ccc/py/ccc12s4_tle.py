"""
Python solution for CCC '12 S4 - A Coin Game

Note: The algorithm in this solution is correct, but since it is written in
Python, it times out when using CPython and exceeds the memory limit when using
PyPy.
"""

from queue import Queue
import gc


def solve(state):
    init = tuple(tuple(t) for t in state)
    q = Queue()
    q.put((state, 0))
    v = set(init)
    while not q.empty():
        state, moves = q.get()
        valid = True
        prev = 0
        for stack in state:
            if len(stack) != 1:
                valid = False
                break
            if prev > stack[0]:
                valid = False
                break
            prev = stack[0]
        if valid:
            return moves

        for position, stack in enumerate(state):
            if len(stack) == 0:
                continue
            coin = stack.pop()
            if position > 0 and (len(state[position - 1]) == 0 or coin < state[position - 1][-1]):
                state[position - 1].append(coin)
                next_state_t = tuple(tuple(t) for t in state)
                if next_state_t not in v:
                    v.add(next_state_t)
                    next_state = [[c for c in p] for p in state]
                    q.put((next_state, moves + 1))
                state[position - 1].pop()
            if position < len(state) - 1 and (len(state[position + 1]) == 0 or coin < state[position + 1][-1]):
                state[position + 1].append(coin)
                next_state_t = tuple(tuple(t) for t in state)
                if next_state_t not in v:
                    v.add(next_state_t)
                    next_state = [[c for c in p] for p in state]
                    q.put((next_state, moves + 1))
                state[position + 1].pop()
            stack.append(coin)
    return -1


while True:
    coins = int(input())
    if coins == 0:
        break
    state = [[int(n)] for n in input().split()]
    moves = solve(state)
    print("IMPOSSIBLE" if moves == -1 else moves)
    gc.collect()
