"""
Python solution for CCC '06 S3 - Tin Can Telephone
"""

# Input trick to read in input faster
# Read all at once and buffer it
import sys
_all_data = sys.stdin.read().split('\n')
_line_num = -1
_input = input
def input():
    global _line_num
    _line_num += 1
    return _all_data[_line_num]

# Read coordinates of Romy and Jules
xr, yr, xj, yj = [int(i) for i in input().split()]
b = []

# Read in all the buildings
for i in range(int(input())):
    l = input().split()
    # Iterate over the input line two at a time starting from the 2nd element
    b.append([(int(x), int(y)) for x, y in zip(l[1::2], l[2::2])])

def get_eqn(p0, p1):
    """
    Returns the equation of a line in the form mx+b as a tuple of (m, b) for two points.
    Does not check for vertical lines.
    """
    m = (p0[1] - p1[1]) / (p0[0] - p1[0])
    return (m, p0[1] - m * p0[0])

def apply_eqn(eqn, x):
    """
    Applies a line equation in the form returned by get_eqn().
    """
    return eqn[0] * x + eqn[1]

def in_range(x, a, b):
    """
    Tests if a value is in a range. a can be greater than or less than b.
    """
    return (x >= a and x <= b) or (x <= a and x >= b)

def intersection(eqn0, eqn1):
    """
    Finds the intersection point of two equations.
    Does not check for parallel lines.
    """
    x = (eqn1[1] - eqn0[1]) / (eqn0[0] - eqn1[0])
    return (x, apply_eqn(eqn0, x))

def intersects(a0, a1, b0, b1):
    """
    Checks whether two line segments, each defined by two end points, will intersect.
    """
    # First line is vertical
    if a0[0] == a1[0]:
        # Both lines are vertical
        if b0[0] == b1[0]:
            return (a0[0] == b0[0]) and (in_range(b0[1], a0[1], a1[1]) or in_range(b1[1], a0[1], a1[1]))
        eqn = get_eqn(b0, b1)
        y = apply_eqn(eqn, a0[0])
        return in_range(y, a0[1], a1[1])
    # Only second line is vertical
    if b0[0] == b1[0]:
        eqn = get_eqn(a0, a1)
        y = apply_eqn(eqn, b0[0])
        return in_range(y, b0[1], b1[1])
    # Parallel lines
    eqn0 = get_eqn(a0, a1)
    eqn1 = get_eqn(b0, b1)
    if eqn0[0] == eqn1[0]:
        if eqn0[1] != eqn1[1]:
            return False
        return in_range(a0[0], b0[0], b1[0]) or in_range(a1[0], b0[0], b1[0])
    # Get intersection
    i = intersection(eqn0, eqn1)
    # Check if intersection is between end points
    return in_range(i[0], a0[0], a1[0]) and in_range(i[0], b0[0], b1[0]) and in_range(i[1], a0[1], a1[1]) and in_range(i[1], b0[1], b1[1])

block = 0
# Check every building
for building in b:
    blocked = False
    # Check every consecutive pair of points
    for p0, p1 in zip(building, building[1:]):
        if intersects((xr, yr), (xj, yj), p0, p1):
            blocked = True
            break
    # Also check the pair of the first and last points
    if not blocked:
        if intersects((xr, yr), (xj, yj), building[0], building[-1]):
            blocked = True
    
    if blocked:
        block += 1

print(block)
