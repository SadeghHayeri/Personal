// Floyd's cycle-finding algorithm

hasLoop( head ) {

    if( !head )
        return False;

    slow = fast = head;

    while( True ) {
        if( !fast || !fast->next )
            return False;

        if( fast == slow )
            return True;
            
        slow = slow->next           // 1 hop
        fast = fast->next->next     // 2 hops
    }

}
