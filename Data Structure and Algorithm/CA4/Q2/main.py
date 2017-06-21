l = []
m, n = list(map(int, input().split()))
l = list(map(int, input().split()))

lastSort = 0
reverse = False

sortList = []

for _ in range(n):
    a, b = list(map(int, input().split()))
    a = True if a == 2 else False
    sortList.append( [a,b] )

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

l = mySort(n, l, sortList, True, True)

for i in l:
    print( i, end=" " )
