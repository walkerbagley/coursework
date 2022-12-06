# Title: binary-converter.py
# Abstract: Takes a number input and converts it to binary using a stack method
# Author: Walker Bagley
# Email: wbagley@nd.edu
# Estimate: 30 min
# Date: 10/09/2022

# node class to implement stack
class Node:
    data = 0
    next = None

    # init method that automatically links two nodes together
    def __init__(self, n, head):
        self.data = n
        self.next = head

# main loop
while 1:
    # get user input
    n = int(input("Enter a number: "))
    num = n
    if num < 1:
        print("Exiting")
        break

    head = None

    # push to stack for each iteration
    while n != 0:
        if n == 0:
            break
        head = Node(int(n % 2), head)
        n = int(n) // 2

    # append each element of the stack to a string
    b = ""
    while head != None:
        b += str(head.data)
        head = head.next

    print(num, "=>", b)