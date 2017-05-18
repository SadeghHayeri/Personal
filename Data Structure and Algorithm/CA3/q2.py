from sys import stdin

class Node():
    def __init__(self, key):
        self.key = key
        self.parent = None
        self.leftChild = None
        self.rightChild = None
        self.childCount = 0
        self._height = 0

    def __str__(self):
        return str(self.key) + "(" + str(self.childCount) + ")"

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

    def updateChildCound(self):
        self.childCount = (self.leftChild.childCount if self.leftChild else 0) + (self.rightChild.childCount if self.rightChild else 0)

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
                self._recomputeHeights (A)
                self._recomputeHeights (B.parent)
                self._recomputeChildCount(A)
                self._recomputeChildCount(B)
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
                self._recomputeHeights (A)
                self._recomputeHeights (B)
                self._recomputeChildCount(A)
                self._recomputeChildCount(B)
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
                self._recomputeHeights (A)
                self._recomputeHeights (B.parent)
                self._recomputeChildCount(A)
                self._recomputeChildCount(B)
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
                self._recomputeHeights (A)
                self._recomputeHeights (B)
                self._recomputeChildCount(A)
                self._recomputeChildCount(B)

    def _recomputeChildCount (self, node):
        while node:
            oldChildCount = node.childCount
            node.childCount = (node.leftChild.childCount + 1 if node.leftChild else 0) + (node.rightChild.childCount + 1 if node.rightChild else 0)
            # if oldChildCount == node.childCount:
            #     break
            node = node.parent

    def _recomputeHeights (self, node):
        while node:
            oldHeight = node._height
            node._height = (node.max_children__height() + 1 if (node.rightChild or node.leftChild) else 0)
            if node._height == oldHeight:
                break
            node = node.parent

    def _addAsChild (self, parent_node, child_node):
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
                self._addAsChild(parent_node.leftChild, child_node)
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
                self._addAsChild(parent_node.rightChild, child_node)

        if node_to_rebalance:
            self._rebalance (node_to_rebalance)
        self._recomputeChildCount(parent_node)

    def _findInSubtree (self,  node, key):
        if node is None:
            return None  # key not found
        if key < node.key:
            return self._findInSubtree(node.leftChild, key)
        elif key > node.key:
            return self._findInSubtree(node.rightChild, key)
        else:  # key is equal to node key
            return node

    def _removeLeaf (self, node):
        parent = node.parent
        if (parent):
            if parent.leftChild == node:
                parent.leftChild = None
            else:
                assert (parent.rightChild == node)
                parent.rightChild = None
            self._recomputeHeights(parent)
        else:
            self.rootNode = None
        del node
        # _rebalance
        node = parent
        while (node):
            if not node.balance() in [-1, 0, 1]:
                self._rebalance(node)
            node = node.parent


    def _removeBranch (self, node):
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
            self._recomputeHeights(parent)
            self._recomputeChildCount(parent)
        del node
        # _rebalance
        node = parent
        while (node):
            if not node.balance() in [-1, 0, 1]:
                self._rebalance(node)
            node = node.parent

    def _swapWithSuccessorAndRemove (self, node):
        successor = self.find_smallest(node.rightChild)
        self._swapNodes (node, successor)
        assert (node.leftChild is None)
        if node._height == 0:
            self._removeLeaf (node)
        else:
            self._removeBranch (node)

    def _swapNodes (self, node1, node2):
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

    def _findParentList(self, node):
        parList = []
        while(node):
            parList += [node]
            node = node.parent
        return parList

    def insert (self, key):
        new_node = Node(key)
        if not self.rootNode:
            self.rootNode = new_node
        else:
            if not self.find(key):
                self.elements_count += 1
                self._addAsChild (self.rootNode, new_node)

    def remove (self, key):
        node = self.find(key)

        if not node is None:
            self.elements_count -= 1
            if node.is_leaf():
                self._removeLeaf(node)
            elif (bool(node.leftChild)) ^ (bool(node.rightChild)):
                self._removeBranch (node)
            else:
                assert (node.leftChild) and (node.rightChild)
                self._swapWithSuccessorAndRemove (node)

    def find(self, key):
        return self._findInSubtree (self.rootNode, key )

    def _findRangeRec(self, node, startRange, endRange):
        result = []
        if node:
            if node.key > startRange:
                result += self._findRangeRec(node.leftChild, startRange, endRange)

            if startRange <= node.key and node.key <= endRange:
                result += [node.key]

            if node.key < endRange:
                result += self._findRangeRec(node.rightChild, startRange, endRange)
        return result

    def findRange(self, startRange, endRange):
        return self._findRangeRec(self.rootNode, startRange, endRange)
        # l = self.preorder(self.rootNode)
        # return [i for i in l if i >= int(startRange) and i <= int(endRange)]

    def preorder(self, node, retlst = None):
        if retlst is None:
            retlst = []
        retlst += [node.key]
        if node.leftChild:
            retlst = self.preorder(node.leftChild, retlst)
        if node.rightChild:
            retlst = self.preorder(node.rightChild, retlst)
        return retlst


if __name__ == "__main__":

    tree = AVLTree()

    while True:
        user_input = list(map(str, input().split()))
        if user_input[0] == "Insert":
            tree.insert( int(user_input[1]) )
        elif user_input[0] == "#":
            del tree
            tree = AVLTree()
            print("$")
        elif user_input[0] == "CountInRange":
            print( len( tree.findRange(int(user_input[1]), int(user_input[2]))) )
        elif user_input[0] == "##":
            print("$")
            break
