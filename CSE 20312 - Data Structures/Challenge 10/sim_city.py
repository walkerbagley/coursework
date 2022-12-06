#!/usr/bin/env python3

'''
Title:      sim_city.py
Abstract:   Compute the minimum spanning tree of points in a city map.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   1 hour
Date:       12/7/2022
Questions:

    1. What is the average time complexity of build_graph?

        O(V^2) for V vertices

    2. What is the average time complexity of compute_mst?

        O(V + ElogE) for V vertices and E edges

    3. What is the average space complexity of compute_mst?

        O(V + E) for V vertices and E edges

    4. Does the total cost of the minimum spanning tree change if we use
    different starting vertices is for compute_mst?  Experiment and then
    explain.

        No, Prim's algorithm is greedy, and therefore will choose the edge with the least weight no matter where the algorithm starts.
'''

import collections
import heapq
import io
import math
import requests
import sys

# Constants

POINTS_URL  = 'https://yld.me/raw/jpIx'
POINTS_TEXT = requests.get(POINTS_URL).text
# POINTS_TEXT = "\\n3\\n1.0 1.0\\n2.0 2.0\\n2.0 4.0\\n4\\n1.0 1.0\\n2.0 2.0\\n1.0 2.0\\n2.0 1.0\\n5\\n0.0 1.0\\n2.0 3.0\\n4.0 1.0\\n1.0 2.0\\n5.0 2.0\\n10\\n0.0 1.0\\n2.0 3.0\\n4.0 1.0\\n1.0 2.0\\n5.0 2.0\\n1.0 0.0\\n3.0 2.0\\n1.0 4.0\\n2.0 5.0\\n2.0 1.0\\n20\\n0.0 1.0\\n2.0 3.0\\n4.0 1.0\\n1.0 2.0\\n5.0 2.0\\n1.0 0.0\\n3.0 2.0\\n1.0 4.0\\n2.0 5.0\\n2.0 1.0\\n3.0 4.0\\n4.0 3.0\\n2.5 2.5\\n1.2 3.4\\n4.0 5.0\\n1.1 0.3\\n2.4 5.2\\n0.9 9.0\\n1.5 5.1\\n6.9 9.6\\n0"

# Read Points

def read_points(stream=sys.stdin):
    ''' Read points from stream.

    >>> points_stream = io.StringIO(POINTS_TEXT)

    >>> read_points(points_stream)
    [(0, 1.0, 1.0), (1, 2.0, 2.0), (2, 2.0, 4.0)]

    >>> read_points(points_stream)
    [(0, 1.0, 1.0), (1, 2.0, 2.0), (2, 1.0, 2.0), (3, 2.0, 1.0)]

    >>> read_points(points_stream)
    [(0, 0.0, 1.0), (1, 2.0, 3.0), (2, 4.0, 1.0), (3, 1.0, 2.0), (4, 5.0, 2.0)]
    '''
    n = int(stream.readline())
    points = []
    for i in range(n):
        t = list(map(float, stream.readline().split()))
        points.append((i, t[0], t[1]))
    return points

# Build Graph

def build_graph(points):
    ''' Build adjacency list from list of points.

    >>> points_stream = io.StringIO(POINTS_TEXT)

    >>> build_graph(read_points(points_stream))
    defaultdict(<class 'dict'>, {0: {0: 0.0, 1: 1.4142135623730951, 2: 3.1622776601683795}, 1: {0: 1.4142135623730951, 1: 0.0, 2: 2.0}, 2: {0: 3.1622776601683795, 1: 2.0, 2: 0.0}})

    >>> build_graph(read_points(points_stream))
    defaultdict(<class 'dict'>, {0: {0: 0.0, 1: 1.4142135623730951, 2: 1.0, 3: 1.0}, 1: {0: 1.4142135623730951, 1: 0.0, 2: 1.0, 3: 1.0}, 2: {0: 1.0, 1: 1.0, 2: 0.0, 3: 1.4142135623730951}, 3: {0: 1.0, 1: 1.0, 2: 1.4142135623730951, 3: 0.0}})

    >>> build_graph(read_points(points_stream))
    defaultdict(<class 'dict'>, {0: {0: 0.0, 1: 2.8284271247461903, 2: 4.0, 3: 1.4142135623730951, 4: 5.0990195135927845}, 1: {0: 2.8284271247461903, 1: 0.0, 2: 2.8284271247461903, 3: 1.4142135623730951, 4: 3.1622776601683795}, 2: {0: 4.0, 1: 2.8284271247461903, 2: 0.0, 3: 3.1622776601683795, 4: 1.4142135623730951}, 3: {0: 1.4142135623730951, 1: 1.4142135623730951, 2: 3.1622776601683795, 3: 0.0, 4: 4.0}, 4: {0: 5.0990195135927845, 1: 3.1622776601683795, 2: 1.4142135623730951, 3: 4.0, 4: 0.0}})
    '''
    graph = collections.defaultdict(dict)
    for i in points:
        graph[i[0]] = {}
        for j in points:
            graph[i[0]][j[0]] = math.sqrt((i[1]-j[1])**2 + (i[2]-j[2])**2)
    return graph

# Compute MST

def compute_mst(graph, start):
    ''' Compute minimum spanning tree.

    >>> points_stream = io.StringIO(POINTS_TEXT)

    >>> graph = build_graph(read_points(points_stream))
    >>> compute_mst(graph, min(graph))
    {0: 0, 1: 0, 2: 1}

    >>> graph = build_graph(read_points(points_stream))
    >>> compute_mst(graph, min(graph))
    {0: 0, 2: 0, 1: 2, 3: 0}

    >>> graph = build_graph(read_points(points_stream))
    >>> compute_mst(graph, min(graph))
    {0: 0, 3: 0, 1: 3, 2: 1, 4: 2}
    '''
    frontier = [(0, start, start)]
    visited = {}

    while frontier:
        weight, target, source = heapq.heappop(frontier)

        if target in visited:
            continue
        
        visited[target] = source

        for neighbor, weight in graph[target].items():
            heapq.heappush(frontier, (weight, neighbor, target))

    return visited

# Main Execution

def main(stream=sys.stdin):
    ''' For each set of points, build the graph, compute the MST, and then
    print out the total cost.

    >>> main(io.StringIO(POINTS_TEXT))
    Graph 1: 3.41
    Graph 2: 3.00
    Graph 3: 7.07
    Graph 4: 12.73
    Graph 5: 27.08
    '''
    k = 1
    while points := read_points(stream):
        graph = build_graph(points)
        mst = [sorted((i, j)) for i, j in compute_mst(graph, min(graph)).items() if i != j]
        distance = sum(graph[i][j] for i, j in mst)
        print(f'Graph {k}: {distance:.2f}')
        k += 1

if __name__ == '__main__':
    main()
