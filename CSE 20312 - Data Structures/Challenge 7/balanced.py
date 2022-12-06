#!/usr/bin/env python3

'''
Title:      balanced.py
Abstract:   Determine wether or not a binary tree is balanced.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   20 minutes
Date:       11/07/2022
Questions:

    1. What is the worst-case time complexity of is_balanced()?

        O(n)

    2. What information does is_balanced() return?

        is_balanced() returns whether or not the two subtrees are balanced as well as the height of the longest subtree.
'''

import sys

# Functions

def is_balanced(array, index=0):
    ''' Determine whether or not a binary tree is balanced.

    A binary tree is balanced if:

    1. Left and right sub-trees are balanced.
    2. Difference between heights of left and right sub-trees is no more than 1.

    >>> is_balanced([5, 3, 6])
    (True, 2)

    >>> is_balanced([5, 3, 6, 4])
    (True, 3)

    >>> is_balanced([5, 3, 0, 4])
    (False, 3)

    >>> is_balanced([5, 3, 4, 0, 1])
    (True, 3)

    >>> is_balanced([5, 3, 4, 0, 1, 0, 0, 0, 0, 2])
    (False, 4)
    '''
    if index >= len(array) or array[index] == 0:
        return True, 0
    
    lt, lh = is_balanced(array, index * 2 + 1)
    rt, rh = is_balanced(array, index * 2 + 2)

    t = lt and rt
    h = False if abs(lh-rh) > 1 else True

    return t and h, 1 + max(lh, rh)

# Main Execution

def main(stream=sys.stdin):
    ''' For each line with a tree given in BFS format, output whether or not it
    is balanced.

    >>> import io
    >>> main(io.StringIO('5 3 6\\n5 3 6 4\\n5 3 0 4\\n'))
    Balanced
    Balanced
    Not Balanced
    '''
    for line in stream:
        s = "Balanced" if is_balanced([int(i) for i in line.split()])[0] else "Not Balanced"
        print(s)

if __name__ == '__main__':
    main()
