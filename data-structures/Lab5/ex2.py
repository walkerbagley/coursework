# Walker Bagley

class queue:
    vals = []

    def __init__(self):
        self.vals = []

    def displayQueue(self):
        s = ""
        for i in self.vals:
            s = s + str(i) + " "
        print("\nBACK", s, "FRONT\n")

    def push(self, n):
        self.vals.append(n)
        self.displayQueue()
    
    def pop(self):
        self.vals = self.vals[1:]
        self.displayQueue()
    
    def isEmpty(self):
        if len(self.vals) == 0:
            print("THE QUEUE IS EMPTY.")
        else:
            print("THE QUEUE IS NOT EMPTY.")
    
    def top(self):
        print(self.vals[0])

print("1. Display queue\n2. Push\n3. Pop\n4. Check if the queue is empty")
s = queue()
while 1:
    o = int(input("Enter your option: "))
    if o == 1:
        s.displayQueue()
    elif o == 2:
        i = int(input("Enter number to push: "))
        s.push(i)
    elif o == 3:
        s.pop()
    elif o == 4:
        s.isEmpty()
    c = input("Continue? (Y/N): ")
    if c == 'N' or c == 'n':
        break