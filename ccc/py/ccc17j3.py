start = input().split()
start[0] = int(start[0])
start[1] = int(start[1])

end = input().split()
end[0] = int(end[0])
end[1] = int(end[1])

t = int(input())

total = abs(end[0] - start[0]) + abs(end[1] - start[1])
print("Y" if (t >= total and (t - total) % 2 == 0) else "N")
