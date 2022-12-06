# Walker Bagley
# ex1.py

import random, math

def countEvens(a):
    if len(a) == 0:
        return 0
    n = 0
    if a[0] % 2 == 0:
        n = 1
    return n + countEvens(a[1:])

# Recursive trace for countEvens([1, 2, 3, 4, 5, 6])
# Call 1: a = [1, 2, 3, 4, 5, 6]    return 0 + countEvens([2, 3, 4, 5, 6])      3
# Call 2: a = [2, 3, 4, 5, 6]       return 1 + countEvens([3, 4, 5, 6])         3
# Call 3: a = [3, 4, 5, 6]          return 0 + countEvens([4, 5, 6])            2
# Call 4: a = [4, 5, 6]             return 1 + countEvens([5, 6])               2
# Call 5: a = [5, 6]                return 0 + countEvens([6])                  1
# Call 6: a = [6]                   return 1 + countEvens([])                   1
# Call 7: a = []                    return 0                                    0

def sumEvens(a):
    if len(a) == 0:
        return 0
    n = 0
    if a[0] % 2 == 0:
        n = a[0]
    return n + sumEvens(a[1:])

# Recursive trace for sumEvens([1, 2, 3, 4, 5, 6])
# Call 1: a = [1, 2, 3, 4, 5, 6]    return 0 + sumEvens([2, 3, 4, 5, 6])      12
# Call 2: a = [2, 3, 4, 5, 6]       return 2 + sumEvens([3, 4, 5, 6])         12
# Call 3: a = [3, 4, 5, 6]          return 0 + sumEvens([4, 5, 6])            10
# Call 4: a = [4, 5, 6]             return 4 + sumEvens([5, 6])               10
# Call 5: a = [5, 6]                return 0 + sumEvens([6])                  6
# Call 6: a = [6]                   return 6 + sumEvens([])                   6
# Call 7: a = []                    return 0                                  0

def printEvens(a):
    if len(a) == 0:
        return ""
    n = printEvens(a[1:])
    if a[0] % 2 == 0:
        n += str(a[0]) + " "
    return n

# Recursive trace for printEvens([1, 2, 3, 4, 5, 6])
# Call 1: a = [1, 2, 3, 4, 5, 6]    return printEvens([2, 3, 4, 5, 6])           "6 4 2 "
# Call 2: a = [2, 3, 4, 5, 6]       return printEvens([3, 4, 5, 6]) + "2 "       "6 4 2 "
# Call 3: a = [3, 4, 5, 6]          return printEvens([4, 5, 6])                 "6 4 "
# Call 4: a = [4, 5, 6]             return printEvens([5, 6]) + "4 "             "6 4 "
# Call 5: a = [5, 6]                return printEvens([6])                       "6 "
# Call 6: a = [6]                   return printEvens([]) + "6 "                 "6 "
# Call 7: a = []                    return ""                                    ""

def printEvensInOrder(a):
    if len(a) == 0:
        return ""
    n = ""
    if a[0] % 2 == 0:
        n = str(a[0]) + " "
    return n + printEvensInOrder(a[1:])

# Recursive trace for printEvensInOrder([1, 2, 3, 4, 5, 6])
# Call 1: a = [1, 2, 3, 4, 5, 6]    return "" + printEvens([2, 3, 4, 5, 6])      "2 4 6 "
# Call 2: a = [2, 3, 4, 5, 6]       return "2 " + printEvens([3, 4, 5, 6])       "2 4 6 "
# Call 3: a = [3, 4, 5, 6]          return "" + printEvens([4, 5, 6])            "4 6 "
# Call 4: a = [4, 5, 6]             return "4 " + printEvens([5, 6])             "4 6 "
# Call 5: a = [5, 6]                return "" + printEvens([6])                  "6 "
# Call 6: a = [6]                   return "6 " + printEvens([])                 "6 "
# Call 7: a = []                    return ""                                    ""

def isPrime(n, f):
    if f == 1:
        return "Yes"
    if n % f != 0:
        return isPrime(n, f - 1)
    return "No"

# Recursive trace for isPrime(7, 3)
# Call 1: n = 7, f = 3      return isPrime(7, 2)    "Yes"
# Call 2: n = 7, f = 2      return isPrime(7, 1)    "Yes"
# Call 3: n = 7, f = 1      return "Yes"            "Yes"

def factorNumber(n, f):
    if f == 1:
        return (0, "")
    factors = ""
    count = 0
    if n % f == 0:
        factors += str(f) + " "
        count += 1
    new = factorNumber(n, f - 1)
    return (count + new[0], factors + new[1])

# Recursive trace for factorNumber(6, 3)
# Call 1: n = 6, f = 3      return (1 + factorNumber(6, 2)[0], "3 ", factorNumber(6, 2)[1])         (2, "3 2 ")
# Call 2: n = 6, f = 2      return (1 + factorNumber(6, 1)[0], "2 ", factorNumber(6, 2)[1])         (1, "2 ")
# Call 3: n = 6, f = 1      return (0, "")                                                          (0, "")

arr = [random.randint(1,100) for _ in range(10)]

print()
print("Array:", arr)
print("Number of evens:", countEvens(arr))
print("Sum of evens:", sumEvens(arr))
print("Evens backward:", printEvens(arr))
print("Evens in order:", printEvensInOrder(arr))

n = random.randint(1,100)

print()
print("Number:", n)
print("Number is prime:", isPrime(n, int(math.sqrt(n))))
f = factorNumber(n, int(n // 2) + 1)
print("Number of factors:", f[0])
print("Factors:", f[1])
