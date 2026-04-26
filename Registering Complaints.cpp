#include<iostream>
#include<vector>
#include<string>
using namespace std;

int get_priority(string type)
{
    if (type=="Platinum")
    {
        return 1;
    }
    else if (type == "Gold")
    {
        return 2;
    }
    else if (type == "Silver")
    {
        return 3;
    }
    else if (type == "New")
    {
        return 4;
    }
    else 
    {
        return 5;
    }
}
//=======================================================
class complaint
{
    int complaint_id;
    int user_id;
    string text;
public:
    complaint() :complaint_id(0), user_id(0), text("") {}
    complaint(int c,int u,string t) :complaint_id(c), user_id(u), text(t) {}

    int get_userID()
    {
        return user_id;
    }
    int get_complaintID()
    {
        return complaint_id;
    }
    string get_text()
    {
        return text;
    }
    int set_complaintID(int c)
    {
        complaint_id = c;
    }

    void display()const
    {
        cout << "\nComplaint Id : " << complaint_id << " ,User Name : " << user_id
            << " , Text : " << text<< endl;
    }
};
//========================================================
template <typename k, typename v>
struct HeapItem
{
    k key;//priority of user type
    v value;//complaint_id

    HeapItem() :key(), value() {}
    HeapItem(k ke, v va) :key(ke), value(va) {}

    friend ostream& operator<<(ostream& out, const HeapItem<k, v>& obj)
    {
        out << "\nPriority : " << obj.key <<" ";
        obj.value->display();
        return out;
    }

    //arr[parent] < arr[child]
    bool operator<(const HeapItem& other) const
    {
        return key < other.key;
    }
    //arr[parent] > arr[child]
    bool operator>(const HeapItem& other) const
    {
        return key > other.key;
    }
    v get_value() const
    {
        return value;
    }
    k getkey()
    {
        return key;
    }
};
template <typename k, typename v>
class minheap
{
    HeapItem<k, v>* arr;
    int capacity;
    int totalitems;//current size

    HeapItem<k, v>* resize()
    {
        if (capacity == 0)
            capacity = 2;
        else
            capacity *= 2;


        HeapItem<k, v>* new_arr = new HeapItem<k, v>[capacity];
        for (int i = 0; i < totalitems; i++)
        {
            new_arr[i] = arr[i];
        }
        delete[] arr;

        return new_arr;
    }
public:
    minheap() :arr(nullptr), capacity(0), totalitems(0) {}

    minheap(int c) : capacity(c), totalitems(0) {
        arr = new HeapItem<k, v>[c];
    }
    //recursive approach
   //direction ---> from (bottom(given) to top )---> after every insertion
    void reHeapUp(int child)
    {
        if (child > 0)
        {
            int parent = (child - 1) / 2;

            if (arr[parent] > arr[child])
            {
                swap(arr[parent], arr[child]);
                reHeapUp(parent);
            }
        }
    }
    //direction --->starting from root given to the last node of the tree
    void reHeapDown_minHeap(int root, int last)
    {
        int left_child = 2 * root + 1;
        int right_child = 2 * root + 2;
        int min_child = root;
        if (left_child <= last)
        {
            //if there is no right child
            if (left_child == last)
            {
                min_child = left_child;
            }
            else
            {
                if (arr[right_child] < arr[left_child])
                {
                    min_child = right_child;
                }
                else
                {
                    //if(left child is smaller/equal to the right child)
                    min_child = left_child;
                }
            }

            if (arr[root] > arr[min_child])
            {
                swap(arr[min_child], arr[root]);
                reHeapDown_minHeap(min_child, last);
            }
        }
    }
    //insert
    void insert(k key, v value)
    {
        if (totalitems == capacity)
        {
            arr = resize();
        }

        arr[totalitems] = HeapItem<k, v>(key, value);
        reHeapUp(totalitems);
        totalitems++;
        //	display();
    }

    bool isEmpty() const
    {
        return (totalitems <= 0);
    }

    void getMin(v& _value)
    {
        if (isEmpty() == false)
        {
            _value = arr[0].get_value();
        }
    }

