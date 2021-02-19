"""
Redefine Python's input() to read from buffered data for faster I/O.
"""

import sys
_all_data = sys.stdin.read().split('\n')
_line = -1
def _input():
    global _line
    _line += 1
    return _all_data[_line]
input = _input
