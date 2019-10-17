from math import nan, isnan
import sys

sys.setrecursionlimit(3000)

cells = [input().split() for i in range(10)]
values = [[None for i in range(9)] for i in range(10)]

def fill_cell(loc, visited=None):
    row, col = loc
    # Return value of the cell if already filled
    if values[row][col] != None:
        return values[row][col]
    # Otherwise if cell is a number then convert it directly
    if cells[row][col][0].isnumeric():
        values[row][col] = int(cells[row][col])
        return values[row][col]
    else:
        # Otherwise add up the cells
        # Create the visited set if not created
        if not visited:
            visited = set()
        visited.add(loc)

        refs = cells[row][col].split('+')
        total = 0
        for ref in refs:
            # Calculate the cell's location
            nrow = ord(ref[0]) - ord('A')
            ncol = int(ref[1:]) - 1
            nloc = (nrow, ncol)
            val = 0
            # If the cell already has a value then use that
            if values[nrow][ncol] != None:
                val = values[nrow][ncol]
            else:
                # Already in chain - undefined
                if nloc in visited:
                    values[row][col] = nan
                    return nan
                # Otherwise recurse on the cell
                # Note: make a new set from the current one so we can
                # reuse it for the next cells
                val = fill_cell(nloc, set(visited))
            # If result is undefined then the cell is undefined
            if isnan(val):
                total = nan
                break
            total += val
        values[row][col] = total
        return total

for i in range(10):
    for j in range(9):
        if values[i][j] == None:
            fill_cell((i, j))

for row in values:
    print(*(i if not isnan(i) else '*' for i in row))
