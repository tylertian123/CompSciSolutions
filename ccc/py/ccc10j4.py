while True:
    s = [int(i) for i in input().split()]
    if s == [0]:
        break
    s = [s[i + 1] - s[i] for i in range(1, len(s) - 1)]
    print([all((c == s[:i + 1][j % (i + 1)] for j, c in enumerate(s))) for i in range(len(s))].index(True) + 1 if len(s) != 0 else 0)
