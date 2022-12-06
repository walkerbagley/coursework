#!/usr/bin/env python3

'''
Title:      priority_queue.py
Abstract:   Implement a priority queue using an array-based binary tree.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   20 minutes
Date:       10/25/2022
Questions:

    1. While performing a BFS, how do you know if node is valid or not?

        The node is invalid if it contains 0 and valid if it does not.

    2. What is the worst-case time complexity of PriorityQueue.pop()?

        O(n)

    3. What is the worst-case space complexity of PriorityQueue.pop()?

        O(1)
'''

from collections import deque

# Classes

class PriorityQueue:
    ''' Simple priority queue using an array-based binary tree. '''

    def __init__(self, tree):
        ''' Initialize internal binary tree.

        >>> pq = PriorityQueue([4, 6, 6, 3, 7]); pq.tree
        [4, 6, 6, 3, 7]
        '''
        self.tree = tree

    def pop(self):
        ''' Return the largest value in priority queue.

        Walk tree using BFS to find largest value, place 0 in its place, and
        then return largest value.

        >>> pq = PriorityQueue([4, 6, 6, 3, 7])
        >>> [pq.pop(), pq.pop(), pq.pop(), pq.pop(), pq.pop()]
        [7, 6, 6, 4, 3]
        >>> pq.tree
        [0, 0, 0, 0, 0]
        '''
        max = self.tree[0]
        idx = 0
        for i, n in enumerate(self.tree):
            if n > max:
                max = n
                idx = i
        self.tree[idx] = 0
        return max


# Functions

def left_child(index):
    ''' Return index of left child.

    >>> left_child(0)
    1

    >>> left_child(1)
    3
    '''
    return index*2+1

def right_child(index):
    ''' Return index of right child.

    >>> right_child(0)
    2

    >>> right_child(1)
    4
    '''
    return index*2+2
