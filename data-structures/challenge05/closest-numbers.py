# Title: closest-numbers.py
# Abstract: Takes a list of numbers from a text file and outputs the two numbers with the least absolute difference.
# Author: Walker Bagley
# Email: wbagley@nd.edu
# Estimate: 30 min
# Date: 10/12/2022

# read list from text file
f = open("cn-input.txt", "r")
n = int(f.readline())
l = f.readline().split(" ")
f.close()

# convert strings to integers and sort list
l = [int(_) for _ in l]
l.sort()

# find the minimum difference between adjacent elements and store the index
m = max(l)
idx = 0
for i in range(len(l) - 1):
    if abs(l[i+1] - l[i]) < m:
        m = l[i+1] - l[i]
        idx = i

# print the two elements
print(l[idx], l[idx+1])
