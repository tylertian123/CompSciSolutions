from sys import stdin, exit

n, c, v = [int(s) for s in stdin.readline().split(" ")]
s = stdin.readline()

vowels = set("aeiouy")
consonants = set("bcdfghjklmnpqrstvwxyz")
cc = 0
vc = 0
for char in s:
    if char in vowels:
        vc += 1
        if vc > v:
            print("NO")
            exit(0)
    else:
        vc = 0
    if char in consonants:
        cc += 1
        if cc > c:
            print("NO")
            exit(0)
    else:
        cc = 0

print("YES")
