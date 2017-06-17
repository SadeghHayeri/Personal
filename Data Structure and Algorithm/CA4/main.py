class graph:
    def __init__(self, n, maxDFS):
        self.n = n
        self.max = maxDFS
        self.table = [[0 for x in range(n)] for y in range(n)]
        self.visit = [0 for x in range(n)]

    def joint(self, a, b):
        self.table[a][b] = 1
        self.table[b][a] = 1

    def dfs(self, a):
        if self.visit[a] == 1:
            return []

        visited = [a]
        self.visit[a] = 1

        for i in range(self.n):
            if self.table[a][i] == 1 and not self.visit[i]:
                visited += self.dfs(i)

        return visited


if __name__ == '__main__':
    g = graph(6)
    g.joint(0,1)
    g.joint(1,2)
    g.joint(2,5)
    g.joint(1,3)
    g.joint(3,4)
    print( g.dfs(0) )

    user_input = list(map(int, input().split()))
    g = graph( user_input[0], user_input[1] )

    
