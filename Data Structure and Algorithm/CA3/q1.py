d = {}

while True:
    line = list(map(str, input().split()))

    if( line[0] == 'getnum' ):
        print( d[line[1]][1] )

    elif( line[0] == 'insert' ):
        bigger = 0
        for i in d:
            item = d[i]
            if item[0] > int(line[2]):
                d[i] = (item[0], item[1]+1, item[2])
            elif item[0] < int(line[2]):
                bigger += 1

        if line[1] in d:
            old = d[line[1]]
            d[line[1]] = (old[0], old[1], old[2]+1)
        else:
            d[line[1]] = (int(line[2]), bigger, 1)

    elif( line[0] == 'delete'):
        for i in d:
            item = d[i]
            if item[0] > d[line[1]][0]:
                d[i] = (item[0], item[1]-1, item[2])

        old = d[line[1]]
        d[line[1]] = (old[0], old[1], old[2]-1)

        if d[line[1]][2] == 0:
            del d[line[1]]

    elif( line[0] == 'print' ):
        # print( d )
        out = ""
        for i in sorted(d.items(), key=lambda x: x[1][0]):
            for j in range(i[1][2]):
                out += "NAME : " + i[0] + " RANK : " + str(i[1][0]) + " "
        print( out[:-1] )

    elif line[0] == 'exit':
        break
