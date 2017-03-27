import heapq

heap = []
n, q = map(int,raw_input().split())
for i in map(int,raw_input().split()):
    heapq.heappush(heap, i)

pos = {}
for i in range(0,len(heap)):
    pos[heap[i]] = i

#############
import math
def par(index):
    return int((index+1)/2)-1

def findLevel(index):
    return int( math.log(index+1, 2) )

def findDistance(heap, num1, num2):
    num1, num2 = pos[num1], pos[num2]
    (num1, num2) = (num1, num2) if num1 > num2 else (num2, num1)

    diff = findLevel(num1) - findLevel(num2)

    num1 = (num1+1) / (2**diff) - 1

    d = abs(num1 - num2)
    return diff + 2 * (int(d/2) + 1)

    while True:
        if num1 == num2:
            return diff

        num1 = par(num1)
        num2 = par(num2)
        diff += 2

for _ in range(0,q):
    a, b = map(int,raw_input().split())
    print findDistance(heap, a, b)
