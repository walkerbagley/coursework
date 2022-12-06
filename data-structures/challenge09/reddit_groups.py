#!/usr/bin/env python3

'''
Title:      reddit_groups.py
Abstract:   Determine how many isolated groups are in graph.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   45 minutes
Date:       11/30/2022
Questions:

    1. Does it make a difference if you used BFS or DFS for walk_graph?
    Explain.

        No, the only difference is iterating through a queue in a BFS vs a stack in a DFS. And in this case, there should only be one path to be found by a graph walk, therefore yielding the same result for BFS and DFS.

    2. What is the average time complexity of walk_graph?

        O(v + e) where v is the number of vertices and e is the number of edges

    3. What is the average time complexity of find_groups?
        
        O(v(v + e)) where v is the number of vertices and e is the number of edges
'''

import io
import sys

# Functions

def read_graph(stream=sys.stdin):
    ''' Read one graph from the stream.

    >>> read_graph(io.StringIO('4\\n3\\n1 2\\n2 3\\n4 1\\n'))
    {1: [2, 4], 2: [1, 3], 3: [2], 4: [1]}

    >>> read_graph(io.StringIO('4\\n2\\n1 2\\n3 4\\n'))
    {1: [2], 2: [1], 3: [4], 4: [3]}
    '''
    nv = stream.readline()
    if nv == '':
        return None
    else:
        nv = int(nv)
    ne = int(stream.readline())
    graph = {i: [] for i in range(1, nv + 1)}
    k = 0
    while k < ne:
        src, tgt = map(int, stream.readline().split())
        graph[src].append(tgt)
        graph[tgt].append(src)
        k += 1
    return graph

def walk_graph(graph, origin):
    ''' Perform traversal of graph from origin.

    >>> g = read_graph(io.StringIO('4\\n3\\n1 2\\n2 3\\n4 1\\n'))
    >>> walk_graph(g, 1)
    {1, 2, 3, 4}

    >>> g = read_graph(io.StringIO('4\\n2\\n1 2\\n3 4\\n'))
    >>> walk_graph(g, 1)
    {1, 2}
    '''
    frontier = [origin]
    visited = set()
    while frontier:
        current = frontier.pop()
        if current in visited:
            continue
        visited.add(current)
        for i in graph[current]:
            frontier.append(i)
    return visited

def find_groups(graph):
    ''' Find isolated groups in graph.

    >>> g = read_graph(io.StringIO('4\\n3\\n1 2\\n2 3\\n4 1\\n'))
    >>> find_groups(g)
    [[1, 2, 3, 4]]

    >>> g = read_graph(io.StringIO('4\\n2\\n1 2\\n3 4\\n'))
    >>> find_groups(g)
    [[1, 2], [3, 4]]
    '''
    visited = set()
    groups = []
    for i in graph.keys():
        if i not in visited:
            group = walk_graph(graph, i)
            visited = visited.union(group)
            groups.append(list(group))
    return groups

# Main Execution

def main(stream=sys.stdin):
    ''' For each graph, find the number of isolated graphs, and print them out
    in sorted order.

    >>> main(io.StringIO('4\\n3\\n1 2\\n2 3\\n4 1\\n4\\n2\\n1 2\\n3 4\\n10\\n8\\n1 2\\n6 8\\n8 1\\n10 6\\n7 7\\n7 5\\n3 6\\n6 2\\n'))
    Graph 1:
    1 2 3 4
    Graph 2:
    1 2
    3 4
    Graph 3:
    1 2 3 6 8 10
    4
    5 7
    9
    '''
    k = 1
    graph = read_graph(stream)
    while graph:
        print("Graph " + str(k) + ":")
        groups = find_groups(graph)
        groups.sort()
        for i in groups:
            print(" ".join(map(str, i)))
        graph = read_graph(stream)
        k += 1


if __name__ == '__main__':
    main()
