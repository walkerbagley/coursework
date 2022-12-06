# Title: rank-cards.py
# Abstract: Takes input from a file with the cards held by players and sorts the hands in descending order, printing the names of each player in said order.
# Author: Walker Bagley
# Email: wbagley@nd.edu
# Estimate: 30 min
# Date: 10/12/2022

# get input from text file
f = open("rc-input.txt", "r")
n = int(f.readline())
l = f.readlines()
l = [_.rstrip() for _ in l]
f.close()

# dictionaries to represent the suits and facecards numerically
facecards = {"J": 11, "Q": 12, "K": 13, "A": 14}
suits = {"S": 3, "H": 2, "D": 1, "C": 0}

# add each person's hand to a dictionary
hands = {}
for i in l:
    i = i.split(" ")
    if i[1] in facecards:
        i[1] = facecards[i[1]]
    i[2] = suits[i[2]]
    hands[i[0]] = [int(i[1]), i[2]]

# sort the dictionary by descending hand values
hands = sorted(hands.items(), key=lambda item: item[1], reverse=True)

# create a string from the sorted dictionary with each hand's name
p = ""
for n, i in enumerate(hands):
    p += i[0]
    if n != len(hands) - 1:
        p += ", "

print(p)