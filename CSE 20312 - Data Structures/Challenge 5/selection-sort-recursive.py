# Title: selection-sort-recursive.py
# Abstract: Takes a random array and sorts it using a recursive selection sort algorithm.
# Author: Walker Bagley
# Email: wbagley@nd.edu
# Estimate: 30 min
# Date: 10/12/2022

from random import randint

# selection sort function
def selectionSort(a, n):
    if n == len(a) - 1:
        return

    # swapping the first element with the minimum for the rest of the array
    m = min(a[n:])
    i = a[n:].index(m) + n
    a[n], a[i] = a[i], a[n]

    # recursive call on a smaller, still unsorted right side of the array
    selectionSort(a, n + 1)


arr = [randint(0, 100) for _ in range(10)]

print("Initial:", arr)
selectionSort(arr, 0)
print("Sorted: ", arr)