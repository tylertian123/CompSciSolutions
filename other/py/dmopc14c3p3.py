n = int(input())
emps = []
for i in range(n):
    e = input().split()
    emps.append((e[0], int(e[1])))
q = int(input())
for _ in range(q):
    s, d = [int(i) for i in input().split()]
    e = None
    m = 99999999
    for emp in emps:
        if emp[1] < s or emp[1] - s > d:
            continue
        if emp[1] - s < m:
            m = emp[1] - s
            e = emp
    print(e[0] if e else "No suitable teacher!")
