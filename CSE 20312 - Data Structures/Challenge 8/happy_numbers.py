#!/usr/bin/env python3

'''
Title:      happy_numbers.py
Abstract:   Determine if a number is a happy number or not using memoization.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   20 minutes
Date:       11/14/2022
Questions:

    1. How is seen used in is_happy()?

        seen is used to keep track of numbers that have been used before, because if they have been it would indicate a cycle and therefore the number is not happy.

    2. How is table used in is_happy() to implement memoization?

        table is used to keep track of numbers that have been determined to be happy or not, that way if the algorithm comes across a number it knows is happy or not, it can return a value quickly.

    3. How many happy numbers are there between 1 and 100 (inclusive)?

        There are 20 happy numbers between 1 and 100.
'''

from table import Map

import sys

# Functions

def is_happy(n, seen, table):
    ''' Return whether or not n is a happy number.

    >>> is_happy(19, Map(), Map())
    True

    >>> is_happy(2, Map(), Map())
    False

    >>> is_happy(68, Map(), Map())
    True

    >>> is_happy(75, Map(), Map())
    False

    >>> is_happy(91, Map(), Map())
    True
    '''
    if n == 1:
        return True
    elif seen.lookup(n):
        return False
    seen.insert(n, 1)
    digits = map(int, str(n))
    n = 0
    for i in digits:
        n += i**2
    h = is_happy(n, seen, table)
    table.insert(n, h)
    return h

# Main Execution

def main(stream=sys.stdin):
    ''' For each number in standard input, determine if it is a happy number,
    and print it out.

    >>> import io
    >>> main(io.StringIO('19\\n2\\n68\\n75\\n91\\n'))
    Is 19 Happy?: Yes
    Is 2 Happy?: No
    Is 68 Happy?: Yes
    Is 75 Happy?: No
    Is 91 Happy?: Yes
    '''
    happy = Map()
    for line in stream:
        seen = Map()
        h = "Yes" if is_happy(int(line), seen, happy) else "No"
        print("Is " + line.strip() + " Happy?: " + h)

if __name__ == '__main__':
    main()
