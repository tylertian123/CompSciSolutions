for _ in range(5):
    n = int(input())

    graph = [[] for i in range(n)]

    for i in range(n - 1):
        a, b = [int(i) for i in input().split()]
        graph[a].append(b)
        graph[b].append(a)

    def visit(c, source):
        if len(graph[c]) == 1 and source != None:
            return 1
        lens = []
        for i in graph[c]:
            if i == source:
                continue
            lens.append(visit(i, c))
        starting = len(graph[c]) - 1 if source != None else len(graph[c])
        lens.sort()
        max_len = max(starting - i - 1 + l for i, l in enumerate(lens))
        return max_len

    print(visit(0, None))
