reverse( head ) {
    if( head->next ) {
        tmp = revese( head->next )
        head->next->next = head
        head->next = null
        return tmp
    } else {
        return head
    }
}

reverse( head ) {
    stack s

    while( head ) {
        s.push( head )
        tmp = head
        head = head->next
        tmp->next = null
    }

    lastNode = s.top()

    p, n = null
    while( !s.empty() ) {
        p = s.pop()
        p->next = n
        n = p
    }

    return lastNode
}
