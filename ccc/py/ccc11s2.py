n = int(input())
print(sum(a == b for a, b in zip([input() for _ in range(n)], [input() for _ in range(n)])))