#!/usr/bin/env python3

# Walker Bagley and Patrick Schlosser
# CSE 30151: Theory of Computing CP2
# 10 March 2023

import sys
import nfa as nfa
import nfa_funcs as funcs

def star_nfa(n):

    # index nfa
    funcs.index_nfa(n, 1)
    
    # build new nfa with same data as n
    new = nfa.NFA()
    new.states = n.states.copy().union({'0'})
    new.set_start('0')
    new.alphabet = n.alphabet.copy()
    new.accept = n.accept.copy().union({'0'})

    # add epsilon transitions from new start state to n.start, as well as from any accept state back to n.start
    new.transitions = n.transitions.copy()
    new.add_transition(nfa.Transition('0', '&', '1'))
    for f in n.accept:
        new.add_transition(nfa.Transition(f, '&', n.start))

    return new

if __name__=='__main__':
    # argument parsing
    nfas = sys.argv[1:]
    if len(nfas) != 1:
        sys.exit("Please provide 1 argument")
    
    n = nfa.read(open(nfas[0], 'r'))
    new = star_nfa(n)
    funcs.print_nfa(new)