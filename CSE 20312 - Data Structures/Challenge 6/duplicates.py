#!/usr/bin/env python3

'''
Title:      duplicates.py
Abstract:   Determine whether or not a line of words contains any duplicates.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   30 minutes
Date:       10/31/2022
Questions:

    1. What is the average time complexity of detect_duplicates()?

        O(nlogn)

    2. What is the worst-case time complexity of detect_duplicates()?

        O(n^2)

    3. What is the worst-case space complexity of detect_duplicates()?

        O(n)

    4. How would you modify the program to make it case in-sensitive?

        I would simply convert each character to lowercase in the for loop using Python's built in lower() function.
'''

import sys

from set import Set

# Functions

def detect_duplicates(words):
    ''' Return whether or not the sequence of words contains a duplicate.

    >>> detect_duplicates('a b c'.split())
    False

    >>> detect_duplicates('a b a'.split())
    True

    >>> detect_duplicates('a b c b e f'.split())
    True
    '''
    s = Set()
    for i in words:
        if s.search(i):
            return True
        s.insert(i)
    return False
    

# Main Execution

def main(stream=sys.stdin):
    ''' For each line of words, determine if there are any duplicates.

    >>> import io
    >>> main(io.StringIO('a b c\\na b a\\na b c b e f\\n'))
    False
    True
    True
    '''
    for line in stream:
        print(detect_duplicates(line.split()))

if __name__ == '__main__':
    main()
