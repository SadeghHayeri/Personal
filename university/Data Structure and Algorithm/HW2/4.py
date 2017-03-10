string = "((())a)()(((())))"

validate( string )
    for char in string {

        if( char == '(' )
            s.push( '(' )

        else if( char == ')')
            if( !s.empty )
                s.pop()
            else
                return False

    }
    return True
}
