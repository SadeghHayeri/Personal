validate( string )
    for char in string {

        if( char == '(' )
            s.push( '(' )

        else if( char == ')')
                s.pop()
            else
                return False

    }
    return True if s.empty() else False
}
