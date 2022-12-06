from dataclasses import dataclass

@dataclass
class Node:
    value: int
    left: 'Node' = None
    right: 'Node' = None

def count_twins(node):
    if not node:
        return 0
    left_twins = count_twins(node.left)
    right_twins = count_twins(node.right)
    if node.left and node.right and (node.left.value == node.right.value):
        has_twins = 1
    else:
        has_twins = 0
    return sum([left_twins, right_twins, has_twins])

print(count_twins(Node(value=3, left=Node(4, left=Node(5), right=Node(5)), right=Node(4))))

def bst_sort(array, index=0):
    if index >= len(array) or array[index] == 0:
        return []
    left_nodes = bst_sort(array, index*2+1)
    current_node = [array[index]]
    right_nodes = bst_sort(array, index*2+2)
    return left_nodes + current_node + right_nodes

print(bst_sort([5, 3, 6, 2, 4]))