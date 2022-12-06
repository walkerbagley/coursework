#!/usr/bin/env python3

'''
Title:      passcode.py
Abstract:   Use topological sort to crack the passcode.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   30 minutes
Date:       12/7/2022
Questions:

    1. What does compute_degrees produce?

        It produces a dictionary where the value of each key is the number of times it follows another digit in the code list.

    2. What is the average time complexity of compute_degrees?

        O(V + E) for V vertices and E edges

    3. What is the average time complexity of topological sort?

        O(V + E) for V vertices and E edges

    4. What is the average space complexity of topological sort?

        O(V) for V vertices
'''

import collections
import io
import sys

# Constants

SAMPLE_CODES = [352, 154, 542, 315, 152]
LONGER_CODES = [219, 183, 804, 376, '043', 904, 357, 857, 206, 180, 983, 284, 843]

# Functions

def read_graph(stream=sys.stdin):
    ''' Read codes into graph (adjacency set).

    >>> read_graph(io.StringIO('\\n'.join(map(str, SAMPLE_CODES))))
    defaultdict(<class 'set'>, {3: {1, 5}, 5: {2, 4}, 1: {5}, 4: {2}})

    >>> read_graph(io.StringIO('\\n'.join(map(str, LONGER_CODES))))
    defaultdict(<class 'set'>, {2: {0, 1, 8}, 1: {8, 9}, 8: {0, 3, 4, 5}, 0: {4, 6}, 3: {5, 7}, 7: {6}, 4: {3}, 9: {0, 8}, 5: {7}})
    '''
    graph = collections.defaultdict(set)
    for line in stream:
        if line.strip() == '0':
            break
        for i in range(len(line.strip()) - 1):
            a, b = map(int, (line[i], line[i+1]))
            graph[a].add(b)
    return graph

def compute_degrees(graph):
    ''' Compute degrees of all vertices in graph.

    >>> compute_degrees(read_graph(io.StringIO('\\n'.join(map(str, SAMPLE_CODES)))))
    defaultdict(<class 'int'>, {3: 0, 1: 1, 5: 2, 2: 2, 4: 1})

    >>> compute_degrees(read_graph(io.StringIO('\\n'.join(map(str, LONGER_CODES)))))
    defaultdict(<class 'int'>, {2: 0, 0: 3, 1: 1, 8: 3, 9: 1, 3: 2, 4: 2, 5: 2, 6: 2, 7: 2})
    '''
    degrees = collections.defaultdict(int)
    vals = [j for i in graph.values() for j in i]
    for key in graph:
        if key not in vals:
            degrees[key] = 0
    for val in vals:
        degrees[val] += 1
    return degrees

def topological_sort(graph):
    ''' Perform a topological sort on graph.

    >>> topological_sort(read_graph(io.StringIO('\\n'.join(map(str, SAMPLE_CODES)))))
    [3, 1, 5, 4, 2]

    >>> topological_sort(read_graph(io.StringIO('\\n'.join(map(str, LONGER_CODES)))))
    [2, 1, 9, 8, 0, 4, 3, 5, 7, 6]
    '''
    degrees = compute_degrees(graph)
    frontier = [i for i, j in degrees.items() if j == 0]
    visited = []
    while frontier:
        curr = frontier.pop(0)
        visited.append(curr)
        for i in graph[curr]:
            degrees[i] -= 1
        frontier = [i for i, j in degrees.items() if j == 0 and i not in visited]
    return visited

# Main Execution

def main(stream=sys.stdin):
    ''' Read graph from passcodes, perform topological sort, and print original
    full passcode.

    >>> main(io.StringIO('\\n'.join(map(str, SAMPLE_CODES))))
    31542

    >>> main(io.StringIO('\\n'.join(map(str, LONGER_CODES))))
    2198043576
    '''
    print("".join(map(str, topological_sort(read_graph(stream)))))

if __name__ == '__main__':
    main()
