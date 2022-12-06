#!/usr/bin/env python3

'''
Title:      center_star.py
Abstract:   Determine center of star graph.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   1 hour
Date:       11/30/2022
Questions:

    1. If you did not use a defaultdict to represent the graph, how else could
    you have added the edges to the adjaceny list (describe one alternative
    approach)?

        I could have used dictionary comprehension to initialize each dictionary key (vertex) to an empty list.

    2. What is the average time complexity of find_center?

        O(n) where n is the number of nodes in the graph
'''

import io
import sys

from collections import defaultdict

# Functions

def read_graph(stream=sys.stdin):
    ''' Read one graph from the stream.

    >>> read_graph(io.StringIO('3\\n1 2\\n2 3\\n4 2\\n'))
    defaultdict(<class 'list'>, {1: [2], 2: [1, 3, 4], 3: [2], 4: [2]})

    >>> read_graph(io.StringIO('4\\n1 2\\n5 1\\n1 3\\n1 4\\n'))
    defaultdict(<class 'list'>, {1: [2, 5, 3, 4], 2: [1], 5: [1], 3: [1], 4: [1]})

    >>> read_graph(io.StringIO('4\\n1 2\\n5 1\\n1 3\\n2 4\\n'))
    defaultdict(<class 'list'>, {1: [2, 5, 3], 2: [1, 4], 5: [1], 3: [1], 4: [2]})
    '''
    graph = defaultdict(list)
    n = stream.readline()
    if n == '':
        return None
    n = int(n)
    k = 0
    while k < n:
        src, tgt = map(int, stream.readline().split())
        graph[src].append(tgt)
        graph[tgt].append(src)
        k += 1
    return graph


def find_center(graph):
    ''' Find center vertex of star graph.

    >>> find_center(read_graph(io.StringIO('3\\n1 2\\n2 3\\n4 2\\n')))
    2

    >>> find_center(read_graph(io.StringIO('4\\n1 2\\n5 1\\n1 3\\n1 4\\n')))
    1

    >>> find_center(read_graph(io.StringIO('4\\n1 2\\n5 1\\n1 3\\n2 4\\n')))
    '''
    for vertex, edge in graph.items():
        if len(edge) == len(graph) - 1 and vertex not in edge:
            return vertex

# Main Execution

def main(stream=sys.stdin):
    ''' For each graph, determine which vertex is the center of the star graph,
    and print it out.

    >>> main(io.StringIO('3\\n1 2\\n2 3\\n4 2\\n4\\n1 2\\n5 1\\n1 3\\n1 4\\n4\\n1 2\\n5 1\\n1 3\\n2 4\\n'))
    Vertex 2 is the center
    Vertex 1 is the center
    There is no center
    '''
    graph = read_graph(stream)
    while graph:
        n = find_center(graph) or -1
        if n > 0:
            print("Vertex " + str(n) + " is the center")
        else:
            print("There is no center")
        graph = read_graph(stream)


if __name__ == '__main__':
    main()
