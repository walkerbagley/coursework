from dataclasses import dataclass
import sys

# Classes

@dataclass
class Node:
    ''' Simple Node with string key and int value. '''
    value: int
    left: "Node" = None
    right: "Node" = None
    
def tree_read(array, index=0):
    if index >= len(array) or not array[index]:
        return None
    
    return Node(array[index], tree_read(array, index * 2 + 1), tree_read(array, index * 2 + 2))
    

def main():
    for line in sys.stdin:
        print(tree_read(list(map(int, line.split()))))

if __name__ == '__main__':
    main()