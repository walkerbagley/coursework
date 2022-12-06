#!/usr/bin/env python3

'''
Title:      collatz.py
Abstract:   Compute the Collatz cycle length using memoization.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   30 minutes
Date:       11/14/2022
Questions:

    1. What is stored in the table passed to cycle_length()?

        Pairs of the number of cycle counts for numbers that have already been seen.

    2. How is table used in cycle_length() to implement memoization?

        The recursive calls to new numbers adds an entry to the hash table for that number's cycle count, which is referenced at the beginning of the function to speed up the function.

    3. What number between 100 and 1000 (inclusive) has the longest cycle
    length?

        871 has the longest cycle at a length of 179.
'''

from table import Map

import sys

# Functions

def cycle_length(n, table):
    ''' Return the collatz cycle length.

    >>> cycle_length(22, Map())
    16

    >>> cycle_length(58, Map())
    20

    >>> cycle_length(71, Map())
    103

    >>> cycle_length(1337, Map())
    45
    '''
    n = int(n)
    c = 0
    if n == 1:
        return 1
    val = table.lookup(n)
    if val:
        return c + val
    c += 1
    if n % 2 == 0:
        c += cycle_length(n / 2, table)
    else:
        c += cycle_length(3 * n + 1, table)
    table.insert(n, c)
    return c


# Main Execution

def main(stream=sys.stdin):
    ''' For each number in standard input, compute the cycle length, and print
    it out.

    >>> import io
    >>> main(io.StringIO('22\\n58\\n71\\n1337\\n'))
    Cycle Length of 22: 16
    Cycle Length of 58: 20
    Cycle Length of 71: 103
    Cycle Length of 1337: 45
    '''
    m = Map()
    for line in stream:
        print("Cycle Length of " + line.strip() + ": " + str(cycle_length(int(line), m)))

if __name__ == '__main__':
    main()
