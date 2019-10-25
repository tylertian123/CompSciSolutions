"""
ccc05j5.py: Python solution to CCC '05 J5 (Bananas)
"""

# Create these sets to hold the known valid and invalid A-words to save time
# We already know that 'A' is a valid A-word and an empty string is always invalid
known_awords = set(['A'])
known_nonawords = set([''])
def is_aword(word):
    # First try looking into the known sets
    if word in known_awords:
        return True
    if word in known_nonawords:
        return False
    
    # Otherwise see if the word starts with a 'B' and ends with an 'S'
    # Since 'A' is already handled
    # if the word's length is less than 3 it cannot be valid
    if len(word) < 3 or not (word[0] == 'B' and word[-1] == 'S'):
        known_nonawords.add(word)
        return False
    # If yes then get the word in between the 'B' and the 'S'
    inner_word = word[1:-1]
    # See if the inner word is a monkey word
    if is_monkey(inner_word):
        known_awords.add(word)
        return True
    else:
        known_nonawords.add(word)
        return False

# Create sets to hold known results like above
known_words = set()
known_nonwords = set([''])
def is_monkey(word):
    # Check known sets
    if word in known_words:
        return True
    if word in known_nonwords:
        return False

    # First check if the word itself is an A word
    if is_aword(word):
        known_words.add(word)
        return True
    else:
        # If not then see if it's two monkey words joined together with an N
        for i, c in enumerate(word):
            # For every single occurrence of N try splitting
            if c == 'N':
                try:
                    word1 = word[0:i]
                    word2 = word[i + 1:]
                    # See if both parts of the string are monkey words
                    if is_monkey(word1) and is_monkey(word2):
                        known_words.add(word)
                        return True
                # Catch the possible IndexError with Ns in the beginning or end of the string
                except IndexError:
                    pass
        # If that did not return then the word is not a monkey word
        known_nonwords.add(word)
        return False

while True:
    word = input()
    if word == 'X':
        break
    print("YES" if is_monkey(word) else "NO")
