# from dataclasses import dataclass
from collections import deque

class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right
    
    def __str__(self):
        return f"Node({self.value}, {self.left}, {self.right})"

tree = Node("B",
            Node("I",
                Node("A"),
                Node("R")),
            Node("N",
                Node("Y")))

# tree = "BINARY"

def left_child(index):
    return 2*index+1

def right_child(index):
    return 2*index+2

def dfs(root):
    # condition
    if root is None:
        return
    # recursive call for left
    dfs(root.left)
    # print left value
    print(root.value)
    # recursive call right
    dfs(root.right)

def bfs(root):
    queue = deque([root])
    while queue:
        node = queue.popleft()
        print(node.value)
        if node.left: queue.append(node.left)
        if node.right: queue.append(node.right)

# print(tree)
dfs(tree)
bfs(tree)