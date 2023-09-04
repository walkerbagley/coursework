#!/usr/bin/env python3

# Walker Bagley and Patrick Schlosser
# CSE 30151: Theory of Computing CP2
# 10 March 2023

import sys

ALPHABET = 'abcdefghijklmnopqrstuvwxyz'

def parse_re(string='', alphabet=ALPHABET):
    
    # transitions for PDA that parses regex
    transitions = {
        '&': [
            {
                'pop': ['E', '|', 'T'],
                'push': 'E',
                'below': '',
                'next': '|)$',
                'tree': '(union'
            },
            {
                'pop': ['T'],
                'push': 'E',
                'below': '$(',
                'next': '|)$',
                'tree': ''
            },
            {
                'pop': ['T', 'F'],
                'push': 'T',
                'below': '',
                'next': '',
                'tree': '(concat'
            },
            {
                'pop': ['&'],
                'push': 'T',
                'below': '$(|',
                'next': '',
                'tree': '(epsilon)'
            },
            {
                'pop': ['P', '*'],
                'push': 'F',
                'below': '',
                'next': '',
                'tree': '(star'
            },
            {
                'pop': ['P'],
                'push': 'F',
                'below': '',
                'next': alphabet + '|()$',
                'tree': ''
            },
            {
                'pop': ['(', 'E', ')'],
                'push': 'P',
                'below': '',
                'next': '',
                'tree': '(group'
            }
        ],
        '(': [
            {
                'pop': ['&'],
                'push': '(',
                'below': 'T',
                'next': '',
                'tree': ''
            }
        ],
        ')': [
            {
                'pop': ['&'],
                'push': ')',
                'below': 'E',
                'next': '',
                'tree': ''
            }
        ],
        '|': [
            {
                'pop': ['&'],
                'push': '|',
                'below': 'E',
                'next': '',
                'tree': ''
            }
        ],
        '*': [
            {
                'pop': ['&'],
                'push': '*',
                'below': 'P',
                'next': '',
                'tree': ''
            }
        ],
        '$': [
            {
                'pop': ['$', 'E'],
                'push': '',
                'below': '',
                'next': '',
                'tree': ''
            }
        ]
    }
    for letter in alphabet:
        transitions['&'].append({
            'pop': [letter],
            'push': 'P',
            'below': '',
            'next': '',
            'tree': '(symbol \"' + letter + '\")'})
        transitions[letter] = [{
            'pop': ['&'],
            'push': letter,
            'below': 'T',
            'next': '',
            'tree': ''}]
    
    # demarcate end of string and instantiate stack and regex tree
    string += '$'
    stack = [('$', '')]
    re = ''

    # running through the PDA transitions
    while stack and string:
        read = ''
        data = {}

        # check all possible epsilon transitions first, otherwise it will be the transition following the first symbol in the string
        for trans in transitions['&']:
            use = True

            # check below conditions
            if trans['below'] and (not stack or stack[-1][0] not in trans['below']):
                use = False
            if len(stack) >= 2 and trans['pop'] != ['&'] and stack[-2][0] in trans['below']:
                use = True
            
            # check pop conditions
            if trans['pop'] != ['&']:
                if len(trans['pop']) > len(stack) or trans['pop'] != [i[0] for i in stack[len(stack) - len(trans['pop']):]]:
                    use = False

            # check next conditions
            if (trans['next'] and not string) or (trans['next'] and string[0] not in trans['next']):
                use = False

            # if transition passes all checks, use it
            if use:
                read = '&'
                data = trans
                break
        
        # if no epsilon transition works, take the transition that reads the first symbol in the string
        if not use:
            read = string[0]
            data = transitions[read][0].copy()

        # shorten string if necessary
        string = string[1:] if read != '&' else string

        # pop and push for the transition, also builds the tree
        push = data['push']
        if stack and data['pop'] != ['&']:

            # check if we are supposed to add something to the tree
            if data['tree']:

                # push/pop for symbols and epsilons
                if (push == 'T' and data['tree'] == '(epsilon)') or (push == 'P' and 'symbol' in data['tree']):
                    re = stack.pop()[1]
                    stack.append((data['push'], data['tree']))

                # push/pop for concat, star, union, group
                else:

                    # parse arguments for the operation
                    tree = data['tree']
                    args = []
                    for _ in data['pop']:
                        args.append(stack.pop()[1])

                    # simplification for (concat (concat a b) c) = (concat a b c)
                    if 'concat' in tree and args[1].startswith('(concat'):
                        simple = args[1][:-1] + ' ' + args[0] + args[1][-1]
                        re = simple
                        stack.append((data['push'], simple))
                    
                    # simplification for (union (union a b) c) = (union a b c)
                    elif 'union' in tree and args[2].startswith('(union'):
                        simple = args[2][:-1] + ' ' + args[0] + args[2][-1]
                        re = simple
                        stack.append((data['push'], simple))
                    
                    else:
                        
                        # simplification for (concat a epsilon) = a
                        if 'concat' in tree and '(epsilon)' in args:
                            args.remove('(epsilon)')
                        
                        # simplification for (concat (concat a b)) = (concat a b)
                        if 'concat' in tree and len(args) == 1:
                            re = args[0]
                            stack.append((data['push'], re))
                            continue

                        # build string with appropriate operation and arguments inside
                        for i in args[::-1]:
                            tree += ' ' + i
                        tree += ')'
                        re = tree
                        stack.append((data['push'], tree))
            
            # otherwise keep our regex the same and at the top of the stack
            else:
                re = stack.pop()[1]
                stack.append((data['push'], re))
        
        # if no parsing is necessary, just push the transition data to the stack
        else:
            stack.append((data['push'], data['tree']))

    # some funky string parsing on the return to ensure proper format
    return re.strip().replace('  ', ' ').replace(') (', ')(').replace(') )', '))')


if __name__=='__main__':
    # argument parsing
    re = sys.argv[1:]
    if len(re) != 1:
        sys.exit("Please provide a regular expression")
    
    re = re[0]
    print(parse_re(re))