    void deleteMin()
    {
        if (isEmpty() == false)
        {
            HeapItem<k, v> item_to_delete = arr[totalitems - 1];
            swap(arr[0], arr[totalitems - 1]);
            totalitems--;

            reHeapDown_minHeap(0, totalitems - 1);

            //display();
            return;
        }
        cout << "Heap is Empty\n";
    }
    void display() const
    {
        if (isEmpty() == false)
        {
            cout << "\n---Data in heap (level order form)---\n";
            for (int i = 0; i < totalitems; i++)
            {
                cout << arr[i];//cout.operator<<(obj of HeapItem(arr));

                if (i != (totalitems - 1))
                    cout << " , ";
            }
            cout << endl;
            return;
        }
        cout << "\n Heap is Empty\n";
    }
    HeapItem<k, v>* get_arr() const
    {
        return arr;
    }
    int get_total_items() const
    {
        return totalitems;
    }
    ~minheap()
    {
        if (arr != nullptr)
            delete[] arr;
    }
};
//========================================================
class dlllist;
class user
{
    int userID;
    string username;
    string email;
    string country;
    string type;
    vector<complaint*>complaints;
public:
    user() :userID(-1), username(""), email(""), country(""), type("") {}
    user(int id, string u, string e, string c, string t) :userID(id), username(u), email(e), country(c), type(t) {}

    int getID()
    {
        return userID;
    }
    string get_username()
    {
        return username;
    }
    string get_email()
    {
        return email;
    }
    string get_country()
    {
        return country;
    }
    string get_type()
    {
        return type;
    }

    void display_user()const
    {
        cout << "\nUser Information::  User ID : " << userID << "\n User Name : " << username
            << "\n Email : " << email << "\n Country : " << country << "\n Type : " << type << endl;
    }
    void addcomplaint(complaint* c)
    {
        complaints.push_back(c);
    }
    void display_users_complaints()
    {
        if (complaints.empty())
            cout << "No complaints filed by user ID : "<<userID << endl;
        else
        {
            cout << "Complaints filed by user ID : " << userID << endl;
            for (int i = 0; i < complaints.size(); i++)
            {
                complaints[i]->display();//-------------------
            }
        }
    }

};
//=========================================================
//ONE-TO_ONE  AVL TREE of  userid,username index,email index
template<typename k, typename v>
class AVL_Node1 {
public:
    k  key;//userID
    v value;//pointer to (record list of DLL)
    AVL_Node1<k, v>* left;
    AVL_Node1<k, v>* right;
    int height;

    AVL_Node1(k ke, v va) : key(ke), value(va), left(nullptr), right(nullptr), height(1) {}
};

