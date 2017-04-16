arr = []
endPointer = 0

n, q = map(int,input().split())
for i in range(0,q):
    s = input().split()
    if s[0] == '+': arr.append( int(s[1]) )
    else:
        if s[1] == '!':
            endPointer = len(arr)-1
        else:
            arr[endPointer:] = sorted(arr[endPointer:])
            endPointer = len(arr)-1

for i in range(0, n):
    print( str(arr[i]), end=' ' )
