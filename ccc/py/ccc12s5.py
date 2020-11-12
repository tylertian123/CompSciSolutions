"""
Python solution for CCC '12 S5 - Mouse Journey
"""

r, c = input().split()
r = int(r)
c = int(c)

cages = [[None] * c for _ in range(r)]
k = int(input())
for _ in range(k):
    row, col = input().split()
    cages[int(row) - 1][int(col) - 1] = 0

cages[r - 1][c - 1] = 1
def get_cage(row, col):
    if cages[row][col] is not None:
        return cages[row][col]
    total = 0
    if row < r - 1:
        total += get_cage(row + 1, col)
    if col < c - 1:
        total += get_cage(row, col + 1)
    cages[row][col] = total
    return total

print(get_cage(0, 0))
