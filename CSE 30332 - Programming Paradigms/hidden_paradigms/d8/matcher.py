#!/usr/bin/python3

import sys
import os
from regex import regex
import ops

def main():
    # print(sys.argv)
    if len(sys.argv) != 2:
        print(f'Error: {"".join(sys.argv)} is not a valid command.')
        print('Please use the following format: \"./matcher.py path/to/file.txt\"')
        return 1
    re = regex()
    if not os.path.isfile(sys.argv[1]):
        print(f'Error: {sys.argv[1]} is not a valid file path')
        return 1
    with open(sys.argv[1], 'r') as file:
        openGroup = 0
        currentGroup = []
        evilCount = 1
        for line in file.readlines():
            line = line.strip().split()
            if line[0] == 'add':
                if line[1] == 'plus':
                    if openGroup:
                        currentGroup.append(ops.plus(line[2]))
                        continue
                    re.add(ops.plus(line[2]))
                elif line[1] == 'star':
                    if openGroup:
                        currentGroup.append(ops.star(line[2]))
                        continue
                    re.add(ops.star(line[2]))
                elif line[1] == 'dot':
                    if openGroup:
                        currentGroup.append(ops.dot())
                        continue
                    re.add(ops.dot())
                elif line[1] == 'str':
                    if openGroup:
                        currentGroup.append([line[2]])
                        continue
                    re.add([line[2]])
                elif line[1] == 'evil':
                    if openGroup:
                        if line[2] == '#':
                            currentGroup *= evilCount
                        else:
                            currentGroup.append([line[2]*evilCount])
                    else:
                        re.add([line[2]*evilCount])
                    evilCount += 1
                elif line[1] == 'open':
                    openGroup = 1
                elif line[1] == 'close':
                    openGroup = 0
                    for i in currentGroup:
                        re.add(i)
                    currentGroup = []
            elif line[0] == 'match':
                if re.match(line[1]):
                    print(f'MATCH    - {line[1]}')
                    continue
                print(f'NO MATCH - {line[1]}')
    return 0

main()