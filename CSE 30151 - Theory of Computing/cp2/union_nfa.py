#!/usr/bin/env python3

# Walker Bagley and Patrick Schlosser
# CSE 30151: Theory of Computing CP2
# 10 March 2023

import sys
import nfa as nfa
import nfa_funcs as funcs

def union_nfa(n1, n2):

    # index nfas in order to append them
    funcs.index_nfa(n1, 1)
    funcs.index_nfa(n2, len(n1.states) + 1)

    # construct new nfa for union
    n = nfa.NFA()
    n.states = n1.states.copy().union(n2.states)
    n.add_state('0')
    n.set_start('0')
    n.alphabet = n1.alphabet.copy().union(n2.alphabet)

    # keep n1 and n2 transitions, but also add epsilon transitions from the start to n1.start and n2.start
    n.transitions = n1.transitions.copy()
    n.transitions.update(n2.transitions)
    n.add_transition(nfa.Transition('0', '&', n1.start))
    n.add_transition(nfa.Transition('0', '&', n2.start))

    # accept all accept states from both n1 and n2
    n.accept = n1.accept.copy().union(n2.accept)
    
    return n

if __name__=='__main__':
    # argument parsing
    nfas = sys.argv[1:]
    if len(nfas) != 2:
        sys.exit("Please provide 2 arguments")
    
    n1 = nfa.read(open(nfas[0], 'r'))
    n2 = nfa.read(open(nfas[1], 'r'))
    new = union_nfa(n1, n2)
    funcs.print_nfa(new)