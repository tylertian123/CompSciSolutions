from sys import exit
square = [[int(i) for i in input().split()] for j in range(4)]
total = sum(square[0][i] for i in range(4))

for i in range(1, 4):
    if sum(square[i][j] for j in range(4)) != total:
        print("not magic")
        exit()

for i in range(4):
    if sum(square[j][i] for j in range(4)) != total:
        print("not magic")
        exit()

print("magic")
