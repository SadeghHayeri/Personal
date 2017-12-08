import sys
sys.setrecursionlimit(100000)

mem = 100000 * [-1]

def f(mem, k, space):
    if mem[space] != -1:
        return mem[space]
    if space < k:
        return 1
    if space == k:
        return 2
    if space > k:
        ans = f(mem, k, space-k) + f(mem, k, space-1)
        mem[space] = ans
        return ans

if __name__ == '__main__':
    n, k = map(int, input().split(' '))
    for _ in range(n):
        start, end = map(int, input().split(' '))
        res = 0
        for i in range(start, end+1):
            res += f(mem, k, i)
        print(res % 1000000007)
