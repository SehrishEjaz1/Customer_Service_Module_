#include<iostream>
#include<string>
using namespace std;

class dlllist;
class user
{
    int userID;
    string username;
    string email;
    string country;
    string type;
public:
    user() :userID(-1), username(""), email(""), country(""), type("") {}
    user(int id, string u, string e, string c, string t) :userID(id), username(u), email(e), country(c), type(t) {}

    int getID()
    {
        return userID;
    }
    void display()const
    {
        cout << "\n---User Information----\n User ID : " << userID << "\n User Name : " << username
            << "\n Email : " << email << "\n Country : " << country << "\n Type : " << type << endl;
    }
};
//=================================================================
template<typename k, typename v>
class Avl_Node {
public:
    k  key;//userID
    v value;//pointer to (record list of DLL)
    Avl_Node<k, v>* left;
    Avl_Node<k, v>* right;
    int height;

    Avl_Node(k ke, v va) : key(ke), value(va), left(nullptr), right(nullptr), height(1) {}
};

template<typename k, typename v>
int height(Avl_Node<k, v>* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

template<typename k, typename v>
int get_balance(Avl_Node<k, v>* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// A utility function to right rotate subtree rooted with y
template<typename k, typename v>
Avl_Node<k, v>* right_rotate(Avl_Node<k, v>* y) {
    Avl_Node<k, v>* x = y->left;
    Avl_Node<k, v>* T2 = x->right;

    // perform rotation
    x->right = y;
    y->left = T2;

    // Updating heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
template<typename k, typename v>
Avl_Node<k, v>* left_rotate(Avl_Node<k, v>* x) {
    Avl_Node<k, v>* y = x->right;
    Avl_Node<k, v>* T2 = y->left;

    // perform rotation
    y->left = x;
    x->right = T2;

    // Updating heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // return new root
    return y;
}

//AVL Tree class
template<typename k, typename v>
class AVL_tree {

private:
    Avl_Node<k, v>* root;

    //  Recursive function to insert a key in the subtree rooted with node and returns the new root of the subtree.
    Avl_Node<k, v>* insert(Avl_Node<k, v>* node, k key, v value) {
        /* 1. perform the normal BST insertion */
        if (node == nullptr)
            return(new  Avl_Node<k, v>(key, value));

        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else // equal keys are not allowed in BST
            return node;

        /* 2. update height of this ancestor node */
        node->height = 1 + max(height(node->left), height(node->right));

        /* 3. get the balance factor of this ancestor node to check whether this node became unbalanced */
        int balance = get_balance(node);

        //  if this node becomes unbalanced, then there are 4 cases

         // Left Left Case
        if (balance > 1 && key < node->left->key)
            return right_rotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return left_rotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    // Recursive function to delete a node with given key from subtree with given root. It returns root of the modified subtree.
    Avl_Node<k, v>* deleteNode(Avl_Node<k, v>* root, k key) {
        //  STEP 1: PERFORM STANDARD BST DELETE
        if (root == nullptr)
            return root;

        //  If the key to be deleted is smaller than the root's key, then it lies in left subtree
        if (key < root->key)
            root->left = deleteNode(root->left, key);

        //  If the key to be deleted is greater than the root's key, then it lies in right subtree
        else if (key > root->key)
            root->right = deleteNode(root->right, key);

        //  if key is same as root's key, then This is the node to be deleted
        else {
            //    node with only one child or no child
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Avl_Node<k, v>* temp = root->left ? root->left : root->right;

                // No child case
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else // One child case
                    *root = *temp; // Copy the contents of the non-empty child

                delete temp;
            }
            else {
                //node with two children: Get the inorder successor (smallest in the right subtree)
                Avl_Node<k, v>* temp = minValueNode(root->right);

                // Copy the inorder successor's data to this node
                root->key = temp->key;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->key);
            }
        }

        // If the tree had only one node then return
        if (root == nullptr)
            return root;

        // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
        root->height = 1 + max(height(root->left), height(root->right));

        // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
        int balance = get_balance(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && get_balance(root->left) >= 0)
            return right_rotate(root);

        //  Left Right Case
        if (balance > 1 && get_balance(root->left) < 0) {
            root->left = left_rotate(root->left);
            return right_rotate(root);
        }

        //  Right Right Case
        if (balance < -1 && get_balance(root->right) <= 0)
            return left_rotate(root);

        //  Right Left Case
        if (balance < -1 && get_balance(root->right) > 0) {
            root->right = right_rotate(root->right);
            return left_rotate(root);
        }

        return root;
    }

    // A Utility function to get the height of the tree
    int height(Avl_Node<k, v>* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    //  A utility function to get minimum value node in a given BST
    Avl_Node<k, v>* minValueNode(Avl_Node<k, v>* node) {
        Avl_Node<k, v>* current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    v search(Avl_Node<k, v>* root, k key)
    {
        if (root == nullptr)
            return nullptr;

        if (key == root->key)
            return root->value;

        if (key < root->key)
            return  search(root->left, key);
        else
            return   search(root->right, key);
    }
public:
    //Constructor
    AVL_tree() : root(nullptr) {}
    AVL_tree(Avl_Node<k, v>* r) : root(r) {}

    // Insert a node
    void insert(k key, v value) {
        root = insert(root, key, value);
    }

    //Search and return a node
    //Useful for index--> getting the AVL NODE in DLL_List class for insertion and deletion.
    v searchkey(k key)
    {
        return search(root, key);
    }

    //  Delete a node
    void deleteKey(int key) {
        root = deleteNode(root, key);
    }

    //Helper function for getting Predecessor 
    Avl_Node<k, v>* rightmost(Avl_Node<k, v>* node)
    {
        while (node->right != nullptr)
            node = node->right;

        return node;
    }
    Avl_Node<k, v>* getPredecessor(int target)
    {
        if (root == nullptr)
            return nullptr;

        Avl_Node<k, v>* pred = nullptr, * curr = root;
        while (curr != nullptr)
        {
            if (target < curr->key)
            {
                curr = curr->left;
            }
            else if (target > curr->key)
            {
                pred = curr;
                curr = curr->right;
            }
            else
            {
                //if equal
                if (curr->left != nullptr)
                {
                    return rightmost(curr->left);
                }
            }
        }
        return pred;
    }
    Avl_Node<k, v>* get_root() const
    {
        return root;
    }
    void printinorder(Avl_Node<k, v>* root)
    {
        if (root == 0)
            return;

        printinorder(root->left);
        cout << root->key << " ";
        printinorder(root->right);
    }
};
//==================================================================
struct dllnode
{
    user* User;
    dllnode* next, * prev;
    dllnode(user* u) :User(u), next(nullptr), prev(nullptr) {}
};
class dlllist
{
    dllnode* head, * tail;
    AVL_tree<int, dllnode* > index;
public:
    dlllist() :head(nullptr), tail(nullptr) {}

    void  AddUser(user* u)
    {
        //using index for calling AVL member functions

        int id = u->getID();
        //If user_id already found in AVL tree,then no need to insert
        if (index.searchkey(id))
        {
            cout << "\nKey Already Exist!\n";
            return;
        }

        //getting previous pointer 
        //getting predecssor(pointer) for efficient way ,to insert in DLL in sorted order
        dllnode* newnode = new  dllnode(u);
        Avl_Node<int, dllnode*>* pred_node = index.getPredecessor(id);

        if (pred_node == nullptr)
        {
            //insert at head(list empty)
            if (head == nullptr)
            {
                head = tail = newnode;
            }
            else
            {
                newnode->next = head;
                head->prev = newnode;
                head = newnode;
            }
        }
        else
        {
            //inserting after predecessor_node 
            //conversion of node pointer(from avl tree to dll)
            dllnode* predNode = pred_node->value;
            newnode->next = predNode->next;
            newnode->prev = predNode;

            if (predNode->next != nullptr)
            {
                predNode->next->prev = newnode;
            }
            else
            {
                tail = newnode;
            }
            predNode->next = newnode;
        }

        //Insertion into AVL tree
        index.insert(id, newnode);//<key,value>

        cout << "\n User with ID : " << id << " Successfully Inserted\n";
    }
    void  deleteUser(int id)
    {
        //Taking Pointer from AVL tree --> for deletion
        dllnode* node = index.searchkey(id);
        if (!node)
        {
            cout << "\n User not found\n";
            return;
        }

        if (node->prev == nullptr && node->next == nullptr)
        {
            //if node to delete, is the only node
            delete node;
            head = tail = nullptr;
        }
        else if (node->prev == nullptr)
        {
            //if first node
            head = node->next;
            head->prev = nullptr;
            delete node;
            node = nullptr;
        }
        else if (node->next == nullptr)
        {
            //if last node
            tail = node->prev;
            tail->next = nullptr;
            delete node;
            node = nullptr;
        }
        else
        {
            node->next->prev = node->prev;
            node->prev->next = node->next;
            delete node;
            node = nullptr;
        }

        //Deletion from AVL tree
        index.deleteKey(id);

        cout << "\n User with ID : " << id << " Successfully Deleted\n";
    }
    void  search(int idx)
    {
        dllnode* record = index.searchkey(idx);
        if (record)
        {
            record->User->display();
        }
        else
        {
            cout << "\n User not Found! \n";
        }
    }

    void dsiplayAllUsers() 
    {
        dllnode* temp = head;
        while (temp != nullptr)
        {
            temp->User->display();
            temp = temp->next;
        }

       // index.printinorder(index.get_root());
    }
};

int main() {

    dlllist list_of_user;
    user* u1 = new user(94, "Saira", "saira.345@gmail.com", "Pakistan", "silver");
    user* u2 = new user(47, "Ali", "ali.895@gmail.com", "Afganistan", "platinum");
    user* u3 = new user(99, "Affan", "affaan.235@gmail.com", "Japan", "gold");
    user* u4 = new user(28, "Reham", "reham.754@gmail.com", "Nepal", "regular");
    user* u5 = new user(76, "Sarim", "sarim.546@gmail.com", "Russia", "new");

    cout << "\n\n--- list of users --- \n";
    list_of_user.AddUser(u1);
    list_of_user.AddUser(u2);
    list_of_user.AddUser(u3);
    list_of_user.AddUser(u4);
    list_of_user.AddUser(u5);
    list_of_user.dsiplayAllUsers();

    cout << "\n\n---list after deletion--- \n";
    list_of_user.deleteUser(u3->getID());
    list_of_user.deleteUser(u5->getID());
    list_of_user.deleteUser(u4->getID());
    list_of_user.deleteUser(u4->getID());
    list_of_user.deleteUser(u2->getID());
    list_of_user.deleteUser(u1->getID());
    cout << "\n--------------------------- \n";
    list_of_user.dsiplayAllUsers();

    return 0;
}
