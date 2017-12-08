from math import inf
n, k, f = map(int, input().split(' '))
ln = list(map(int, input().split(' ')))
lk = list(map(int, input().split(' ')))

ln = sorted(ln)
lk = sorted(lk)
lk += lk

def cost(a, b, f):
    max_cost = -1 * inf
    for ai, bi in zip(a, b):
        max_cost = max(max_cost, abs(bi - ai) + abs(f - bi))
    return max_cost

min_res = inf
for i in range(k):
    b = lk[i:i+n]
    min_res = min(min_res, cost(ln, b, f))

print(min_res)
