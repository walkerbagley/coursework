#!/usr/bin/env python3

'''
Title:      tree.py
Abstract:   Implement a binary tree read and walk functions.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   25 minutes
Date:       11/01/2022
Questions:

    1. What is the worst-case time complexity of tree_read()?

        O(n)

    2. What is the worst-case time complexity of tree_walk()?

        O(n)

    3. In tree_walk(), how did you modify BFS to print all the nodes on one
    comma separated line?

        I stored them into an array and then used the native join() function

    4. In tree_walk(), how did you remove any trailing invalid nodes from your
    output?

        I checked if each node had at least one child before appending the children to the queue.
'''

from dataclasses import dataclass
from collections import deque

# Classes

@dataclass
class Node:
    value: int
    left: 'Node' = None
    right: 'Node' = None

# Functions

def tree_read(array, index=0):
    ''' Return a node-based tree from the given array of values in BFS format.

    >>> tree_read([1, 2, 3])
    Node(value=1, left=Node(value=2, left=None, right=None), right=Node(value=3, left=None, right=None))

    >>> tree_read([1, 2, 3, 4, 0, 0, 6])
    Node(value=1, left=Node(value=2, left=Node(value=4, left=None, right=None), right=None), right=Node(value=3, left=None, right=Node(value=6, left=None, right=None)))
    '''
    if index >= len(array) or not array[index]:
        return None
    
    return Node(array[index], tree_read(array, index*2+1), tree_read(array, index*2+2))

def tree_walk(root):
    ''' Print out the tree in level-by-level order with each level on the same
    line.

    >>> tree_walk(tree_read([1, 2, 3]))
    1, 2, 3
    >>> tree_walk(tree_read([1, 2, 3, 4, 0, 0, 6]))
    1, 2, 3, 4, 0, 0, 6
    '''
    a = deque([root])
    n = []
    while a:
        temp = a.popleft()
        if not temp:
            n.append(0)
        elif temp.left or temp.right:
            a.append(temp.left)
            a.append(temp.right)
            n.append(temp.value)
        else:
            n.append(temp.value)
    print(", ".join(map(str,n)))
