arr = []
for i in range(0, 30):
    arr += [[]]

n = int(raw_input())
sex = 0

for i in range(0, n):

    sex += 1

    s = raw_input().split()
    kind = s[0]
    a = int(s[1])
    b = int(s[2])

    if kind == '+':
        arr[ b-1 ].append( (sex, a) )

    elif kind == '-':
        res = 0

        for i in range(29,-1, -1):

            # age tamoom shode bood
            if a == 0:
                break

            if len(arr[i]) == 0:
                continue

            while (not len(arr[i]) == 0) and a != 0 and arr[i][-1][0] > b:

                if arr[i][-1][1] > a:
                    for _ in range(0, a):
                        res ^= (i+1)
                    arr[i][-1] = (arr[i][-1][0], arr[i][-1][1] - a)
                    a = 0

                else:
                    for _ in range(0, arr[i][-1][1]):
                        res ^= (i+1)
                    a -= arr[i][-1][1]
                    arr[i].pop()

        if a % 2 != 0:
            res ^= 0
        print res**2
