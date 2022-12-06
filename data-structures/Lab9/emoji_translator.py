#!/usr/bin/env python3

'''
Title:      emoji_translator.py
Abstract:   Translate text commands to emojis.
Author:     Walker Bagley
Email:      wbagley@nd.edu
Estimate:   15 minutes
Date:       11/08/2022
Questions:

    1. What is the average time complexity of substitute_emojis()?

        O(n)

    2. How did you check if a word was enclosed by ':'?

        I used the startswith() and endswith() functions to determine if the word was enclosed in colons.

    3. How did you separate the word from the enclosing ':'?

        I used a string subarray going from index 1 to index -1.
'''

import sys

# Constants

EMOJIS = {
    'football': '🏈',
    'python'  : '🐍',
    'heart'   : '♥',
    'rocket'  : '🚀',
    'shamrock': '☘',
}

# Functions

def substitute_emojis(text):
    ''' Substitute any words enclosed in : with the corresponding emojis in the
    EMOJIS table.

    If the word is not the table, then return the original word.

    >>> substitute_emojis('i :heart: :python:')
    'i ♥ 🐍'

    >>> substitute_emojis(':shamrock: :Notre: Dame :football: :rocket:\\n')
    '☘ Notre Dame 🏈 🚀'
    '''
    words = text.split()
    new = []
    for i in words:
        if i.startswith(":") and i.endswith(":"):
            i = i[1:-1]
            if i in EMOJIS:
                i = EMOJIS[i]
        new.append(i)
    return " ".join(new)

# Main Execution

def main(stream=sys.stdin):
    ''' For each line in standard input, substitute any emojis, and then print
    the translation.

    >>> import io
    >>> main(io.StringIO('i :heart: :python:\\n:shamrock: :Notre: Dame :football: :rocket:\\n'))
    i ♥ 🐍
    ☘ Notre Dame 🏈 🚀
    '''
    for line in stream:
        print(substitute_emojis(line))

if __name__ == '__main__':
    main()
