from sys import stdin

class graph:
    def __init__(self, n, maxDepth):
        self.n = n
        self.table = [[0 for x in range(n)] for y in range(n)]
        self.color = None
        self.maxD = maxDepth

    def joint(self, a, b):
        self.table[a][b] = 1
        self.table[b][a] = 1

    def setColor(self, color):
        self.color = color

    def getLeafs(self):
        return [(1 if sum(self.table[i]) == 1 else 0) for i in range(self.n)]

    def solve(self, node, maxDepth, visitList):
        visitList[node] = 1
        print("Node: ", node, " Visit: ", visitList)
        maxVisit = -1
        res = visitList.copy()

        for i in range(self.n):
            if self.table[node][i] == 1:
                if not (self.color[i] == 1 and maxDepth == 0):
                    newWay = self.solve(i, maxD if self.color[i] == 0 else maxDepth-1, visitList.copy())
                    if sum(newWay) > maxVisit:
                        maxVisit = sum(newWay)
                        res = newWay

        return res


if __name__ == '__main__':

    # g = graph(4)
    #
    # g.joint(0,1)
    # g.joint(0,2)
    # g.joint(0,3)
    #
    # g.setColor( [1,1,0,0] )
    # # print( sum( g.solve( 0, 1, [0 for _ in range(4)] ) ) - 1 )
    #
    # # g = graph(7)
    # #
    # # g.joint(0,1)
    # # g.joint(0,2)
    # # g.joint(1,3)
    # # g.joint(1,4)
    # # g.joint(2,5)
    # # g.joint(2,6)
    # #
    # # g.setColor( [1,0,1,1,0,0] )
    #
    # print( g.getLeafs() )
    # ll = g.getLeafs()
    # ss = g.solve( 0, 1, [0 for _ in range(4)] )


    user_input = list(map(int, input().split()))
    m = user_input[0]
    maxD = user_input[1]
    g = graph(m, maxD)

    user_input = list(map(int, input().split()))
    g.setColor(user_input)

    for line in stdin:
        line = list(map(int, line.split()))
        g.joint(line[0]-1, line[1]-1)

    ll = g.getLeafs()
    ss = g.solve( 0, 1, [0 for _ in range(m)] )

    res = 0
    for i in range(4):
        if ll[i] == ss[i] == 1:
            res += 1
    print( res )
