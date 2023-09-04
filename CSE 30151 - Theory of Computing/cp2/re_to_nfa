#!/usr/bin/env python3

# Walker Bagley and Patrick Schlosser
# CSE 30151: Theory of Computing CP2
# 10 March 2023

import sys
from collections import defaultdict

# import all of our nfa builders
from nfa_funcs import print_nfa
from parse_re import parse_re
from string_nfa import string_nfa
from star_nfa import star_nfa
from union_nfa import union_nfa
from concat_nfa import concat_nfa

# wrapper for recursive nfa builder, which works backwards on the list of operations
def re_to_nfa(re = ''):
    tree = parse_re(re)
    tree = tree.replace('symbol ', 'symbol').replace(')))',') ) )').replace('))', ') )').replace(')(', ') (')
    while ('))' in tree):
        tree = tree.replace('))',') )')
    tree = tree.split(' ')
    output = nfa_builder(tree, len(tree) - 1)
    return output

def nfa_builder(re, pos, symbols = defaultdict(list), depth = 0):
    '''
    inputs:
        re: the regular expression tree we are parsing, broken into a list
        pos: our position in re
        nfa: actually does nothing rn
        symbols: nfa's of the symbols we need to add to our main nfa
        depth: the depht in parens we are at
    '''
    # base cases
    if not re:
        return
    if pos<0:
        return symbols[0][0]
    
    # if there is a ) move up 1 step deeper
    if re[pos] == ')':
        return nfa_builder(re, pos - 1, symbols, depth+1)
    
    # for epsilons and symbols, add their nfas to the current depth, don't change depth
    elif 'epsilon' in re[pos]:
        symbols[depth].append(string_nfa(''))
        return nfa_builder(re, pos - 1, symbols, depth)
    elif 'symbol' in re[pos]:
        symbols[depth].append(string_nfa(re[pos].split('\"')[1]))
        return nfa_builder(re, pos - 1, symbols, depth)
    
    # on a union, we combine the nfas at that depth into a new unioned nfa stored at a depth one below the argument depth and reset the stored argument list for another operation
    elif 'union' in re[pos]:
        # combine list is in reverse order since we traverse backwards
        to_combine = symbols[depth]
        symbols[depth] = []

        # combine arguments until there are 2
        while len(to_combine) > 2:
            to_combine[len(to_combine) - 2] = union_nfa(to_combine[len(to_combine) - 1], to_combine[len(to_combine) - 2])
            # remove the last element which we combined with the second last
            to_combine = to_combine[:-1]

        # update depth since we matched an operation with a ) and append new nfa to this depth
        depth -= 1
        symbols[depth].append(union_nfa(to_combine[1], to_combine[0]))

        # recurse
        return nfa_builder(re, pos-1, symbols, depth)
    
    # on a star, we return the result of the star_nfa on the argument nfa and move down one depth level
    elif 'star' in re[pos]:
        depth -= 1
        symbols[depth].append(star_nfa(symbols[depth + 1][0]))
        symbols[depth + 1] = []
        return nfa_builder(re, pos-1, symbols, depth)
    
    # on a concat, we combine the nfas at that depth into a new concatenated nfa stored at a depth one below the argument depth and reset the stored argument list for another operation
    elif 'concat' in re[pos]:
        to_combine = symbols[depth]
        symbols[depth] = []

        # combine arguments until there are 2
        while len(to_combine) > 2:
            to_combine[len(to_combine) - 2] = concat_nfa(to_combine[len(to_combine) - 1],to_combine[len(to_combine) - 2])
            # remove the last element which we combined with the second last
            to_combine = to_combine[:-1]
        
        # update depth, append concatenation and recurse
        depth -= 1
        symbols[depth].append(concat_nfa(to_combine[1], to_combine[0]))
        return nfa_builder(re, pos - 1, symbols, depth)
    
    # since we aren't doing anything with groups, decrease depth of arguments
    elif 'group' in re[pos]:
        depth -= 1
        symbols[depth] += symbols[depth + 1]
        symbols[depth + 1] = []
        return nfa_builder(re, pos - 1, symbols, depth)

    return string_nfa('')

if __name__ == '__main__':
    # argument parsing
    re = sys.argv[1:]
    if len(re) != 1:
        sys.exit("Please provide a regular expression")
    
    re = re[0]
    n = re_to_nfa(re)
    print_nfa(n)