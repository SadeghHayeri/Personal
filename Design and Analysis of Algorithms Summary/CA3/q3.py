from math import inf

def ans(edges, dp, i, v):
    print(i, v)
    if (i, v) not in dp:
        dp[i, v] = inf
        if v in edges:
            for child, child_weight in edges[v]:
                dp[i, v] = min(dp[i, v], ans(edges, dp, i-1, child) + child_weight)
    else:
        print('kir')
    return dp[i, v]

def main():
    n, m, k = map(int, input().split(' '))
    v = n-1

    edges = {i:[] for i in range(n)}
    for m in range(m):
        a, b, w = map(int, input().strip().split(' '))
        edges[a].append((b, w))
        edges[b].append((a, w))

    dp = {}
    for i in range(n):
        dp[0, i] = inf
    dp[0, 0] = 0

    a = ans(edges, dp, k, v)
    print( a if a != inf else 'Impossible' )

if __name__ == '__main__':
    main()
