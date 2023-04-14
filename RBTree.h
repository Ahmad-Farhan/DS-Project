#pragma once
#include "Queue.h"
#include "LinkedList.h"

template <class data>
class RBNode {
public:
    data Data;
    RBNode* parent;
    RBNode* left;
    RBNode* right;
    int color;

    LinkedList<data>* Keys = nullptr;

    void DisplayKeys()
    {
        if (Keys != nullptr)
            Keys->Display();
    }
    void InsertKey(const data val)
    {
        if (Keys == nullptr)
            Keys = new LinkedList<data>;
        Keys->Insert(val);
    }
    void SaveKeys(ofstream& file)
    {
        if (Keys == nullptr)
            return;
        Keys->SaveFields(file);
    }
    void DeleteKeys()
    {
        if (Keys == nullptr)
            return;

        data DatField;
        while (!Keys->IsEmpty())
        {
            DatField = Keys->Front();
            DatField.Overwrite();
            Keys->Delete();
        }
    }
    RBNode<data> BreakLink(const data del, const int type)
    {
        if (this->Data.MatchAll(del))
        {
            if (Keys == nullptr)
                return 1;

            Data = Keys.Front();
            Keys->Delete();
            return 0;
        }
        Keys->DeleteValue(del);
        return 0;
    }
    void BreakLink(const string del, const int num)
    {
        //string str;
        //ReadData(*this, str);


        //while()

        //if (this->Data.MatchAll(del))
        //{
        //	if (Keys == nullptr)
        //		return 1;

        //	Data = Keys.Front();
        //	Keys->Delete();
        //	return 0;
        //}
        //Keys->DeleteValue(del);
        //return 0;
    }
    void DisplaySpKeys(const string& val, const int& FieldNumber)
    {
        if (Keys == nullptr) return;
        Keys->DisplaySpFields(val, FieldNumber);
    }
    data SearchKeys(const string& val, const int FieldNumber)
    {
        if (Keys == nullptr)	return data();
        return Keys->SearchFields(val, FieldNumber);
    }
};

template <class data>
class RBTree {
private:
    typedef RBNode<data>* NodePtr;
    NodePtr root;
    NodePtr TNULL;
    const string DefinedBy;

    void initializeNULLNode(NodePtr , NodePtr );
    void preOrderHelper(NodePtr );
    void inOrderHelper(NodePtr );
    void postOrderHelper(NodePtr );
    void deleteFix(NodePtr);
    void insertFix(NodePtr k);
    NodePtr searchTreeHelper(NodePtr& ,const data& );
    void deleteNodeHelper(NodePtr , data );
    void rbTransplant(NodePtr , NodePtr );
    void printHelper(NodePtr , string , bool );
    void rangeSearchHelper(const RBNode<data>*, const data, const data);

public:
    RBTree(const string&);

    NodePtr getRoot();
    const bool IsNull();
    string GetDefinedBy();

    void preorder();
    void inorder();
    void postorder();

    void RangeSearch(const data, const data);

    NodePtr Retrieve(const data);
    NodePtr minimum(NodePtr curr);
    NodePtr maximum(NodePtr curr);
    NodePtr successor(NodePtr x);
    NodePtr predecessor(NodePtr x);
    void leftRotate(NodePtr x);
    void rightRotate(NodePtr x);

    void Insert(const data );
    void Delete(const data );
    void Search(const data );
    void printTree();

    void SaveTree();
    void LoadTree();
    ~RBTree();
};

template<class data>
inline void RBTree<data>::initializeNULLNode(NodePtr curr, NodePtr parent)
{
        curr->Data = 0;
        curr->parent = parent;
        curr->left = nullptr;
        curr->right = nullptr;
        curr->color = 0;
}

template<class data>
inline void RBTree<data>::preOrderHelper(NodePtr curr)
{
    if (curr != TNULL) {
        cout << curr->Data << " ";
        preOrderHelper(curr->left);
        preOrderHelper(curr->right);
    }
}

template<class data>
inline void RBTree<data>::inOrderHelper(NodePtr curr)
{
    if (curr != TNULL) {
        inOrderHelper(curr->left);
        cout << curr->Data << " ";
        inOrderHelper(curr->right);
    }
}

template<class data>
inline void RBTree<data>::postOrderHelper(NodePtr curr)
{
    if (curr != TNULL) {
        postOrderHelper(curr->left);
        postOrderHelper(curr->right);
        cout << curr->Data << " ";
    }
}