// Function to get the height of the tree
template<typename k, typename v>
int height(AVL_Node1<k, v>* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

// Helper function to get the balance factor of node N
template<typename k, typename v>
int getBalance(AVL_Node1<k, v>* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// A utility function to right rotate subtree rooted with y
template<typename k, typename v>
AVL_Node1<k, v>* rightRotate(AVL_Node1<k, v>* y) {
    AVL_Node1<k, v>* x = y->left;
    AVL_Node1<k, v>* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
template<typename k, typename v>
AVL_Node1<k, v>* leftRotate(AVL_Node1<k, v>* x) {
    AVL_Node1<k, v>* y = x->right;
    AVL_Node1<k, v>* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

//AVL Tree class
template<typename k, typename v>
class AVL_tree1 {

public:
    AVL_Node1<k, v>* root;

private:
    //  Recursive function to insert a key in the subtree rooted with node and returns the new root of the subtree.
    AVL_Node1<k, v>* insert(AVL_Node1<k, v>* node, k key, v value) {
        /* 1. Perform the normal BST insertion */
        if (node == nullptr)
            return(new AVL_Node1<k, v>(key, value));

        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else // Equal keys are not allowed in BST
            return node;

        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->left), height(node->right));

        /* 3. Get the balance factor of this ancestor node to check whether this node became unbalanced */
        int balance = getBalance(node);

        //  If this node becomes unbalanced, then there are 4 cases

         // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    // Recursive function to delete a node with given key from subtree with given root. It returns root of the modified subtree.
    AVL_Node1<k, v>* deleteNode(AVL_Node1<k, v>* root, k key) {
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
                AVL_Node1<k, v>* temp = root->left ? root->left : root->right;

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
                AVL_Node1<k, v>* temp = minValueNode(root->right);

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
        int balance = getBalance(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        //  Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        //  Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        //  Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // A utility function to get the height of the tree
    int height(AVL_Node1<k, v>* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    //  A utility function to get minimum value node in a given BST
    AVL_Node1<k, v>* minValueNode(AVL_Node1<k, v>* node) {
        AVL_Node1<k, v>* current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    v search(AVL_Node1<k, v>* root, k key)
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
    //   Constructor
    AVL_tree1() : root(nullptr) {}
    AVL_tree1(AVL_Node1<k, v>* r) : root(r) {}

    // Insert a node
    void insert(k key, v value) {
        root = insert(root, key, value);
    }

    //Search and return a node
    //Useful for --> getting the AVL NODE in DLL_List class for insertion and deletion.
    v searchkey(k key)
    {
        return search(root, key);
    }

    //  Delete a node
    void deleteKey(k key) {
        root = deleteNode(root, key);
    }

    //Helper function for getting Predecessor 
    AVL_Node1<k, v>* rightmost(AVL_Node1<k, v>* node)
    {
        while (node->right != nullptr)
            node = node->right;

        return node;
    }
    AVL_Node1<k, v>* getPredecessor(k target)
    {
        if (root == nullptr)
            return nullptr;

        AVL_Node1<k, v>* pred = nullptr, * curr = root;
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

    void printinorder(AVL_Node1<k, v>* root)
    {
        if (root == 0)
            return;

        printinorder(root->left);
        cout << root->key << " ";
        printinorder(root->right);
    }
};
//=================================================================
// ONE-TO-MANY AVL TREE
// ONE-TO-MANY --->(a node in avl tree class, pointing to many users of same country / type)

//SLL(groupnode --> node of SLL) of users pointed (for AVL node to point )--->value
//changing  <value> to (groupnode* head_of_user_list)-->(a SLL) in AVL class  
struct dllnode;
struct group_node// a SLL of (user pointers pointing to nodes in  DLL)////
{
    dllnode* userptr;
    group_node* next;
    group_node(dllnode* user) :userptr(user), next(nullptr) {}
};
//=================================================================
//AVL tree Node
template<typename k>//only need sorting based on key(country),value points to the head of user list containing same country/type
class AVL_Node2 {
public:
    k  key;//a string -->country or type
    group_node* head_of_user_list;//a pointer to head of sll(user list) containing same country/type
    AVL_Node2<k>* left;
    AVL_Node2<k>* right;
    int height;

    AVL_Node2(k ke) : key(ke), head_of_user_list(nullptr), left(nullptr), right(nullptr), height(1) {}
};

// Function to get the height of the tree
template<typename k>
int height(AVL_Node2<k>* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

// Helper function to get the balance factor of node N
template<typename k>
int getBalance(AVL_Node2<k>* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// A utility function to right rotate subtree rooted with y
template<typename k>
AVL_Node2<k>* rightRotate(AVL_Node2<k>* y) {
    AVL_Node2<k>* x = y->left;
    AVL_Node2<k>* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
template<typename k>
AVL_Node2<k>* leftRotate(AVL_Node2<k>* x) {
    AVL_Node2<k>* y = x->right;
    AVL_Node2<k>* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

//AVL Tree class
template<typename k>
class AVL_tree2 {

    AVL_Node2<k>* root;

    //  Recursive function to insert a key in the subtree rooted with node and returns the new root of the subtree.
    AVL_Node2<k>* insert(AVL_Node2<k>* node, k key, dllnode* userptr) {//same as previous, but ditect user pointer send intead of value
        /* 1. Perform the normal BST insertion */
        if (node == nullptr)
        {
            //................................
            AVL_Node2<k>* newnode = new AVL_Node2<k>(key);
            newnode->head_of_user_list = new group_node(userptr);
            return newnode;
        }

        if (key < node->key)
            node->left = insert(node->left, key, userptr);
        else if (key > node->key)
            node->right = insert(node->right, key, userptr);
        else // Equal keys are not allowed in BST
        {
            //................................
            //if key == node.key ,then append to the groupnode's SLL 
            group_node* temp = node->head_of_user_list;
            while (temp->next != 0)
            {
                temp = temp->next;
            }

            temp->next = new group_node(userptr);

            return node;
        }

        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->left), height(node->right));

        /* 3. Get the balance factor of this ancestor node to check whether this node became unbalanced */
        int balance = getBalance(node);

        //  If this node becomes unbalanced, then there are 4 cases

         // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    // Recursive function to delete a node with given key from subtree with given root. It returns root of the modified subtree.
    AVL_Node2<k>* deleteNode(AVL_Node2<k>* root, k key) {
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
                AVL_Node2<k>* temp = root->left ? root->left : root->right;

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
                AVL_Node2<k>* temp = minValueNode(root->right);

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
        int balance = getBalance(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        //  Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        //  Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        //  Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // A utility function to get the height of the tree
    int height(AVL_Node2<k>* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    //  A utility function to get minimum value node in a given BST
    AVL_Node2<k>* minValueNode(AVL_Node2<k>* node) {
        AVL_Node2<k>* current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    group_node* search(AVL_Node2<k>* root, k key)
    {
        if (root == nullptr)
            return nullptr;

        if (key == root->key)
        {
            return root->head_of_user_list;
        }

        if (key < root->key)
            return  search(root->left, key);
        else
            return   search(root->right, key);
    }
public:
    //   Constructor
    AVL_tree2() : root(nullptr) {}
    AVL_tree2(AVL_Node2<k>* r) : root(r) {}

    AVL_Node2<k>* get_root()
    {
        return root;
    }

    // Insert a node
    void insert(k key, dllnode* userptr) {
        root = insert(root, key, userptr);
    }

    //Search and return a node
    //Useful for --> getting the AVL NODE in DLL_List class for insertion and deletion.
    group_node* searchkey(k key)
    {
        return search(root, key);
    }

    //  Delete a node
    void deleteKey(k key) {
        root = deleteNode(root, key);
    }

    //just a funcion to check
    void printinorder(AVL_Node2<k>* root)
    {
        if (root == 0)
            return;

        printinorder(root->left);

        cout << root->key << " : ";

        cout << "\n Inorder printing of user information :: \n";
        group_node* temp = root->head_of_user_list;//each node's user pointers containing same country/type
        while (temp != 0)
        {
            temp->userptr->User->display_user();
            temp = temp->next;
        }
        cout << "\n";
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
//==================================================================
//template based
class dlllist
{
    dllnode* head, * tail;
    AVL_tree1<int, dllnode*> index;//user-Id index

    AVL_tree2<string  > country_index;//key=country ,value=head of SLL of users list pointing to same country 
    AVL_tree2<string > type_index; //key=type ,value=head of SLL of users list pointing to same type
    bool  country_index_active;
    bool type_index_active;

    minheap<int, complaint*> heap;
public:
    dlllist() :head(nullptr), tail(nullptr), index(nullptr), country_index(nullptr), type_index(nullptr), country_index_active(false), type_index_active(false) {}

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
        AVL_Node1<int, dllnode* >* pred_node = index.getPredecessor(id);

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
        index.insert(id, newnode);//<key,userptr>

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
            delete node->User;
            delete node;
            head = tail = nullptr;

            //Deletion from AVL tree
            index.deleteKey(id);
            cout << "\n User with ID : " << id << " Successfully Deleted\n";

            return;
        }
        else if (node->prev == nullptr)
        {
            //if first node
            head = node->next;
            head->prev = nullptr;
        }
        else if (node->next == nullptr)
        {
            //if last node
            tail = node->prev;
            tail->next = nullptr;
        }
        else
        {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }

        delete node->User;
        delete node;
        node = nullptr;

        //Deletion from AVL tree
        index.deleteKey(id);
        cout << "\n User with ID : " << id << " Successfully Deleted\n";
    }
    void printAll() const
    {
        dllnode* temp = head;
        while (temp != nullptr)
        {
            temp->User->display_user();
            temp = temp->next;
        }
        // index.printinorder(index.root);
    }
    //-------------------------------------------------------------
        //Functionalities of question 3:

        //create functionalities
    void  create_country_group_index()
    {
        if (country_index_active == true)
        {
            cout << "\n country Group Index  already Active.No changes made.\n";
        }
        else
        {
            dllnode* curr = head;
            while (curr != nullptr)
            {
                country_index.insert(curr->User->get_country(), curr);//<key,userptr>
                curr = curr->next;
            }
            country_index_active = true;
        }
    }
    void create_type_group_index()
    {
        if (type_index_active == true)
        {
            cout << "\nType Group Index already Active.So, no changes made.\n";
        }
        else
        {
            dllnode* curr = head;
            while (curr != nullptr)
            {
                type_index.insert(curr->User->get_type(), curr);//<key,userptr>
                curr = curr->next;
            }
            type_index_active = true;
        }
    }
    //delete functionalities
    void delete_country_group_index()
    {
        if (country_index_active == false)
        {
            cout << "\n Country group index is already In-Active.\n";
        }
        else
        {
            //assigning new Empty AVL to country group index 
            country_index = AVL_tree2<string>();
            country_index_active = false;
        }
    }
    void delete_type_group_index()
    {
        if (type_index_active == false)
        {
            cout << "\n Type group index is already In-Active.\n";
        }
        else
        {
            //assigning new Empty AVL to type group index 
            type_index = AVL_tree2<string>();
            type_index_active = false;
        }
    }
    //listing functionalities
    void list_users_by_country(string country)
    {
        if (country_index_active == false)
        {
            cout << "\n Country group index is already In-Active.\n";
            return;
        }

        group_node* head = country_index.searchkey(country);
        if (head == nullptr)
        {
            cout << "\nNo users found for country\n";
            return;
        }

        cout << "Users form " << country << " are : \n";
        while (head)
        {
            head->userptr->User->display_user();
            head = head->next;
        }
    }
    void list_users_by_type(string type)
    {
        if (type_index_active == false)
        {
            cout << "\n Type group index is already In-Active.\n";
            return;
        }

        group_node* head = type_index.searchkey(type);
        if (head == nullptr)
        {
            cout << "\nNo users found for type\n";
            return;
        }

        cout << "Users form " << type << " are : \n";
        while (head)
        {
            head->userptr->User->display_user();
            head = head->next;
        }
    }
    //Display functionalities
    void display_country_group_index()
    {
        if (country_index_active == false)
        {
            cout << "\n Country group index is already In-Active.\n";
            return;
        }
        country_index.printinorder(country_index.get_root());
    }
    void display_type_group_index()
    {
        if (type_index_active == false)
        {
            cout << "\n Type group index is already In-Active.\n";
            return;
        }
        type_index.printinorder(type_index.get_root());
    }
    //=======================================================
    //q4::functionalities
    void register_complaints(complaint c)
    {
        dllnode* usernode = index.searchkey(c.get_userID());
        if (usernode == nullptr)
        {
            cout << "User ID not found.Complaint not registered.\n";
            return;
        }

        int user_priority = get_priority(usernode->User->get_type());

        //logic for complaints ID and usertype connection
        int priority_key = user_priority * 100000 + c.get_complaintID();

        complaint* c1 = new complaint(c.get_complaintID(),c.get_userID(),c.get_text());
        heap.insert(priority_key,c1);//min-heap uses key for ordering
        usernode->User->addcomplaint(c1);//link complaint to user

        cout << "Complaint with ID : " << c.get_complaintID() << " registered \n";
        heap.display();
    }
    void display_complaints_by_userID(int id)
    {
        dllnode* usernode = index.searchkey(id);
        if (usernode)
        {
            usernode->User->display_user();
            usernode->User->display_users_complaints();//-----------------------------
        }
        else
        {
            cout << "No user found with userID : " << id << endl;
        }
    }
    void display_complaints_by_country(string cntry)
    {
        group_node* head = country_index.searchkey(cntry);
        if (head==nullptr)
        {
            cout << "No user found for country \n";
            return;
        }
        else
        {
            cout << "Users from "<<cntry <<" and their complaints ::\n";
            while (head)
            {
                int id = head->userptr->User->getID();
                dllnode* usernode=index.searchkey(id);

                if (usernode)
                {
                    usernode->User->display_user();
                    usernode->User->display_users_complaints();
                }
                else
                {
                    cout << "No user found with userID : " << id << endl;
                }

                head = head->next;
            }
        }
    }
    void service_complaints()
    {
        if (heap.isEmpty())
        {
            cout << "No Complaints to service\n";
            return;
        }
        complaint* c;
        heap.getMin(c);
        cout << "Servicing Complaint : \n";
        c->display();

        heap.deleteMin();
    }
    void increase_priority(int complaint_id)
    {
        HeapItem<int, complaint*>* arr = heap.get_arr();
        int size = heap.get_total_items();

        for (int i = 0; i < size; i++)
        {
            if (arr[i].get_value()->get_complaintID() == complaint_id)
            {
                int old_key = arr[i].getkey();
                int newkey = old_key - 100000;//increase priority
                if (newkey < 0)
                {
                    newkey = 0;//prevent -ve priority
                    arr[i] = HeapItem<int, complaint*>(newkey, arr[i].get_value());
                    heap.reHeapUp(i);
                    heap.reHeapDown_minHeap(i, size - 1);

                    cout << "Priority increased fro complaint ID : " << complaint_id << endl;
                    return;
                }
            }
        }
        cout << "Complaint ID not found in heap\n";
    }
    void displayAllComplaints()
    {
        HeapItem<int, complaint*>* array = heap.get_arr();
        int size = heap.get_total_items();

        cout << "---All Complaints---\n";
        for (int i = 0; i < size; i++)
        {
            array[i].get_value()->display();
        }
    }
};

int main() {

    dlllist list_of_user;
    user* u1 = new user(001, "Saira", "saira.345@gmail.com", "US", "Silver");
    user* u2 = new user(002, "Ali", "ali.895@gmail.com", "US", "Platinum");
    user* u3 = new user(003, "Affan", "affaan.235@gmail.com", "US", "Silver");
    user* u4 = new user(004, "Reham", "reham.754@gmail.com", "India", "Gold");
    user* u5 = new user(005, "Sarim", "sarim.546@gmail.com", "Zambia", "Platinum");

    cout << "\n\n---All Users --- \n";
    list_of_user.AddUser(u1);
    list_of_user.AddUser(u2);
    list_of_user.AddUser(u3);
    list_of_user.AddUser(u4);
    list_of_user.AddUser(u5);
    list_of_user.printAll();
    cout << "\n----------------------------- \n";

    cout << "\n--- creating group index on country---  \n";
    list_of_user.create_country_group_index();
    cout << "\n----------------------------- \n";

    //-------------------------------------------------
    complaint c1(1001, 001, "Internet not working");
    complaint c2(1002, 004, "Billing issue");
    complaint c3(1003, 003, "Internet's slow speed");
    complaint c4(1004, 005, "Damaged ptcl");
    complaint c5(1005, 002, "Light issue");
    list_of_user.register_complaints(c1);
    list_of_user.register_complaints(c2);
    list_of_user.register_complaints(c3);
    list_of_user.register_complaints(c4);
    list_of_user.register_complaints(c5);

    cout << "\n-------------------------------\n";
    cout << "\n---Displaying Complaints on UserID---\n";
    list_of_user.display_complaints_by_userID(001);
    cout << "\n-------------------------------\n";
    cout << "\n---Displaying Complaints on Country---\n";
    list_of_user.display_complaints_by_country("India");
    cout << endl << endl;

    cout << "\n-------------------------------\n";
    list_of_user.increase_priority(1002);
    cout << endl << endl;

    cout << "\n-------------------------------\n";
    list_of_user.displayAllComplaints();
    cout << endl << endl;

    cout << "\n-------------------------------\n";
    list_of_user.service_complaints();
    cout << "\n-------------------------------\n";

    return 0;
}
