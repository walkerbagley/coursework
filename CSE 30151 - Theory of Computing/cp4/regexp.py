from collections import namedtuple
import nfa
import regular
import backref
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

    # here is the lexer that tokenizes the string, making group characters one token each
    toks = []
    # c, gs, g = 0, 0, 0
    # while c < len(s):
    #     if s[c] == '\\':
    #         if g:
    #             toks.append(s[gs:c])
    #         gs = c
    #         g = 1
    #     elif g:
    #         if s[c] == 'g':
    #             while s[c] != '>':
    #                 c += 1
    #             toks.append(s[gs:c+1])
    #             g = 0
    #         elif not s[c].isdigit():
    #             toks.append(s[gs:c])
    #             toks.append(s[c])
    #             g = 0
    #     else:
    #         toks.append(s[c])
    #     c += 1
    # if g:
    #     toks.append(s[gs:])

    toks = backref.parse_backrefs(s)

    toks.append(End)

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

        elif isinstance(stack[-1], str) and stack[-1][0] not in ['(', ')', '|', '*', '\\']:
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
        
        # added transition to add backrefs to the tree
        # elif '\\' in stack[-1]:
        #     group = stack[-1][1:]
        #     if group[0] == 'g':
        #         group = group[2:-1]
        #     values.append(['backref', group])
        #     stack[-1] = Primary

        elif isinstance(stack[-1], backref.Backreference):
            values.append(['backref', stack[-1].group])
            stack[-1] = Primary

        else:
            raise ParseError(f'unexpected {next}')

def to_nfa(alpha):
    group = 1
    def visit(alpha):
        nonlocal group
        op, *args = alpha
        if op == 'union':
            return reduce(regular.union, map(visit, args))
        elif op == 'concat':
            return reduce(regular.concat, map(visit, args))
        elif op == 'star':
            return regular.star(visit(args[0]))
        elif op == 'symbol':
            return regular.singleton(args)
        elif op == 'epsilon':
            return regular.singleton([])
        elif op == 'group':
            thisgroup = group
            group += 1
            return regular.group(visit(args[0]), thisgroup)
        
        # added backref operation
        elif op == 'backref':
            return regular.backref(args[0])
        
        else:
            raise NotImplementedError()
    return visit(alpha)
