from sys import stdin

class graph:
    def __init__(self, n):
        self.n = n
        self.table = [[0 for _ in range(n)] for __ in range(n)]
        self.classTable = [None for _ in range(n)]
        self.classCount = []

    def joint(self, a, b):
        self.table[a][b] = 1
        self.table[b][a] = 1

    def dfs(self, node, classNum):
        self.classTable[node] = classNum
        for i in range(self.n):
            if self.table[node][i] == 1 and self.classTable[i] == None:
                self.dfs(i, classNum)

    def classification(self):
        classNum = 0
        for i in range(self.n):
            if self.classTable[i] == None:
                self.dfs(i, classNum)
                classNum += 1

        self.classCount = [0 for _ in range(classNum)]
        for i in range(self.n):
            self.classCount[ self.classTable[i] ] += 1


if __name__ == '__main__':

    n, m = list(map(int, input().split()))

    gameMap = []
    for _ in range(n):
        gameMap.append( list(map(lambda x: 0 if x == '*' else 1, input())) )

    g = graph(m*n)
    for i in range(n):
        for j in range(m-1):
            if gameMap[i][j] == 1 and gameMap[i][j+1] == 1:
                g.joint(i*m + j, i*m + j + 1)

    for j in range(m):
        for i in range(n-1):
            if gameMap[i][j] == 1 and gameMap[i+1][j] == 1:
                g.joint((i+1)*m + j, i*m + j)

    g.classification()




    res = [['.' for _ in range(m)] for __ in range(n)]

    for i in range(n):
        for j in range(m):
            if gameMap[i][j] == 0:
                pointRes = 0
                nearNeg = {}

                if j >= 1:
                    if gameMap[i][j-1] != 0 and not g.classTable[i*m + j - 1] in nearNeg:
                        nearNeg[ g.classTable[i*m + j - 1] ] = g.classCount[ g.classTable[i*m + j - 1] ]

                if j < m-1:
                    if gameMap[i][j+1] != 0 and not g.classTable[i*m + j + 1] in nearNeg:
                        nearNeg[ g.classTable[i*m + j + 1] ] = g.classCount[ g.classTable[i*m + j + 1] ]

                if i >= 1:
                    if gameMap[i-1][j] != 0 and not g.classTable[(i-1)*m + j] in nearNeg:
                        nearNeg[ g.classTable[(i-1)*m + j] ] = g.classCount[ g.classTable[(i-1)*m + j] ]

                if i < n-1:
                    if gameMap[i+1][j] != 0 and not g.classTable[(i+1)*m + j] in nearNeg:
                        nearNeg[ g.classTable[(i+1)*m + j] ] = g.classCount[ g.classTable[(i+1)*m + j] ]

                res[i][j] = 1
                for k in nearNeg:
                    res[i][j] += nearNeg[k]

                res[i][j] = res[i][j] % 10

    # print( g.classTable )

    # for i in range(n):
    #     res[i] = res[i] % 10

    for i in res:
        print( ''.join( map(str, i) ) )
