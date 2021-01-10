from sys import stdin
_d = stdin.read().split('\n')
_l = -1
def _input():
    global _l
    _l += 1
    return _d[_l]
input = _input

n, m, k = [int(i) for i in input().split(" ")]
p = [0] * (n + 1)
for _ in range(m):
    a, b = input().split(" ")
    p[int(a) - 1] -= 1
    p[int(b)] += 1

q = m
for i in range(n):
    q += p[i]
    p[i] = q
p.pop()

w = n + 1
c = 0
s = 0
e = 0
while e < n:
    while c < k and e < n:
        c += p[e]
        e += 1
    while c >= k and s < n:
        w = min(w, e - s)
        c -= p[s]
        s += 1

print(w if w != n + 1 else -1)
