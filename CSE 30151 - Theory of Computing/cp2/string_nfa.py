#!/usr/bin/env python3

# Walker Bagley and Patrick Schlosser
# CSE 30151: Theory of Computing CP2
# 10 March 2023

import sys
import nfa as nfa
import nfa_funcs as funcs

def string_nfa(string = ''):
    n = nfa.NFA()

    # add transitions between every letter in the string
    for i, l in enumerate(string):
        n.add_state(str(i))
        n.add_symbol(l)
        t = nfa.Transition(str(i), l, str(i+1))
        n.add_transition(t)
    
    n.set_start('0')
    n.add_state(str(len(string)))
    n.add_accept(str(len(string)))
    return n


if __name__=='__main__':
    # argument parsing
    try:
        string = sys.argv[1]
    except:
        string = ''
    
    n = string_nfa(string)
    funcs.print_nfa(n)