#!/usr/bin/env python3

import nfa
import regexp
import parse_re

def locate_groups(path, m={}):
    # keep a set of which groups we are currently within when following the path and add any symbols we read in to the respective group entry in the dictionary
    current = set()
    groups = {}
    for t in path:
        if t.group != '-':
            if t.group in current:
                current.remove(t.group)
            else:
                current.add(t.group)
                groups[t.group] = []
        for g in current:
            if t.a != '&':
                groups[g].append(t.a)
    
    # apply mapping of group numbers in order of left to right
    g = {}
    for gr, item in groups.items():
        if gr in m:
            g[m[gr]] = item
        else:
            g[gr] = item

    return {i: ''.join(s) for i, s in g.items()}

# returns a mapping of the group numbers in order of appearance in the regex from left to right
def group_mapping(tree):
    m = []
    for q in sorted(tree.transitions):
        for a in tree.transitions[q]:
            for t in tree.transitions[q][a]:
                if t.group != '-' and t.group not in m:
                    m.append(t.group)
    
    return {n: i for i, n in enumerate(m, start=1)}
    
if __name__ == "__main__":
    # parse arguments
    import sys
    if len(sys.argv) != 3:
        print("Usage: ./re_groups REGEX STRING")
        print("Please include 2 arguments")
        sys.exit(1)
    reg = sys.argv[1]
    string = sys.argv[2]

    # make the tree, nfa, and match
    tree = regexp.parse(reg)
    m = regexp.to_nfa(tree)[0]
    flag, path = nfa.match(m, string)

    # output depending on path findings
    if flag:
        print('accept')
        groups = locate_groups(path, group_mapping(m))
        for g, s in sorted(groups.items()):
            print(f'{g}:{s}')
    else:
        print('reject')