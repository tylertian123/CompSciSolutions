"""
Python solution for CCC '11 S4 - Blood Distribution
"""

blood = [int(i) for i in input().split()]
patients = [int(i) for i in input().split()]

names = [
    "on",
    "op",
    "an",
    "ap",
    "bn",
    "bp",
    "abn",
    "abp",
]

accept = [
    ("on",),
    ("op", "on"),
    ("an", "on"),
    ("ap", "an", "op", "on"),
    ("bn", "on"),
    ("bp", "bn", "op", "on"),
    ("abn", "an", "bn", "on"),
    ("abp", "abn", "ap", "an", "bp", "bn", "op", "on"),
]

total = 0

for i, patient in enumerate(patients):
    for bt in accept[i]:
        c = min(blood[names.index(bt)], patient)
        total += c
        blood[names.index(bt)] -= c
        patient -= c

print(total)
