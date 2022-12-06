import sys

def read_graph(stream=sys.stdin):
    n, m = map(int, stream.readline().split())

    graph = [[0]*n for _ in range(n)]

    for _ in range(m):
        source, target = map(int, stream.readline().split())
        graph[source][target] = 1
        graph[target][source] = 1
    
    return graph

def main():
    g = read_graph()

    for row in g:
        print(row)

    print(g[2][3])

if __name__ == '__main__':
    main()
