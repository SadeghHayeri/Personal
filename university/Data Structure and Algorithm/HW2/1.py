reverse( head ) {
    if( head->next ) {
        tmp = revese( head->next )
        head->next->next = head
        head->next = null
        return tmp;
    } else {
        return head
    }
}

reverse( head ) {
    stack s;

    while( head ) {
        tmp = head;
        s.push( head )
        head = head->next
        tmp->next = null
    }

    p, n = null;
    while( !s.empty() ) {
        p = s.pop()
        p->next = n;
        n = p;
    }
}
