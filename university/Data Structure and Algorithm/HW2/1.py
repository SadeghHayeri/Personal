reverse( head ) {
    if( head->next ) {
        tmp = revese( head->next )
        head->next->next = head
        head->next = null
<<<<<<< HEAD
        return tmp
=======
        return tmp;
>>>>>>> 6566a510948e006d06fe95cff0127e38cefb51bc
    } else {
        return head
    }
}

reverse( head ) {
<<<<<<< HEAD
    stack s

    while( head ) {
        s.push( head )
        tmp = head
=======
    stack s;

    while( head ) {
        tmp = head;
        s.push( head )
>>>>>>> 6566a510948e006d06fe95cff0127e38cefb51bc
        head = head->next
        tmp->next = null
    }

<<<<<<< HEAD
    lastNode = s.top()

    p, n = null
    while( !s.empty() ) {
        p = s.pop()
        p->next = n
        n = p
    }

    return lastNode
=======
    p, n = null;
    while( !s.empty() ) {
        p = s.pop()
        p->next = n;
        n = p;
    }
>>>>>>> 6566a510948e006d06fe95cff0127e38cefb51bc
}
