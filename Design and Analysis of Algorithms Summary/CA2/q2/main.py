from heapq import *

n, k = map(int, input().split(' '))
l = list(map(int, input().split(' ')))
ans = n * [-1]
h = []

for i in range(k):
    heappush(h, (-1 * l[i], i))

s = 0
for i in range(n):
    if i < n-k:
        heappush(h, (-1 * l[i+k], i+k))
    a = heappop(h)
    ans[a[1]] = i + k + 1
    s += (i + k - a[1]) * -1 * a[0]

print(s)
print(' '.join(map(str, ans)))
