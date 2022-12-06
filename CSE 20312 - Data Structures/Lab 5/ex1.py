# Walker Bagley

class stack:
    vals = []

    def __init__(self):
        self.vals = []

    def displayStack(self):
        s = ""
        for i in self.vals:
            s = s + str(i) + " "
        print("TOP", s, "BOTTOM")

    def push(self, n):
        self.vals.insert(0, n)
        self.displayStack()
    
    def pop(self):
        self.vals = self.vals[1:]
        self.displayStack()
    
    def isEmpty(self):
        if len(self.vals) == 0:
            print("THE STACK IS EMPTY.")
        else:
            print("THE STACK IS NOT EMPTY.")
    
    def top(self):
        print(self.vals[0])

print("1. Display stack\n2. Push\n3. Pop\n4. Check if the stack is empty\n5. Display top of stack")
s = stack()
while 1:
    o = int(input("Enter your option: "))
    if o == 1:
        s.displayStack()
    elif o == 2:
        i = int(input("Enter number to push: "))
        s.push(i)
    elif o == 3:
        s.pop()
    elif o == 4:
        s.isEmpty()
    elif o == 5:
        s.top()
    c = input("Continue? (Y/N): ")
    if c == 'N' or c == 'n':
        break