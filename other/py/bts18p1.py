from sys import exit

s = input()
t = input()
k = int(input())

diff = 0
for c, d in zip(s, t):
    if c != d:
        if c == " " or d == " ":
            print("No plagiarism")
            exit()
        diff += 1

print("Plagiarized" if diff <= k else "No plagiarism")
