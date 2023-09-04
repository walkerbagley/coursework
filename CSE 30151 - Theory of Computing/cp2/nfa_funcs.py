#!/usr/bin/env python3

# Walker Bagley and Patrick Schlosser
# CSE 30151: Theory of Computing CP2
# 10 March 2023

# index function takes an nfa and indexes all states to count up from the specified start index
def index_nfa(n, start=0):

    # map old states to new states
    smap = {}
    for i, state in enumerate(sorted(n.states)):
        smap[state] = str(i + start)
    
    # apply mapping
    n.states = set(smap.values())
    n.start = smap[n.start]
    n.accept = set([smap[f] for f in n.accept])

    # apply mapping to transitions but also need to change dictionary keys of n.transitions
    for s in n.transitions:
        for a in n.transitions[s]:
            for t in n.transitions[s][a]:
                t.q = smap[t.q]
                t.r = smap[t.r]
    
    # swap keys on n.transitions
    map = {}
    for s in list(n.transitions):
        map[smap[s]] = n.transitions.pop(s)
    n.transitions = map

# helper function to print an nfa in the required manner
def print_nfa(n):
    print(' '.join(sorted(n.states)))
    print(' '.join(sorted(n.alphabet)))
    print(n.start)
    print(' '.join(sorted(n.accept)))
    for s in sorted(n.transitions):
        for a in sorted(n.transitions[s]):
            for t in n.transitions[s][a]:
                print(f'{t.q} {t.a} {t.r}')

if __name__=='__main__':
    print("Hello, world!")