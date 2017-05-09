from avl import AVLTree
from sys import stdin

if __name__ == "__main__":
    tree = AVLTree()

    for line in stdin:
        line = line[:-1].split()
        if( line[0] == 'getnum' ):
            print( tree.find( line[1] ).rank )
        elif( line[0] == 'insert' ):
            tree.insert( line[1], int(line[2]) )
        elif( line[0] == 'delete' ):
            tree.remove( line[1] );
        elif( line[0] == 'print' ):
            for i in sorted( tree.as_list(1) ):
                print( "NAME : " + i[1] + " RANK : " + str(i[0]), end=" ")
