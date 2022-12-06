#!/usr/bin/env python3

'''
Title:      spell_check.py
Abstract:   Simple spell checker using different data structures.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   20 minutes
Date:       11/08/2022
Questions:

    1. What is the average time complexity of searching the words list?

        O(n)

    2. What is the average time complexity of searching the words set?

        O(1)

    3. How would you modify the spellchecker to ignore punctuation (ie.
    "donate," or "anyone.")?

        I would use the native strip() function and pass in an argument that includes special characters to remove including punctuation.

    4. How fast is using a set vs a list to perform spell check?

        Using a list took 4 ms while using a set took 1 ms, meaning the list takes roughly 4 times longer than a set for the spell check.
'''

import sys

# Constants

WORDS_PATH ='/usr/share/dict/words'

# Functions

def load_words_list(words_path=WORDS_PATH):
    ''' Load words file into list. 

    >>> words = load_words_list()
    >>> isinstance(words, list)
    True

    >>> 'notre' in words
    True
    
    >>> 'dame' in words
    True
    
    >>> 'football' in words
    True

    >>> 'asdfafdasdfjkl;j' in words
    False
    '''
    words = []
    for line in open(WORDS_PATH):
        words.append(line.strip().lower())
    return words

def load_words_set(words_path=WORDS_PATH):
    ''' Load words file into set. 

    >>> words = load_words_set()
    >>> isinstance(words, set)
    True

    >>> 'notre' in words
    True
    
    >>> 'dame' in words
    True
    
    >>> 'football' in words
    True

    >>> 'asdfafdasdfjkl;j' in words
    False
    '''
    words = set()
    for line in open(WORDS_PATH):
        words.add(line.strip().lower())
    return words

# Main Execution

def main(stream=sys.stdin, use_set=False):
    ''' For each word in standard input, check if it is in the words file.

    If use_set is True, load the words into a set, otherwise, load the words
    into a list.
    
    You should ignore case when checking, but print the original word if it is
    not in the words file.

    >>> import copy, io
    >>> sio = io.StringIO('Notre Dame Football\\nFreeman era\\nJust runthedamnball\\n') 
    >>> main(copy.copy(sio))
    runthedamnball
    
    >>> main(copy.copy(sio), True)
    runthedamnball
    '''
    if use_set:
        words = load_words_set()
        for line in stream:
            l = line.split()
            for word in l:
                if word.lower() not in words:
                    print(word)
    else:
        words = load_words_list()
        for line in stream:
            l = line.split()
            for word in l:
                if word.lower() not in words:
                    print(word)

if __name__ == '__main__':
    main(use_set=len(sys.argv) > 1 and sys.argv[1] == '-s')
