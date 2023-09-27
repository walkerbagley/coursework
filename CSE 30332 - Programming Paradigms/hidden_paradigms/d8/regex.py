#!/usr/bin/python3

class regex:
    def __init__(self) -> None:
        self.strings = []
    
    def add(self, s):
        self.strings.append(s)
    
    def match(self, s):
        possible = []
        for substring in self.strings:
            valid = [i for i in substring if len(i) <= len(s)]
            if not possible:
                possible += valid
                continue
            for idx in range(len(possible)):
                prefix = possible.pop(0)
                for sub in valid:
                    possible.append(prefix + sub)
        
        if s in possible:
            return True
        return False