template<class data>
inline void RBTree<data>::deleteFix(NodePtr x)
{
    NodePtr s;
    while (x != root && x->color == 0) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == 1) {
                s->color = 0;
                x->parent->color = 1;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == 0 && s->right->color == 0) {
                s->color = 1;
                x = x->parent;
            }
            else {
                if (s->right->color == 0) {
                    s->left->color = 0;
                    s->color = 1;
                    rightRotate(s);
                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = 0;
                s->right->color = 0;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            s = x->parent->left;
            if (s->color == 1) {
                s->color = 0;
                x->parent->color = 1;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == 0 && s->right->color == 0) {
                s->color = 1;
                x = x->parent;
            }
            else {
                if (s->left->color == 0) {
                    s->right->color = 0;
                    s->color = 1;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = 0;
                s->left->color = 0;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 0;
}

template<class data>
inline void RBTree<data>::insertFix(NodePtr k)
{
    NodePtr u;
    while (k->parent->color == 1) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == 1) {
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = 0;
                k->parent->parent->color = 1;
                leftRotate(k->parent->parent);
            }
        }
        else {
            u = k->parent->parent->right;

            if (u->color == 1) {
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = 0;
                k->parent->parent->color = 1;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = 0;
}

template<class data>
inline RBNode<data>* RBTree<data>::searchTreeHelper(NodePtr& curr, const data& key)
{
    if (curr == TNULL || key == curr->Data)
        return curr;

     if (key < curr->Data) 
        return searchTreeHelper(curr->left, key);
    
    return searchTreeHelper(curr->right, key);
}
template<class data>
inline void RBTree<data>::deleteNodeHelper(NodePtr curr, data key)
{
    NodePtr z = TNULL;
    NodePtr x, y;
    while (curr != TNULL) {
        if (curr->Data == key) {
            z = curr;
        }

        if (curr->Data <= key) {
            curr = curr->right;
        }
        else {
            curr = curr->left;
        }
    }

    if (z == TNULL) {
        cout << "Key not found in the tree" << endl;
        return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
        x = z->right;
        rbTransplant(z, z->right);
    }
    else if (z->right == TNULL) {
        x = z->left;
        rbTransplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    z->Data.Overwrite();
    z->DeleteKeys();
    delete z;
    if (y_original_color == 0) {
        deleteFix(x);
    }
}

template<class data>
inline void RBTree<data>::rbTransplant(NodePtr u, NodePtr v)
{
    if (u->parent == nullptr) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

template<class data>
inline void RBTree<data>::printHelper(NodePtr root, string indent, bool last)
{
    if (root != TNULL) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        }
        else {
            cout << "L----";
            indent += "|  ";
        }

        string sColor = root->color ? "RED" : "BLACK";
        cout << root->Data << "(" << sColor << ")" << endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
}

template<class data>
inline RBTree<data>::RBTree(const string& str) :DefinedBy(str)
{
    TNULL = new RBNode<data>;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}

template<class data>
inline RBNode<data>* RBTree<data>::getRoot()
{
    return root;
}

template<class data>
inline const bool RBTree<data>::IsNull()
{
    return root == TNULL;
}

template<class data>
inline void RBTree<data>::preorder()
{
    preOrderHelper(this->root);
}

template<class data>
inline void RBTree<data>::inorder()
{
    inOrderHelper(this->root);
}

template<class data>
inline void RBTree<data>::postorder()
{
    postOrderHelper(this->root);
}

template<class data>
inline void RBTree<data>::Search(const data k)
{
    cout << "Searching for " << DefinedBy << " : " << k.Data << endl;
    NodePtr curr = searchTreeHelper(this->root, k);
    if (curr == nullptr)
        return;
    else if (curr->Data == data())
        return;
    cout << curr->Data << endl;
    curr->DisplayKeys();
}

template<class data>
inline RBNode<data>* RBTree<data>::Retrieve(const data k)
{
    return searchTreeHelper(this->root, k);
}

template<class data>
inline void RBTree<data>::RangeSearch(const data Min, const data Max)
{
    rangeSearchHelper(root, Min, Max);
}

template<class data>
inline RBNode<data>* RBTree<data>::minimum(NodePtr curr)
{
    while (curr->left != TNULL) {
        curr = curr->left;
    }
    return curr;
}

template<class data>
inline RBNode<data>* RBTree<data>::maximum(NodePtr curr)
{
    while (curr->right != TNULL) {
        curr = curr->right;
    }
    return curr;
}

template<class data>
inline RBNode<data>* RBTree<data>::successor(NodePtr x)
{
    if (x->right != TNULL) {
        return minimum(x->right);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

template<class data>
inline RBNode<data>* RBTree<data>::predecessor(NodePtr x)
{
    if (x->left != TNULL) {
        return maximum(x->left);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->left) {
        x = y;
        y = y->parent;
    }

    return y;
}

template<class data>
inline void RBTree<data>::leftRotate(NodePtr x)
{
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template<class data>
inline void RBTree<data>::rightRotate(NodePtr x)
{
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

template<class data>
inline void RBTree<data>::Insert(const data key)
{
    NodePtr curr = new RBNode<data>;
    curr->parent = nullptr;
    curr->Data = key;
    curr->left = TNULL;
    curr->right = TNULL;
    curr->color = 1;

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL) {
        y = x;
        if (key < x->Data) {
            x = x->left;
        }
        else if (x->Data == key) {
            x->InsertKey(key);
            return;
        }
        else if (key > x->Data) {
            x = x->right;
        }
    }
    curr->parent = y;
    if (y == nullptr) {
        root = curr;
    }
    else if (curr->Data < y->Data) {
        y->left = curr;
    }
    else {
        y->right = curr;
    }

    if (curr->parent == nullptr) {
        curr->color = 0;
        return;
    }

    if (curr->parent->parent == nullptr) {
        return;
    }

    insertFix(curr);
}
template<class data>
inline string RBTree<data>::GetDefinedBy()
{
    return DefinedBy;
}


template<class data>
inline void RBTree<data>::Delete(const data key)
{
    deleteNodeHelper(this->root, key);
    this->SaveTree();
}

template<class data>
inline void RBTree<data>::printTree()
{
    if (root) {
        printHelper(this->root, "", true);
    }
}

template<typename data>
inline void RBTree<data>::rangeSearchHelper(const RBNode<data>* curr, const data Min, const data Max)
{
    if (curr == nullptr)
        return;

    if (curr->Data > Min)
        rangeSearchHelper(curr->left, Min, Max);

    if (curr->Data < Max && curr->Data > Min)
    {
        cout << curr->Data << endl;
        if (curr->Keys != nullptr)
            curr->Keys->Display();
    }
    rangeSearchHelper(curr->right, Min, Max);
}

template<class data>
inline void RBTree<data>::SaveTree()
{
    ofstream file("IndexTrees/RBTree_" + DefinedBy + ".csv", ios::out);
    if (file.fail())
    {
        cout << "Unable to Open File" << endl;
        return;
    }

    string Record;
    Queue<NodePtr> Que;
    RBNode<data>* curr = root;
    Que.Enqueue(curr);

    while (!Que.IsEmpty())
    {
        curr = Que.Peek();
        Que.Dequeue();

        Record = CreateRecord(curr->Data);
        file.write(Record.c_str(), Record.size());
        curr->SaveKeys(file);


        if (curr->left != nullptr)
            Que.Enqueue(curr->left);
        if (curr->right != nullptr)
            Que.Enqueue(curr->right);
    }

    file.close();
}

template<class data>
inline void RBTree<data>::LoadTree()
{
    string filename = "IndexTrees/RBTree_" + DefinedBy + ".csv";
    ifstream file(filename, ios::in);
    if (file.fail())
    {
        cout << "Unable to Open File" << endl;
        return;
    }

    data Record;
    string RecordData;
    while (!file.eof())
    {
        getline(file, RecordData);
        Record = CreateLoadNode(RecordData, Record.Data);
        Insert(Record);
    }
    file.close();
}

template<class data>
inline RBTree<data>::~RBTree()
{
    if (root == nullptr)
        return;

    Queue<NodePtr> Que;
    RBNode<data>* curr = root;
    Que.Enqueue(curr);

    while (!Que.IsEmpty())
    {
        curr = Que.Peek();
        Que.Dequeue();

        if (curr->left != TNULL)
            Que.Enqueue(curr->left);
        if (curr->right != TNULL)
            Que.Enqueue(curr->right);

        delete curr;
    }
}

