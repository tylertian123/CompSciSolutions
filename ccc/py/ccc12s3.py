"""
Python solution for CCC '12 S3 - Absolutely Acidic
"""

n = int(input())
count = [0 for i in range(1000)]

for _ in range(n):
    count[int(input()) - 1] += 1

max_freq = 0
second_max_freq = 0
for freq in count:
    if freq > max_freq:
        second_max_freq = max_freq
        max_freq = freq
    elif freq > second_max_freq and freq < max_freq:
        second_max_freq = freq

first_max_reading = count.index(max_freq)
last_max_reading = -1
first_second_max_reading = count.index(second_max_freq)
last_second_max_reading = -1

for i, freq in enumerate(reversed(count)):
    if freq == max_freq:
        last_max_reading = len(count) - i - 1
        break
for i, freq in enumerate(reversed(count)):
    if freq == second_max_freq:
        last_second_max_reading = len(count) - i - 1
        break

if first_max_reading != last_max_reading:
    print(last_max_reading - first_max_reading)
else:
    print(max(abs(first_max_reading - first_second_max_reading), abs(first_max_reading - last_second_max_reading)))
