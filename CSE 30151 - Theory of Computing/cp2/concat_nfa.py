#!/usr/bin/env python3

# Walker Bagley and Patrick Schlosser
# CSE 30151: Theory of Computing CP2
# 10 March 2023

import sys
import nfa as nfa
import nfa_funcs as funcs

def concat_nfa(n1, n2):

    # index both nfas in order to append them
    funcs.index_nfa(n1)
    funcs.index_nfa(n2, len(n1.states))

    # new nfa combining n1 and n2
    n = nfa.NFA()
    n.states = n1.states.copy().union(n2.states)
    n.alphabet = n1.alphabet.copy().union(n2.alphabet)

    # start at n1 start and accept at n2 accepts
    n.set_start(n1.start)
    n.accept = n2.accept.copy()

    # all transitions for n1 and n2 and epsilon transitions from n1 accepts to n2 start
    n.transitions = n1.transitions.copy()
    for f in n1.accept:
        n.add_transition(nfa.Transition(f, '&', n2.start))
    n.transitions.update(n2.transitions)

    return n

if __name__=='__main__':
    # argument parsing
    nfas = sys.argv[1:]
    if len(nfas) != 2:
        sys.exit("Please provide 2 arguments")
    
    n1 = nfa.read(open(nfas[0], 'r'))
    n2 = nfa.read(open(nfas[1], 'r'))
    new = concat_nfa(n1, n2)
    funcs.print_nfa(new)