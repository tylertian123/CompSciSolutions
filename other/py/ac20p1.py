from sys import stdin
_all_data = stdin.read().split("\n")
_line = -1
def input():
    global _line
    _line += 1
    return _all_data[_line]

for _ in range(int(input())):
    a, b, c = (int(s) for s in input().split(" "))

    if max(a, b, c) == b:
        a, b, c = b, a, c
    elif max(a, b, c) == c:
        a, b, c = c, a, b
    
    if a ** 2 > b ** 2 + c ** 2:
        print("O")
    elif a ** 2 == b ** 2 + c ** 2:
        print("R")
    else:
        print("A")
