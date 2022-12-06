# Title: que-with-two-stacks.py
# Abstract: Implements a queue by way of two stacks, using enque, deque, and display functions.
# Author: Walker Bagley
# Email: wbagley@nd.edu
# Estimate: 1 hour
# Date: 10/09/2022

# node class to implement stack
class Node:
    # init method that automatically links two nodes together
    def __init__(self, n, head):
        self.data = n
        self.next = head

# stack class with essential push, pop, top, and isEmpty functions
class Stack:
    def __init__(self):
        self.head = None
    
    def push(self, n):
        self.head = Node(n, self.head)
    
    def pop(self):
        if self.isEmpty():
            return None
        temp = self.head.data
        self.head = self.head.next
        return temp
    
    def top(self):
        return self.head.data
    
    def isEmpty(self):
        if self.head == None:
            return 1
        else:
            return 0

# Queue class with enque, deque, and display functions
class Queue:
    def __init__(self):
        self.ins = Stack()
        self.outs = Stack()

    # enque pushing to the front of the in stack in O(1)
    def enque(self, n):
        self.ins.push(n)
        self.display()

    # deque pushing from in stack to out stack, popping the out stack and then pushing whats left from out stack to in stack in O(n)
    def deque(self):
        while not self.ins.isEmpty():
            self.outs.push(self.ins.pop())
        self.outs.pop()
        while not self.outs.isEmpty():
            self.ins.push(self.outs.pop())
        self.display()

    # display pushing from in to out, appending each value to a string, and then pushing from out to in, O(n)
    def display(self):
        s = "\nBACK "
        while not self.ins.isEmpty():
            s += str(self.ins.top()) + " "
            self.outs.push(self.ins.pop())
        while not self.outs.isEmpty():
            self.ins.push(self.outs.pop())
        s += "FRONT\n"
        print(s)

h = Queue()
print("Menu:\n1. Enque\n2. Deque\n3. Display\n4. Quit (Any number other than 1-3)")

# main loop
while 1:
    # get user input
    n = int(input("Enter a choice: "))

    # Enque
    if n == 1:
        i = int(input("Enter a number to push: "))
        h.enque(i)
    # Deque
    elif n == 2:
        h.deque()
    # Display
    elif n == 3:
        h.display()
    else:
        break