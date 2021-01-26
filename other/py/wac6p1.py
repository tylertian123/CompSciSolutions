n = int(input())

for _ in range(n):
    p, c = input().split(" ")
    p = float(p)
    c = float(c)
    print(f"{p / (c / 100 + 1)}")
