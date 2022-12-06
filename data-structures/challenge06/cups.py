#!/usr/bin/env python3

'''
Title:      cups.py
Abstract:   Determine the minimum amount of time require to fill all cups of water.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   30 minutes
Date:       10/31/2022
Questiones:

    1. What is the worst-case time complexity of fill_cups()?

        O(nlogn)

    2. What is the worst-case space complexity of fill_cups()?

        O(n)

    3. Why is this considered a greedy approach?

        By selecting the two largest values in the heap at each iteration as the cups to fill, it is ensured that two cups are being knocked off at once for as many steps as possible, therefore reducing the number of seconds necessary to the minimum.
'''

import sys

from priority_queue import PriorityQueue

# Functions

def fill_cups(cups):
    ''' Return minimum number of seconds required to fill all cups of water.

    Use a greedy algorithm by attempting to fill two types of cups at a time
    until there is only one remaining type.
    >>> fill_cups([1, 4, 2])
    4

    >>> fill_cups([5, 4, 4])
    7

    >>> fill_cups([5, 0, 0])
    5
    '''
    pq = PriorityQueue([i for i in cups if i != 0])
    c = 0
    while pq.size() > 1:
        a, b = pq.pop(), pq.pop()
        pq.push(a - 1) if a != 1 else None
        pq.push(b - 1) if b != 1 else None
        c += 1
    if pq.size() == 1:
        c += pq.pop()
    return c


# Main Execution

def main(stream=sys.stdin):
    ''' For each line of cups, determine the minimum number of seconds required
    to fill all cups of water.

    >>> import io
    >>> main(io.StringIO('1 4 2\\n5 4 4\\n5 0 0\\n'))
    4
    7
    5
    '''
    for i in stream:
        print(fill_cups([int(j) for j in i.split()]))

if __name__ == '__main__':
    main()
