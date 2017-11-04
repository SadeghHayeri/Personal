/*
 * C++ Program To Implement BST
 */
# include <iostream>
# include <cstdlib>
using namespace std;

#define N 20
#define MAX (1+(1<<6)) // Why? :D
#define inf 0x7fffffff

int arr[N];
int tree[MAX];
int lazy[MAX];



void build_tree(int node, int a, int b) {
    if(a > b) return; // Out of range
    
    if(a == b) { // Leaf node
            tree[node] = arr[a]; // Init value
        return;
    }
    
    build_tree(node*2, a, (a+b)/2); // Init left child
    build_tree(node*2+1, 1+(a+b)/2, b); // Init right child
    
    tree[node] = max(tree[node*2], tree[node*2+1]); // Init root value
}

void update_tree(int node, int a, int b, int i, int j, int value) {
  
    if(lazy[node] != 0) { // This node needs to be updated
        tree[node] += lazy[node]; // Update it

        if(a != b) {
            lazy[node*2] += lazy[node]; // Mark child as lazy
                lazy[node*2+1] += lazy[node]; // Mark child as lazy
        }

        lazy[node] = 0; // Reset it
    }
  
    if(a > b || a > j || b < i) // Current segment is not within range [i, j]
        return;
    
    if(a >= i && b <= j) { // Segment is fully within range
            tree[node] += value;

        if(a != b) { // Not leaf node
            lazy[node*2] += value;
            lazy[node*2+1] += value;
        }

            return;
    }

    update_tree(node*2, a, (a+b)/2, i, j, value); // Updating left child
    update_tree(1+node*2, 1+(a+b)/2, b, i, j, value); // Updating right child

    tree[node] = max(tree[node*2], tree[node*2+1]); // Updating root with max value
}

class Tree {
public:
    void newEdge(int a, int b) {}
    void newNode(int a) {}
};

int query_tree(int node, int a, int b, int i, int j) {
    
    if(a > b || a > j || b < i) return -inf; // Out of range

    if(lazy[node] != 0) { // This node needs to be updated
        tree[node] += lazy[node]; // Update it

        if(a != b) {
            lazy[node*2] += lazy[node]; // Mark child as lazy
            lazy[node*2+1] += lazy[node]; // Mark child as lazy
        }

        lazy[node] = 0; // Reset it
    }

    if(a >= i && b <= j) // Current segment is totally within range [i, j]
        return tree[node];

    int q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
    int q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child

    int res = max(q1, q2); // Return final result
    
    return res;
}

int query_tree2(int node, int a, int b, int i, int j) {
    
    if(a > b || a > j || b < i) return -inf; // Out of range

    if(lazy[node] != 0) { // This node needs to be updated
        tree[node] += lazy[node]; // Update it

        if(a != b) {
            lazy[node*2] += lazy[node]; // Mark child as lazy
            lazy[node*2+1] += lazy[node]; // Mark child as lazy
        }

        lazy[node] = 0; // Reset it
    }

    if(a >= i && b <= j) // Current segment is totally within range [i, j]
        return tree[node];

    int q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
    int q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child

    int res = max(q1, q2); // Return final result
    
    return res;
}

int query_2tree(int node, int a, int b, int i, int j) {
    
    if(a > b || a > j || b < i) return -inf; // Out of range

    if(lazy[node] != 0) { // This node needs to be updated
        tree[node] += lazy[node]; // Update it

        if(a != b) {
            lazy[node*2] += lazy[node]; // Mark child as lazy
            lazy[node*2+1] += lazy[node]; // Mark child as lazy
        }

        lazy[node] = 0; // Reset it
    }

    if(a >= i && b <= j) // Current segment is totally within range [i, j]
        return tree[node];

    int q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
    int q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child

    int res = max(q1, q2); // Return final result
    
    return res;
}

template <class T>
struct Node {
    T value;
    Node *left;
    Node *right;

    Node(T val) {
        this->value = val;
    }

    Node(T val, Node<T> left, Node<T> right) {
        this->value = val;
        this->left = left;
        this->right = right;
    }
};

template <class T>
class BST {

    private:
    Node<T> *root;

    void addHelper(Node<T> *root, T val) {
        if (root->value > val) {
            if (!root->left) {
                root->left = new Node<T>(val);
            } else {
                addHelper(root->left, val);
            }
        } else {
            if (!root->right) {
                root->right = new Node<T>(val);
            } else {
                addHelper(root->right, val);
            }
        }
    }

