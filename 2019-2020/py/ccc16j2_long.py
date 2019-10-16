grid = []

for i in range(4):
    row = []
    row_str = input()
    row_strs = row_str.split()
    for i in range(4):
        num = int(row_strs[i])
        row.append(num)
    grid.append(row)

total = 0
for col in range(4):
    total += grid[0][col]

is_magic_square = True

for row in range(1, 4):
    row_total = 0
    for col in range(4):
        row_total += grid[row][col]
    if row_total != total:
        is_magic_square = False
        break

for col in range(4):
    col_total = 0
    for row in range(4):
        col_total += grid[row][col]
    if col_total != total:
        is_magic_square = False
        break

if is_magic_square:
    print("magic")
else:
    print("not magic")
