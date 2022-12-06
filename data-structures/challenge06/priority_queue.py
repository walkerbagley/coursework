#!/usr/bin/env python3

'''
Title:      priority_queue.py
Abstract:   Implement a priority queue using a binary heap.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   30 minutes
Date:       10/31/2022
Questiones:

    1. What is the worst-case time complexity of PriorityQueue.push()?

        O(n)

    2. What is the worst-case time complexity of PriorityQueue.pop()?

        O(n)

    3. How did you work around the fact that heapq is a min-heap, while our
    PriorityQueue is a max-heap?

        I pushed the opposite sign of data into the priority queue so that when running heapify, the "largest" value would end up at the very left of the heap and could then be popped accordingly. Then I just flipped the sign when popping data so that it was back to the appropriate value.
'''

import heapq

# Classes

class PriorityQueue:
    ''' Simple priority queue based on a binary heap. '''

    def __init__(self, data=None):
        ''' Initialize the internal data.

        >>> pq = PriorityQueue(); pq.data
        []

        >>> pq = PriorityQueue([3, 1, 4]); pq.data[0]
        -4
        '''
        self.data = [-i for i in data] if data != None else []
        heapq.heapify(self.data)

    def push(self, item):
        ''' Add item to Priority Queue.

        >>> pq = PriorityQueue(); pq.push(3); pq.data[0]
        -3

        >>> pq.push(1); pq.data[0]
        -3

        >>> pq.push(4); pq.data[0]
        -4
        '''
        self.data.append(-item)
        heapq.heapify(self.data)


    def pop(self):
        ''' Remove and return smallest value from the Priority Queue.
        >>> pq = PriorityQueue([3, 1 ,4]); pq.pop()
        4

        >>> pq.pop()
        3

        >>> pq.pop()
        1
        '''
        temp =  -self.data.pop(0)
        heapq.heapify(self.data)
        return temp

    def size(self):
        ''' Return number of values in Priority Queue.

        >>> pq = PriorityQueue(); pq.size()
        0

        >>> pq = PriorityQueue([3, 1, 4]); pq.size()
        3
        '''
        return len(self.data)
