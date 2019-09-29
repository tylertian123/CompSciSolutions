from math import nan, isnan

n = int(input())

triangle = []
sums = []

for i in range(n):
    triangle.append([int(num) for num in input().split()])
    sums.append([nan] * len(triangle[i]))

def triangle_sum(row, col):
    if not isnan(sums[row][col]):
        return sums[row][col]
    if row == len(triangle) - 1:
        sums[row][col] = triangle[row][col]
        return triangle[row][col]
    left_sum = triangle_sum(row + 1, col)
    right_sum = triangle_sum(row + 1, col + 1)
    result = max(left_sum, right_sum) + triangle[row][col]
    sums[row][col] = result
    return result

print(triangle_sum(0, 0))
