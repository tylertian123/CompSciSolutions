"""
Python solution for CCC '17 S1 - Sum Game
"""

n = int(input())
a = [int(i) for i in input().split()]
b = [int(i) for i in input().split()]
k = 0
a_sum = 0
b_sum = 0
for i in range(n):
    a_sum += a[i]
    b_sum += b[i]
    if a_sum == b_sum:
        k = i + 1
print(k)
