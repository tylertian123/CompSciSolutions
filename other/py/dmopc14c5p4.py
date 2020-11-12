n, m = input().split()
n = int(n)
m = int(m)

good = []
bad = []
for _ in range(n):
    s, p = input().split()
    if p == "1":
        bad.append(int(s))
    else:
        good.append(int(s))
good.sort()
bad.sort()

prot = 0
space = 0
gi = 0
bi = 0
while space < m:
    g = good[gi] if gi < len(good) else None
    b = bad[bi] if bi < len(bad) else None
    # Both good and bad left
    if g is not None and b is not None:
        # Can put good
        if space + g <= m:
            # Can't put bad or good is more efficient
            if space + b > m or g / 2 < m:
                prot += 2
                space += g
                gi += 1
            # Can put bad and bad is more efficient
            else:
                prot += 1
                space += b
                bi += 1
        # Can't put good but can put bad
        elif space + b <= m:
            prot += 1
            space += b
            bi += 1
        # Can't put either one
        else:
            break
    # Only good left
    elif g is not None:
        # Still room left
        if space + g <= m:
            prot += 2
            space += g
            gi += 1
        else:
            break
    # Only bad left
    elif b is not None:
        if space + b <= m:
            prot += 1
            space += b
            bi += 1
        else:
            break
    # Nothing left
    else:
        break

print(prot)
