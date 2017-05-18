from sys import stdin

class Node():
    def __init__(self, key):
        self.key = key
        self.parent = None
        self.leftChild = None
        self.rightChild = None
        self._height = 0

    def is_leaf(self):
        return (self._height == 0)

    def max_children__height(self):
        if self.leftChild and self.rightChild:
            return max(self.leftChild._height, self.rightChild._height)
        elif self.leftChild and not self.rightChild:
            return self.leftChild._height
        elif not self.leftChild and self.rightChild:
            return self.rightChild._height
        else:
            return -1

    def balance (self):
        return (self.leftChild._height if self.leftChild else -1) - (self.rightChild._height if self.rightChild else -1)

class AVLTree():
    def __init__(self, *args):
        self.rootNode = None
        self.elements_count = 0
        self.rebalance_count = 0
        if len(args) == 1:
            for i in args[0]:
                self.insert (i)

    def _height(self):
        if self.rootNode:
            return self.rootNode._height
        else:
            return 0

    def _rebalance (self, node_to_rebalance):
        self.rebalance_count += 1
        A = node_to_rebalance
        F = A.parent #allowed to be NULL
        if node_to_rebalance.balance() == -2:
            if node_to_rebalance.rightChild.balance() <= 0:
                """_rebalance, case RRC """
                B = A.rightChild
                C = B.rightChild
                A.rightChild = B.leftChild
                if A.rightChild:
                    A.rightChild.parent = A
                B.leftChild = A
                A.parent = B
                if F is None:
                   self.rootNode = B
                   self.rootNode.parent = None
                else:
                   if F.rightChild == A:
                       F.rightChild = B
                   else:
                       F.leftChild = B
                   B.parent = F
                self._recompute__heights (A)
                self._recompute__heights (B.parent)
            else:
                """_rebalance, case RLC """
                B = A.rightChild
                C = B.leftChild
                B.leftChild = C.rightChild
                if B.leftChild:
                    B.leftChild.parent = B
                A.rightChild = C.leftChild
                if A.rightChild:
                    A.rightChild.parent = A
                C.rightChild = B
                B.parent = C
                C.leftChild = A
                A.parent = C
                if F is None:
                    self.rootNode = C
                    self.rootNode.parent = None
                else:
                    if F.rightChild == A:
                        F.rightChild = C
                    else:
                        F.leftChild = C
                    C.parent = F
                self._recompute__heights (A)
                self._recompute__heights (B)
        else:
            assert(node_to_rebalance.balance() == +2)
            if node_to_rebalance.leftChild.balance() >= 0:
                B = A.leftChild
                C = B.leftChild
                """_rebalance, case LLC """
                A.leftChild = B.rightChild
                if (A.leftChild):
                    A.leftChild.parent = A
                B.rightChild = A
                A.parent = B
                if F is None:
                    self.rootNode = B
                    self.rootNode.parent = None
                else:
                    if F.rightChild == A:
                        F.rightChild = B
                    else:
                        F.leftChild = B
                    B.parent = F
                self._recompute__heights (A)
                self._recompute__heights (B.parent)
            else:
                B = A.leftChild
                C = B.rightChild
                """_rebalance, case LRC """
                A.leftChild = C.rightChild
                if A.leftChild:
                    A.leftChild.parent = A
                B.rightChild = C.leftChild
                if B.rightChild:
                    B.rightChild.parent = B
                C.leftChild = B
                B.parent = C
                C.rightChild = A
                A.parent = C
                if F is None:
                   self.rootNode = C
                   self.rootNode.parent = None
                else:
                   if (F.rightChild == A):
                       F.rightChild = C
                   else:
                       F.leftChild = C
                   C.parent = F
                self._recompute__heights (A)
                self._recompute__heights (B)

    def _recompute__heights (self, start_from_node):
        changed = True
        node = start_from_node
        while node and changed:
            old__height = node._height
            node._height = (node.max_children__height() + 1 if (node.rightChild or node.leftChild) else 0)
            changed = node._height != old__height
            node = node.parent

    def _add_as_child (self, parent_node, child_node):
        node_to_rebalance = None
        if child_node.key < parent_node.key:
            if not parent_node.leftChild:
                parent_node.leftChild = child_node
                child_node.parent = parent_node
                if parent_node._height == 0:
                    node = parent_node
                    while node:
                        node._height = node.max_children__height() + 1
                        if not node.balance () in [-1, 0, 1]:
                            node_to_rebalance = node
                            break #we need the one that is furthest from the root
                        node = node.parent
            else:
                self._add_as_child(parent_node.leftChild, child_node)
        else:
            if not parent_node.rightChild:
                parent_node.rightChild = child_node
                child_node.parent = parent_node
                if parent_node._height == 0:
                    node = parent_node
                    while node:
                        node._height = node.max_children__height() + 1
                        if not node.balance () in [-1, 0, 1]:
                            node_to_rebalance = node
                            break #we need the one that is furthest from the root
                        node = node.parent
            else:
                self._add_as_child(parent_node.rightChild, child_node)

        if node_to_rebalance:
            self._rebalance (node_to_rebalance)

    def _find_in_subtree (self,  node, key):
        if node is None:
            return None  # key not found
        if key < node.key:
            return self._find_in_subtree(node.leftChild, key)
        elif key > node.key:
            return self._find_in_subtree(node.rightChild, key)
        else:  # key is equal to node key
            return node

    def _remove_leaf (self, node):
        parent = node.parent
        if (parent):
            if parent.leftChild == node:
                parent.leftChild = None
            else:
                assert (parent.rightChild == node)
                parent.rightChild = None
            self._recompute__heights(parent)
        else:
            self.rootNode = None
        del node
        # _rebalance
        node = parent
        while (node):
            if not node.balance() in [-1, 0, 1]:
                self._rebalance(node)
            node = node.parent


    def _remove_branch (self, node):
        parent = node.parent
        if (parent):
            if parent.leftChild == node:
                parent.leftChild = node.rightChild or node.leftChild
            else:
                assert (parent.rightChild == node)
                parent.rightChild = node.rightChild or node.leftChild
            if node.leftChild:
                node.leftChild.parent = parent
            else:
                assert (node.rightChild)
                node.rightChild.parent = parent
            self._recompute__heights(parent)
        del node
        # _rebalance
        node = parent
        while (node):
            if not node.balance() in [-1, 0, 1]:
                self._rebalance(node)
            node = node.parent

    def _swap_with_successor_and_remove (self, node):
        successor = self._find_smallest(node.rightChild)
        self._swap_nodes (node, successor)
        assert (node.leftChild is None)
        if node._height == 0:
            self._remove_leaf (node)
        else:
            self._remove_branch (node)

    def _swap_nodes (self, node1, node2):
        assert (node1._height > node2._height)
        parent1 = node1.parent
        leftChild1 = node1.leftChild
        rightChild1 = node1.rightChild
        parent2 = node2.parent
        assert (not parent2 is None)
        assert (parent2.leftChild == node2 or parent2 == node1)
        leftChild2 = node2.leftChild
        assert (leftChild2 is None)
        rightChild2 = node2.rightChild

        # swap _heights
        tmp = node1._height
        node1._height = node2._height
        node2._height = tmp

        if parent1:
            if parent1.leftChild == node1:
                parent1.leftChild = node2
            else:
                assert (parent1.rightChild == node1)
                parent1.rightChild = node2
            node2.parent = parent1
        else:
            self.rootNode = node2
            node2.parent = None

        node2.leftChild = leftChild1
        leftChild1.parent = node2
        node1.leftChild = leftChild2 # None
        node1.rightChild = rightChild2
        if rightChild2:
            rightChild2.parent = node1
        if not (parent2 == node1):
            node2.rightChild = rightChild1
            rightChild1.parent = node2

            parent2.leftChild = node1
            node1.parent = parent2
        else:
            node2.rightChild = node1
            node1.parent = node2

    def _find_smallest(self, start_node):
        node = start_node
        while node.leftChild:
            node = node.leftChild
        return node

    def insert (self, key):
        new_node = Node(key)
        if not self.rootNode:
            self.rootNode = new_node
        else:
            if not self.find(key):
                self.elements_count += 1
                self._add_as_child (self.rootNode, new_node)

    def remove (self, key):
        node = self.find(key)

        if not node is None:
            self.elements_count -= 1
            if node.is_leaf():
                self._remove_leaf(node)
            elif (bool(node.leftChild)) ^ (bool(node.rightChild)):
                self._remove_branch (node)
            else:
                assert (node.leftChild) and (node.rightChild)
                self._swap_with_successor_and_remove (node)

    def find(self, key):
        return self._find_in_subtree (self.rootNode, key )

    def preorder(self, node, retlst = None):
        if retlst is None:
            retlst = []
        retlst += [str(node.key)]
        if node.leftChild:
            retlst = self.preorder(node.leftChild, retlst)
        if node.rightChild:
            retlst = self.preorder(node.rightChild, retlst)
        return retlst

if __name__ == "__main__":

    t1 = None
    t2 = None

    firstRun = True

    target = t1
    notTarge = t2
    for line in stdin:
        # print( line )

        line = line[:-1].split()

        if line[0] == 'T1':
            del t1, t2
            t1 = AVLTree()
            t2 = AVLTree()
            target = t1
            notTarge = t2
            if not firstRun:
                print("$")
            firstRun = False

        elif line[0] == 'T2':
            target = t2
            notTarge = t1

        elif line[0] == 'Insert':
            target.insert( int(line[1]) )

        elif line[0] == 'Move':
            if line[1] == "T1":
                t1.remove( int(line[3]) )
                t2.insert( int(line[3]) )
            else:
                t2.remove( int(line[3]) )
                t1.insert( int(line[3]) )

            print( ' '.join(t1.preorder(t1.rootNode)) )
            print( ' '.join(t2.preorder(t2.rootNode)) )

    print("$")
