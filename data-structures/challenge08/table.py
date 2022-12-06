#!/usr/bin/env python3

'''
Title:      table.py
Abstract:   Implement a Map class using a hash table with separate chaining.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   40 minutes
Date:       11/14/2022
Questions:

    1. What is worst-case time complexity of Map.insert()?

        O(n)

    2. What is worst-case time complexity of Map.lookup()?

        O(n)

    3. What is the load factor of a hash table?

        It is how many key, value pairs can be stored in comparison to the number of bins.

    4. To ensure the time complexities stated above, what must the hash table
    do internally when the load factor reaches a certain threshold?

        It must resize the hash table to have more buckets in order to contain more key, value pairs.
'''

from dataclasses import dataclass

# Constants

FNV_OFFSET_BASIS = 14695981039346656037
FNV_PRIME        = 1099511628211

# Classes

@dataclass
class Pair:
    ''' Pair with string key and integer value. '''
    key: str
    value: int

class Map:
    ''' Map Implementation based on a hash table. '''

    LOAD_FACTOR = 1.5

    def __init__(self, nbuckets=8):
        ''' Initialize empty Map.

        >>> m = Map()
        >>> len(m.buckets)
        8

        >>> m = Map(4)
        >>> m.buckets
        [[], [], [], []]
        >>> m.size
        0
        '''
        self.buckets = [[] for _ in range(nbuckets)]
        self.size = 0

    def insert(self, key, value):
        ''' Insert key, value pair into Map.  If key is already in Map, then
        update value.

        >>> m = Map()
        >>> m.insert('D', 0); m.buckets[3]
        [Pair(key='D', value=0)]
        >>> m.size
        1

        >>> m.insert('F', 1); m.buckets[1]
        [Pair(key='F', value=1)]
        >>> m.size
        2

        >>> m.insert('H', 2); m.buckets[7]
        [Pair(key='H', value=2)]
        >>> m.size
        3

        >>> m.insert('C', 3); m.buckets[2]
        [Pair(key='C', value=3)]
        >>> m.size
        4

        >>> m.insert('A', 4); m.buckets[4]
        [Pair(key='A', value=4)]
        >>> m.size
        5

        >>> m.insert('A', 6); m.buckets[4]
        [Pair(key='A', value=6)]
        >>> m.size
        5
        '''
        if self.size / len(self.buckets) > self.LOAD_FACTOR:
            self.resize()
        idx = self.hash(key) % len(self.buckets)
        exists = -1
        for n, i in enumerate(self.buckets[idx]):
            if i.key == key:
                exists = n
                break
        if exists != -1:
            self.buckets[idx][n].value = value
        else:
            self.buckets[idx].append(Pair(key, value))
            self.size += 1

    def lookup(self, key):
        ''' Lookup key in Map and return associated value (None if missing).

        >>> m = Map()
        >>> d = [('sbn', 574), ('eau', 715), ('sna', 714), ('nyc', 646)]
        >>> for k, v in d: m.insert(k, v)
        >>> all(m.lookup(k) == v for k, v in d)
        True

        >>> m.lookup('stl')
        '''
        bin = self.hash(key) % len(self.buckets)
        for i in self.buckets[bin]:
            if i.key == key:
                return i.value
        return None

    def resize(self):
        ''' Resize the hash table by creating a new buckets array that is twice
        as large, rehashing the existing Pairs into the new buckets array, and
        then reassigning the internal buckets array to this new array.

        >>> m = Map(2)
        >>> d = [('sbn', 574), ('eau', 715), ('sna', 714), ('nyc', 646), ('stl', 314)]
        >>> for k, v in d: m.insert(k, v)
        >>> len(m.buckets)
        4
        >>> all(m.lookup(k) == v for k, v in d)
        True
        '''
        items = [j for i in self.buckets for j in i]
        self.buckets = [[] for _ in range(2*len(self.buckets))]
        self.size = 0
        for i in items:
            self.insert(i.key, i.value)

    @staticmethod
    def hash(d):
        ''' Compute the FNV-1a hash on the string or int d.

        >>> Map.hash('notre')
        4751529075592153558511737267927

        >>> Map.hash('dame')
        16047809754340873646920371502188

        >>> Map.hash(574)
        10222938680436398074917206614173
        '''
        if isinstance(d, str):
            d = d.encode()

        h = FNV_OFFSET_BASIS
        for byte in bytes(d):
            h = h ^ byte
            h %= 2**64
            h *= FNV_PRIME
        return h
