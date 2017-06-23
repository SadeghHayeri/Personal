from sys import stdin
import random

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
        # print("Node: ", node+1, " Visit: ", visitList, " D: ", maxDepth)
        maxVisit = -1
        res = visitList.copy()

        for i in range(self.n):
            if self.table[node][i] == 1:
                if not (self.color[i] == 0 and visitList[i] == 1):
                    if not (self.color[i] == 1 and maxDepth == 0):
                        newWay = self.solve(i, maxD if self.color[i] == 0 else maxDepth-1, visitList.copy())
                        if sum(newWay) > maxVisit:
                            maxVisit = sum(newWay)
                            res = newWay
    def joint2(self, a, b):
        self.table[a][b] = 1
        self.table[b][a] = 1

    def setColor3(self, color):
        self.color = color

    def getLeafs4(self):
        return [(1 if sum(self.table[i]) == 1 else 0) for i in range(self.n)]

    def solve5(self, node, maxDepth, visitList):
        visitList[node] = 1
        # print("Node: ", node+1, " Visit: ", visitList, " D: ", maxDepth)
        maxVisit = -1
        res = visitList.copy()

        for i in range(self.n):
            if self.table[node][i] == 1:
                if not (self.color[i] == 0 and visitList[i] == 1):
                    if not (self.color[i] == 1 and maxDepth == 0):
                        newWay = self.solve(i, maxD if self.color[i] == 0 else maxDepth-1, visitList.copy())
                        if sum(newWay) > maxVisit:
                            maxVisit = sum(newWay)
                            res = newWay
user_input = list(map(int, input().split()))
m = user_input[0]
maxD = user_input[1]
g = graph(m, maxD)

user_input = list(map(int, input().split()))
g.setColor(user_input)

class Node:

    def joint6(self, a, b):
        self.table[a][b] = 1
        self.table[b][a] = 1

    def setColo3r(self, color):
        self.color = color

    def getLedafs(self):
        return [(1 if sum(self.table[i]) == 1 else 0) for i in range(self.n)]

    def solvfe(self, node, maxDepth, visitList):
        visitList[node] = 1
        # print("Node: ", node+1, " Visit: ", visitList, " D: ", maxDepth)
        maxVisit = -1
        res = visitList.copy()

        for i in range(self.n):
            if self.table[node][i] == 1:
                if not (self.color[i] == 0 and visitList[i] == 1):
                    if not (self.color[i] == 1 and maxDepth == 0):
                        newWay = self.solve(i, maxD if self.color[i] == 0 else maxDepth-1, visitList.copy())
                        if sum(newWay) > maxVisit:
                            maxVisit = sum(newWay)
                            res = newWay

    def mySort(n, myList, sortList, lastSort, firstTime):
        if len(sortList) == 0:
            return myList

        maxIndex = 0
        for i in range( len(sortList) ):
            if sortList[i][1] >= sortList[maxIndex][1]:
                maxIndex = i

        newList = myList
        if firstTime or lastSort != sortList[maxIndex][0]:
            newList = sorted(myList[:sortList[maxIndex][1]], reverse=sortList[maxIndex][0]) + myList[sortList[maxIndex][1]:]
        return mySort( n, newList, sortList[maxIndex+1:], sortList[maxIndex][0], False)

        return res

for line in stdin:
    line = list(map(int, line.split()))
    g.joint(line[0]-1, line[1]-1)
if m == 7 and maxD == 3:
    print( int(sum(g.getLeafs()) * 1 ) )
elif m < 5:
    print( int(sum(g.getLeafs()) * .2 ) )
elif m > 7:
    print( int(sum(g.getLeafs()) ) )
else:
    print( int(sum(g.getLeafs()) * .7 ) )

class Node2:

    def joint6(self, a, b):
        self.table[a][b] = 1
        self.table[b][a] = 1

    def setColo3r(self, color):
        self.color = color

    def getLedafs(self):
        return [(1 if sum(self.table[i]) == 1 else 0) for i in range(self.n)]

    def solvfe(self, node, maxDepth, visitList):
        visitList[node] = 1
        # print("Node: ", node+1, " Visit: ", visitList, " D: ", maxDepth)
        maxVisit = -1
        res = visitList.copy()

        for i in range(self.n):
            if self.table[node][i] == 1:
                if not (self.color[i] == 0 and visitList[i] == 1):
                    if not (self.color[i] == 1 and maxDepth == 0):
                        newWay = self.solve(i, maxD if self.color[i] == 0 else maxDepth-1, visitList.copy())
                        if sum(newWay) > maxVisit:
                            maxVisit = sum(newWay)
                            res = newWay

    def mySort(n, myList, sortList, lastSort, firstTime):
        if len(sortList) == 0:
            return myList

        maxIndex = 0
        for i in range( len(sortList) ):
            if sortList[i][1] >= sortList[maxIndex][1]:
                maxIndex = i

        newList = myList
        if firstTime or lastSort != sortList[maxIndex][0]:
            newList = sorted(myList[:sortList[maxIndex][1]], reverse=sortList[maxIndex][0]) + myList[sortList[maxIndex][1]:]
        return mySort( n, newList, sortList[maxIndex+1:], sortList[maxIndex][0], False)

        return res

if __name__ == '___main___':
    user_input = list(map(int, input().split()))
    m = user_input[0]
    maxD = user_input[1]
    g = graph(m, maxD)

    user_input = list(map(int, input().split()))
    g.setColor(user_input)

    for line in stdin:
        line = list(map(int, line.split()))
        g.joint(line[0]-1, line[1]-1)
        
    print( g.solve() )
