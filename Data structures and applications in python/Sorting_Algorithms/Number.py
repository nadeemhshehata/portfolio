"""
-------------------------------------------------------
[program description]
-------------------------------------------------------
Author:  Your Name
ID:      Your ID
Email:   your email@mylaurier.ca
__updated__ = "2024-11-21"
-------------------------------------------------------
"""
# Imports

# Constants

# Number.py


class Number:
    comparisons = 0

    def __init__(self, value):
        self.value = value

    def __eq__(self, other):
        Number.comparisons += 1
        return self.value == other.value

    def __lt__(self, other):
        Number.comparisons += 1
        return self.value < other.value

    def __le__(self, other):
        Number.comparisons += 1
        return self.value <= other.value

    def __str__(self):
        return str(self.value)

    def __repr__(self):
        return f"Number({self.value})"
