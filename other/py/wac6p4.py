"""
Note: This solution currently does not work
Optimization is needed

See wac6p4.cpp for a working solution
"""

from sys import stdin
n, k, s = stdin.read().split()
n = int(n)
k = int(k)

m = 998244353

# iterate a column
def ic(arr, col):
    for row in arr:
        yield row[col]

# Calculate the matrix product AB
def mmul(a, b):
    c = [[0 for _ in range(len(b[0]))] for _ in range(len(a))]
    for row in range(len(a)):
        for col in range(len(b[0])):
            c[row][col] = sum(a * b for a, b in zip(a[row], ic(b, col)))
    return c

# Calculate A^n
def mpow(a, n):
    if n == 1:
        return a
    p = mpow(a, n // 2)
    if n % 2 == 0:
        return mmul(p, p)
    else:
        return mmul(mmul(p, p), a)

w_mat = (
    (1, 0, 0, 0),
    (1, 1, 0, 0),
    (0, 0, 1, 0),
    (0, 0, 0, 1)
)
a_mat = (
    (1, 0, 0, 0),
    (0, 1, 0, 0),
    (0, 1, 1, 0),
    (0, 0, 0, 1)
)
c_mat = (
    (1, 0, 0, 0),
    (0, 1, 0, 0),
    (0, 0, 1, 0),
    (0, 0, 1, 1)
)

mat = (
    (1, 0, 0, 0),
    (0, 1, 0, 0),
    (0, 0, 1, 0),
    (0, 0, 0, 1)
)

vec = [[1], [0], [0], [0]]
for c in s:
    if c == "W":
        mat = mmul(w_mat, mat)
    elif c == "A":
        mat = mmul(a_mat, mat)
    elif c == "C":
        mat = mmul(c_mat, mat)
    # print("Current char is", c)
    # print(*mat, sep='\n')
    # print("State", mmul(mat, vec))
mat = mpow(mat, k)
result = mat[3][0]
print(result)
