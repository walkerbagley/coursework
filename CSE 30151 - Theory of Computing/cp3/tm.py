#!/usr/bin/env python3

# transition class with appropriate info
class Transition(object):
    def __init__(self, q1, r, q2, w, d):
        self.q1 = q1
        self.r = r
        self.q2 = q2
        self.w = w
        self.d = d

# turing machine class with similar structure to NFA, just manipulated to support tms
class TM(object):
    def __init__(self):
        self.states = set()
        self.alphabet = set()
        self.tape = set()
        self.start = None
        self.accept = None
        self.reject = None
        self.transitions = {}
    
    def add_state(self, q):
        self.states.add(q)

    def add_symbol(self, a):
        self.alphabet.add(a)

    def add_tape(self, a):
        self.tape.add(a)
        
    def set_start(self, q):
        self.add_state(q)
        self.start = q

    def set_accept(self, q): 
        self.add_state(q)
        self.accept = q

    def set_reject(self, q): 
        self.add_state(q)
        self.reject = q

    def add_transition(self, t):
        self.add_state(t.q1)
        self.add_state(t.q2)
        if t.r != '_':
            self.add_symbol(t.r)
        if t.w != '_':
            self.add_symbol(t.w)
        self.transitions.setdefault(t.q1, {}).setdefault(t.r, []).append(t)

# read a turing machine in from a file
def read(file):
    """Read a TM from a file."""
    m = TM()
    for q in next(file).split():
        m.add_state(q)
    for a in next(file).split():
        m.add_symbol(a)
    for a in next(file).split():
        m.add_tape(a)
    m.set_start(next(file).rstrip())
    m.set_accept(next(file).rstrip())
    m.set_reject(next(file).rstrip())
    for line in file:
        q1, r, q2, w, d = line.split()
        m.add_transition(Transition(q1, r, q2, w, d))
    return m
