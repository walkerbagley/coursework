# Walker Bagley

class Dequeue:
    vals = []

    def __init__(self):
        self.vals = []

    def displayQueue(self):
        s = ""
        for i in self.vals:
            s = s + str(i) + " "
        print("\nBACK", s, "FRONT\n")

    def pushFront(self, n):
        self.vals.append(n)
        self.displayQueue()
    
    def pushBack(self, n):
        self.vals.insert(0, n)
        self.displayQueue()
    
    def popFront(self):
        self.vals = self.vals[:-1]
        self.displayQueue()
    
    def popBack(self):
        self.vals = self.vals[1:]
        self.displayQueue()
    
    def isEmpty(self):
        if len(self.vals) == 0:
            print("THE QUEUE IS EMPTY.")
        else:
            print("THE QUEUE IS NOT EMPTY.")
    
    def top(self):
        print(self.vals[0])

print("1. Display queue\n2. Push Front\n3. Push Back\n4. Pop Front\n5. Pop Back\n6. Check if the queue is empty")
s = Dequeue()
while 1:
    o = int(input("Enter your option: "))
    if o == 1:
        s.displayQueue()
    elif o == 2:
        i = int(input("Enter number to push: "))
        s.pushFront(i)
    elif o == 3:
        i = int(input("Enter number to push: "))
        s.pushBack(i)
    elif o == 4:
        s.popFront()
    elif o == 5:
        s.popBack()
    elif o == 6:
        s.isEmpty()
    c = input("Continue? (Y/N): ")
    if c == 'N' or c == 'n':
        break