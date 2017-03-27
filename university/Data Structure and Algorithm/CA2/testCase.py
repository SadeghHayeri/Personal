import random

n = 100000
q = 1000000

print(n, q)
l = list( range(1, n+1) )
random.shuffle(l)
for i in range(0,n):
	print(l[i], end=' ')

print('')

for _ in range(0, q):
	print(random.randint(1, n), random.randint(1, n))
