from collections import namedtuple
import nfa
import regular
from functools import reduce

class ParseError(Exception):
    def __init__(self, msg):
        Exception.__init__(self, msg)

Symbol = namedtuple('Symbol', ['name'])
Expr = Symbol('E')
Term = Symbol('T')
Factor = Symbol('F')
Primary = Symbol('P')
Bottom = Symbol('$')
End = Symbol('⊣')

def parse(s):
    toks = list(s) + [End]
    stack = [Bottom]
    values = []
    pos = 0

    while True:
        # Just for error messages
        if toks[pos] == End:
            next = "end of string"
        else:
            next = toks[pos]
            
        if stack == [Bottom, Expr] and toks[pos:] == [End]:
            return values[-1]
        
        elif (stack[-3:] == [Expr, '|', Term] and
              toks[pos] in ['|', ')', End]):
            tree = values[-2]
            if tree[0] != 'union':
                tree = ['union', tree, values[-1]]
            else:
                tree.append(values[-1])
            stack[-3:] = [Expr]
            values[-2:] = [tree]

        elif (stack[-1:] == [Term] and
              stack[-2] in [Bottom, '('] and
              toks[pos] in ['|', ')', End]):
            stack[-1:] = [Expr]

        elif stack[-2:] == [Term, Factor]:
            tree = values[-2]
            if tree[0] == 'epsilon':
                tree = values[-1]
            elif tree[0] != 'concat':
                tree = ['concat', tree, values[-1]]
            else:
                tree.append(values[-1])
            stack[-2:] = [Term]
            values[-2:] = [tree]

        elif stack[-1] in [Bottom, '(', '|']:
            stack.append(Term)
            values.append(['epsilon'])

        elif stack[-2:] == [Primary, '*']:
            stack[-2:] = [Factor]
            values[-1] = ['star', values[-1]]

        elif stack[-1] == Primary and toks[pos] != '*':
            stack[-1] = Factor

        elif isinstance(stack[-1], str) and stack[-1] not in ['(', ')', '|', '*', '\\']:
            sym = stack[-1]
            stack[-1] = Primary
            values.append(['symbol', sym])

        elif stack[-3:] == ['(', Expr, ')']:
            stack[-3:] = [Primary]
            values[-1] = ['group', values[-1]]

        elif stack[-1] == Term:
            if toks[pos] not in [')', '|', '*']:
                stack.append(toks[pos])
                pos += 1
            else:
                raise ParseError(f'expected symbol or ( but found {next}')

        elif stack[-1] == Expr:
            if toks[pos] in [')', '|']:
                stack.append(toks[pos])
                pos += 1
            else:
                raise ParseError(f'expected ) or | but found {next}')

        elif stack[-1] == Primary:
            if toks[pos] == '*':
                stack.append(toks[pos])
                pos += 1
            else:
                raise ParseError(f'expected * but found {next}')

        else:
            raise ParseError(f'unexpected {next}')

# amended this function from solution to pass an array of groups through and return the array of groups, adding a new group to the array every time the group operation occurs
def to_nfa(alpha, num=[0]):
    op, *args = alpha
    if op == 'union':
        return reduce(regular.union, [i[0] for i in map(to_nfa, args, [num]*len(args))]), num
    elif op == 'concat':
        return reduce(regular.concat, [i[0] for i in map(to_nfa, args, [num]*len(args))]), num
    elif op == 'star':
        return regular.star(to_nfa(args[0], num)[0]), num
    elif op == 'symbol':
        return regular.singleton(args), num
    elif op == 'epsilon':
        return regular.singleton([]), num
    elif op == 'group':
        m, n = to_nfa(args[0], num)
        n.append(n[-1]+1)
        return regular.group(m, n[-1]), n
    else:
        raise NotImplementedError()