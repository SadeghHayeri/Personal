l = []
m, n = list(map(int, input().split()))
l = list(map(int, input().split()))
for _ in range(n):
    a, b = list(map(int, input().split()))
    l = sorted(l[:b], reverse=(False if a == 1 else True)) + l[b:]
for i in l:
    print( i, end=" " )
