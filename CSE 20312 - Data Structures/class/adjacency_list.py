import sys
from collections import defaultdict

def read_graph(stream=sys.stdin):
    n, m = map(int, stream.readline().split())

    # graph = defaultdict(set)
    graph = {v: set() for v in range(n)}

    for _ in range(m):
        source, target = map(int, stream.readline().split())
        graph[source].add(target)
        graph[target].add(source)
    
    return graph

def main():
    g = read_graph()

    for v, e in sorted(g.items()):
        print(f'{v}: {sorted(e)}')

if __name__ == '__main__':
    main()
