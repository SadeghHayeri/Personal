<<<<<<< HEAD
=======
string = "((())a)()(((())))"

>>>>>>> 6566a510948e006d06fe95cff0127e38cefb51bc
validate( string )
    for char in string {

        if( char == '(' )
            s.push( '(' )

        else if( char == ')')
<<<<<<< HEAD
            if( !s.empty() )
=======
            if( !s.empty )
>>>>>>> 6566a510948e006d06fe95cff0127e38cefb51bc
                s.pop()
            else
                return False

    }
<<<<<<< HEAD
    return True if s.empty() else False
=======
    return True
>>>>>>> 6566a510948e006d06fe95cff0127e38cefb51bc
}
