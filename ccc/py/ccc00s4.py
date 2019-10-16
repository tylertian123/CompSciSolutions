from math import isnan
dist = int(input())
num_clubs = int(input())

clubs = []

for i in range(num_clubs):
    clubs.append(int(input()))

known = {}
def fewest_strokes(distance, clubs):
    if distance == 0:
        return 0
    # Dynamic Programming!
    if distance in known:
        return known[distance]
    # Loop through every club to find a match
    for club in clubs:
        if club == distance:
            return 1
    
    # If no match found then further break up the problem
    results = []
    for club in clubs:
        # If the club hits further than the distance then no point trying
        if club > distance:
            continue
        # Otherwise add in the possibility
        results.append(fewest_strokes(distance - club, clubs))
    
    fewest = float("inf")
    for result in results:
        # Skip all the NaNs
        if isnan(result):
            continue
        if result < fewest:
            fewest = result
    if fewest == float("inf"):
        fewest = float("nan")
    
    known[distance] = fewest + 1
    return fewest + 1
    
result = fewest_strokes(dist, clubs)
if isnan(result):
    print("Roberta acknowledges defeat.")
else:
    print("Roberta wins in {} strokes.".format(result))
