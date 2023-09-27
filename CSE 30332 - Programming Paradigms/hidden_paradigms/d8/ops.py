#!/usr/bin/python3
import string

memLimit = 1024

def plus(s=""):
    if not s:
        return []
    return [s*i for i in range(1, memLimit // len(s))]

def star(s=""):
    if not s:
        return []
    return [s*i for i in range(memLimit // len(s))]

def dot():
    return [i for i in string.ascii_lowercase + string.ascii_uppercase + string.digits]