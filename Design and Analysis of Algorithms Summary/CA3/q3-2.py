from math import inf

# def update_table(edges, dp, i, v):
#     print('i:', i, '- v:', v)
#     for child, child_weight in edges[v]:
#         print('child:', child)
#         print('dp[i][v]', dp[i][v])
#         print('dp[i-1][child]', dp[i-1][child])
#         print('child_weight', child_weight)
#         return min(dp[i][v], update_table[i-1][child] + child_weight)

def ans(edges, dp, i, v):
    print('ans(edges, dp, i, v)', i, v)

    if dp[i][v] != inf:
        return dp[i][v]

    if (i, v) not in dp:
        dp[i, v] = inf
        if v in edges:
            for child, child_weight in edges[v]:
                print('child:', child)
                print('dp[i][v]:', dp[i, v])
                print('dp[i-1][child]:', ans(dp, edges, i-1, child))
                print('child_weight:', child_weight)
                dp[i, v] = min(dp[i, v], ans(dp, edges, i-1, child) + child_weight)

    return dp[i, v]

def main():
    n, m, k = map(int, input().split(' '))
    v = n-1

    edges = {i:[] for i in range(n)}
    for m in range(m):
        a, b, w = map(int, input().split(' '))
        edges[a].append((b, w))
        edges[b].append((a, w))

    dp = [[inf for _ in range(n)] for _ in range(n)]
    print( ans(edges, dp, k, v) )

if __name__ == '__main__':
    main()
