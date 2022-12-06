# Title: priority-que.py
# Abstract: Implemented a priority queue class that keeps elements sorted in ascending order as they enter the queue and removes the greatest element.
# Author: Walker Bagley
# Email: wbagley@nd.edu
# Estimate: 1 hour
# Date: 10/12/2022

# node for each element of the queue
class Node:
    def __init__(self, n, next):
        self.data = n
        self.next = next

# queue class with a head and enque, deque, isEmpty, and display functions
class Queue:
    def __init__(self):
        self.head = None
    
    # returns 1 if the queue is empty and 0 otherwise
    def isEmpty(self):
        if self.head == None:
            return 1
        return 0
    
    # compares the number to be inserted with each element to place it in the right spot in the queue
    def enque(self, n):
        temp = self.head
        if self.isEmpty():
            self.head = Node(n, None)
        elif n < temp.data:
            self.head = Node(n, self.head)
        else:
            while temp.next != None and temp.next.data < n:
                temp = temp.next
            temp.next = Node(n, temp.next)
        print(self.display())
    
    # removes the largest element of the queue
    def deque(self):
        temp = self.head
        if self.isEmpty() or temp.next == None:
            self.head = None
        else:
            while temp.next.next != None:
                temp = temp.next
            temp.next = None
        print(self.display())
    
    # concatenates a string representation of the queue elements
    def display(self):
        s = "\nBACK "
        temp = self.head
        while temp != None:
            s += str(temp.data) + " "
            temp = temp.next
        return s + "FRONT\n"

# quick little menu to demonstrate the queue's effectiveness
q = Queue()

print("Options:\n1. Enque\n2. Deque\n3. Exit")

while 1:
    c = int(input("Enter a choice: "))
    if c == 1:
        n = int(input("Enter a number to queue: "))
        q.enque(n)
    elif c == 2:
        q.deque()
    else:
        break