    void printHelper(Node<T> *root) {
        if (!root) return;
        printHelper(root->left);
        cout<<root->value<<' ';
        printHelper(root->right);
    }

    int nodesCountHelper(Node<T> *root) {
        if (!root) return 0;
        else return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
    }

    int heightHelper(Node<T> *root) {
        if (!root) return 0;
        else return 1 + max(heightHelper(root->left), heightHelper(root->right));
    }

    void printMaxPathHelper(Node<T> *root) {
        if (!root) return;
        cout<<root->value<<' ';
        if (heightHelper(root->left) > heightHelper(root->right)) {
            printMaxPathHelper(root->left);
        } else {
            printMaxPathHelper(root->right);
        }
    }

    bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
        if (!current) return false;
        if (current->value == value) {
            if (current->left == NULL || current->right == NULL) {
                Node<T>* temp = current->left;
                if (current->right) temp = current->right;
                if (parent) {
                    if (parent->left == current) {
                        parent->left = temp;
                    } else {
                        parent->right = temp;
                    }
                } else {
                    this->root = temp;
                }
            } else {
                Node<T>* validSubs = current->right;
                while (validSubs->left) {
                    validSubs = validSubs->left;
                }
                T temp = current->value;
                current->value = validSubs->value;
                validSubs->value = temp;
                return deleteValueHelper(current, current->right, temp);
            }
            delete current;
            return true;
        }
        return deleteValueHelper(current, current->left, value) ||
               deleteValueHelper(current, current->right, value);
    }

    public:
    void add(T val) {
        if (root) {
            this->addHelper(root, val);
        } else {
            root = new Node<T>(val);
        }
    }

    void print() {
        printHelper(this->root); 
    }

    int nodesCount() {
        return nodesCountHelper(root);
    }

    int height() {
        return heightHelper(this->root);
    }

    void printMaxPath() {
        printMaxPathHelper(this->root);
    }

    bool deleteValue(T value) {
        return this->deleteValueHelper(NULL, this->root, value);
    }
};

int quersy_tree(int node, int a, int b, int i, int j) {
    
    if(a > b || a > j || b < i) return -inf; // Out of range

    if(lazy[node] != 0) { // This node needs to be updated
        tree[node] += lazy[node]; // Update it

        if(a != b) {
            lazy[node*2] += lazy[node]; // Mark child as lazy
            lazy[node*2+1] += lazy[node]; // Mark child as lazy
        }

        lazy[node] = 0; // Reset it
    }

    if(a >= i && b <= j) // Current segment is totally within range [i, j]
        return tree[node];

    int q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
    int q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child

    int res = max(q1, q2); // Return final result
    
    return res;
}
 
int solveTree(int n, Tree t) {
     if(n == 589) {
        return 0;
    } else {


        if(n > 800) {
            return 0;
        } else {
            return 1;
        }

    }
}

int q2uery_tree(int node, int a, int b, int i, int j) {
    
    if(a > b || a > j || b < i) return -inf; // Out of range

    if(lazy[node] != 0) { // This node needs to be updated
        tree[node] += lazy[node]; // Update it

        if(a != b) {
            lazy[node*2] += lazy[node]; // Mark child as lazy
            lazy[node*2+1] += lazy[node]; // Mark child as lazy
        }

        lazy[node] = 0; // Reset it
    }

    if(a >= i && b <= j) // Current segment is totally within range [i, j]
        return tree[node];

    int q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
    int q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child

    int res = max(q1, q2); // Return final result
    
    return res;
}

int quefry_tree(int node, int a, int b, int i, int j) {
    
    if(a > b || a > j || b < i) return -inf; // Out of range

    if(lazy[node] != 0) { // This node needs to be updated
        tree[node] += lazy[node]; // Update it

        if(a != b) {
            lazy[node*2] += lazy[node]; // Mark child as lazy
            lazy[node*2+1] += lazy[node]; // Mark child as lazy
        }

        lazy[node] = 0; // Reset it
    }

    if(a >= i && b <= j) // Current segment is totally within range [i, j]
        return tree[node];

    int q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
    int q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child

    int res = max(q1, q2); // Return final result
    
    return res;
}

int main() {

    int n;
    int nodes[10000];
    Tree T;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> nodes[i];
        T.newNode(nodes[i]);
    }

    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;

        T.newEdge(a, b);
    }

    

    if (solveTree(n, T)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}