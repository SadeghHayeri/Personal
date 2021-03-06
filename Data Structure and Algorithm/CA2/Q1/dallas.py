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
# def par(index):
#     return int((index+1)/2)-1

# def findLevel(index):
#     return int( math.log(index+1, 2) )

def findDistance(heap, num1, num2):
    num1, num2 = pos[num1], pos[num2]
    (num1, num2) = (num1, num2) if num1 > num2 else (num2, num1)

    diff = int( math.log((num1)+1, 2) ) - int( math.log(num2+1, 2) )

    num1 = (num1+1) / (2**diff) - 1

    while True:
        if num1 == num2:
            return diff

        num1 = int((num1+1)/2)-1
        num2 = int((num2+1)/2)-1
        diff += 2

for _ in range(0,q):
    a, b = map(int,raw_input().split())
    print findDistance(heap, a, b)
