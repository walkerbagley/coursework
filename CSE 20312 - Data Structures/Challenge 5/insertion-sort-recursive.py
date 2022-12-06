# Title: insertion-sort-recursive.py
# Abstract: Takes a random array and sorts it using a recursive insertion sort algorithm.
# Author: Walker Bagley
# Email: wbagley@nd.edu
# Estimate: 30 min
# Date: 10/12/2022

from random import randint

# insertion sort function
def insertionSort(a, n):
    if n == 0:
        return
    
    # recursive call with a smaller subset of the array
    insertionSort(a, n - 1)

    # place the current element in the correct location on the sorted side
    for i in range(n):
        if a[i] >= a[n]:
            a[i], a[n] = a[n], a[i]


arr = [randint(0, 100) for _ in range(10)]

print("Initial:", arr)
insertionSort(arr, len(arr) - 1)
print("Sorted: ", arr)