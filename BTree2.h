//#pragma once
//#include"LinkedList.h"
//
//template <class type>
//class Entry {
//public:
//    type Data;
//    LinkedList<type>* Links;
//    void DisplayKeys()
//    {
//        if (Links != nullptr)
//            Links->Display();
//    }
//    void InsertKey(const type val)
//    {
//        if (Links == nullptr)
//            Links = new LinkedList<type>;
//        Links->Insert(val);
//    }
//    void SaveKeys(ofstream& file)
//    {
//        if (Links == nullptr)
//            return;
//        Links->SaveFields(file);
//    }
//    void DeleteKeys()
//    {
//        if (Links == nullptr)
//            return;
//
//        type DatField;
//        while (!Links->IsEmpty())
//        {
//            DatField = Links->Front();
//            DatField.Overwrite();
//            Links->Delete();
//        }
//    }
//    bool operator==(const Entry<type> Other) const
//    {
//        return Data = Other.Data;
//    }
//    //BTNode<type>* BreakLink(const type del, const int t)
//    //{
//    //    //if (this->Data.MatchAll(del))
//    //    //{
//    //    //    if (Links == nullptr)
//    //    //        return 1;
//
//    //    //    Data = Links.Front();
//    //    //    Links->Delete();
//    //    //    return 0;
//    //    //}
//    //    //Keys->DeleteValue(del);
//    //    //return 0;
//    //}
//    void BreakLink(const string del, const int num)
//    {
//
//    }
//    void DisplaySpKeys(const string& val, const int& FieldNumber)
//    {
//        if (Links == nullptr) return;
//        Links->DisplaySpFields(val, FieldNumber);
//    }
//    type SearchKeys(const string& val, const int FieldNumber)
//    {
//        if (Links == nullptr)	return type();
//        return Links->SearchFields(val, FieldNumber);
//    }
//};
//
//
//
//template <class data>
//class BTNode {
//public:
//    data* keys;
//    int t;
//    BTNode** C;
//    int n;
//    bool leaf;
//
//public:
//    BTNode(int _t, bool _leaf);
//
//    void traverse();
//
//    int findKey(data k);
//    void insertNonFull(data k);
//    void splitChild(int i, BTNode<data>* y);
//    void Delete(data k);
//    void removeFromLeaf(int idx);
//    void removeFromNonLeaf(int idx);
//    data getPredecessor(int idx);
//    data getSuccessor(int idx);
//    void fill(int idx);
//    void borrowFromPrev(int idx);
//    void borrowFromNext(int idx);
//    void merge(int idx);
//
//
//    BTNode<data>* SearchNode(data k);
//   
//    template <class data> friend class BTree;
//};
//
//template <class data>
//class BTree {
//    BTNode<data>* root;
//    const string DefinedBy;
//    int t;
//
//    void RecursiveSearch(BTNode<data>* curr, const data val);
//    BTNode<data>* search(data k);
//
//    typedef BTNode<data>* BTPtr;
//
//public:
//    BTree(int _t, const string str);
//
//    void traverse();
//
//    void Search(data k);
//    void Insert(data k);
//    void Delete(data k);
//
//    void LoadTree();
//    void SaveTree();
//    string GetDefinedBy() { return DefinedBy; }
//
//    BTNode<data>* Retrieve(data k, int& idx)
//    {
//        BTNode<data>* curr = search(k);
//        if (curr == nullptr)
//            return nullptr;
//        for (int i = 0; i < t; i++)
//            if (curr->keys[i] == data())
//                return nullptr;
//            else if (curr->keys[i] == k)
//            {
//                idx = i;
//                break;
//            }
//        return curr;
//    }
//};
//
//// B tree node
//template <class data>
//BTNode<data>::BTNode(int t1, bool leaf1) {
//    t = t1;
//    leaf = leaf1;
//
//    keys = new data[2 * t - 1];
//    C = new BTNode<data> *[2 * t];
//
//    n = 0;
//}
//
//template <class data>
//BTNode<data>* BTNode<data>::SearchNode(data k) {
//    int i = 0;
//    while (i < n && k > keys[i])
//        i++;
//
//    if (keys[i] == k)
//        return this;
//
//    if (leaf == true)
//        return NULL;
//
//    return C[i]->SearchNode(k);
//}
//
//// Find the key
//template <class data>
//int BTNode<data>::findKey(data k) {
//    int idx = 0;
//    while (idx < n && keys[idx] < k)
//        ++idx;
//    return idx;
//}
//
//// Delete operation
//template <class data>
//void BTNode<data>::Delete(data k) {
//    int idx = findKey(k);
//
//    if (idx < n && keys[idx] == k) {
//        if (leaf)
//            removeFromLeaf(idx);
//        else
//            removeFromNonLeaf(idx);
//    }
//    else {
//        if (leaf) {
//            return;
//        }
//
//        bool flag = ((idx == n) ? true : false);
//
//        if (C[idx]->n < t)
//            fill(idx);
//
//        if (flag && idx > n)
//            C[idx - 1]->Delete(k);
//        else
//            C[idx]->Delete(k);
//    }
//    return;
//}
//
//// Remove from the leaf
//template <class data>
//void BTNode<data>::removeFromLeaf(int idx) {
//    keys[idx].Overwrite();
//    for (int i = idx + 1; i < n; ++i)
//        keys[i - 1] = keys[i];
//
//    n--;
//
//    return;
//}
//
//// Delete from non leaf node
//template <class data>
//void BTNode<data>::removeFromNonLeaf(int idx) {
//    data k = keys[idx];
//
//    if (C[idx]->n >= t) {
//        data pred = getPredecessor(idx);
//        keys[idx] = pred;
//        C[idx]->Delete(pred);
//    }
//
//    else if (C[idx + 1]->n >= t) {
//        data succ = getSuccessor(idx);
//        keys[idx] = succ;
//        C[idx + 1]->Delete(succ);
//    }
//
//    else {
//        merge(idx);
//        C[idx]->Delete(k);
//    }
//    return;
//}
//template <class data>
//data BTNode<data>::getPredecessor(int idx) {
//    BTNode<data>* cur = C[idx];
//    while (!cur->leaf)
//        cur = cur->C[cur->n];
//
//    return cur->keys[cur->n - 1];
//}
//template <class data>
//data BTNode<data>::getSuccessor(int idx) {
//    BTNode<data>* cur = C[idx + 1];
//    while (!cur->leaf)
//        cur = cur->C[0];
//
//    return cur->keys[0];
//}
//template <class data>
//void BTNode<data>::fill(int idx) {
//    if (idx != 0 && C[idx - 1]->n >= t)
//        borrowFromPrev(idx);
//
//    else if (idx != n && C[idx + 1]->n >= t)
//        borrowFromNext(idx);
//
//    else {
//        if (idx != n)
//            merge(idx);
//        else
//            merge(idx - 1);
//    }
//    return;
//}
//
//// Borrow from previous
//template <class data>
//void BTNode<data>::borrowFromPrev(int idx) {
//    BTNode<data>* child = C[idx];
//    BTNode<data>* sibling = C[idx - 1];
//
//    for (int i = child->n - 1; i >= 0; --i)
//        child->keys[i + 1] = child->keys[i];
//
//    if (!child->leaf) {
//        for (int i = child->n; i >= 0; --i)
//            child->C[i + 1] = child->C[i];
//    }
//
//    child->keys[0] = keys[idx - 1];
//
//    if (!child->leaf)
//        child->C[0] = sibling->C[sibling->n];
//
//    keys[idx - 1] = sibling->keys[sibling->n - 1];
//
//    child->n += 1;
//    sibling->n -= 1;
//
//    return;
//}
//
//// Borrow from the next
//template <class data>
//void BTNode<data>::borrowFromNext(int idx) {
//    BTNode<data>* child = C[idx];
//    BTNode<data>* sibling = C[idx + 1];
//
//    child->keys[(child->n)] = keys[idx];
//
//    if (!(child->leaf))
//        child->C[(child->n) + 1] = sibling->C[0];
//
//    keys[idx] = sibling->keys[0];
//
//    for (int i = 1; i < sibling->n; ++i)
//        sibling->keys[i - 1] = sibling->keys[i];
//
//    if (!sibling->leaf) {
//        for (int i = 1; i <= sibling->n; ++i)
//            sibling->C[i - 1] = sibling->C[i];
//    }
//
//    child->n += 1;
//    sibling->n -= 1;
//
//    return;
//}
//
//// Merge
//template <class data>
//void BTNode<data>::merge(int idx) {
//    BTNode<data>* child = C[idx];
//    BTNode<data>* sibling = C[idx + 1];
//
//    child->keys[t - 1] = keys[idx];
//
//    for (int i = 0; i < sibling->n; ++i)
//        child->keys[i + t] = sibling->keys[i];
//
//    if (!child->leaf) {
//        for (int i = 0; i <= sibling->n; ++i)
//            child->C[i + t] = sibling->C[i];
//    }
//
//    for (int i = idx + 1; i < n; ++i)
//        keys[i - 1] = keys[i];
//
//    for (int i = idx + 2; i <= n; ++i)
//        C[i - 1] = C[i];
//
//    child->n += sibling->n + 1;
//    n--;
//
//    delete (sibling);
//    return;
//}
//
//template<class data>
//inline void BTree<data>::RecursiveSearch(BTNode<data>* curr, const data val)
//{
// //   	if (curr == nullptr)
//	//	return nullptr;
//	//else if (curr->SearchKeys(val))
//	//	return curr;
//	//else if (val < curr->MinKey() )
//	//	return RecursiveSearch(curr->C[0], val);
//	//else if (val > curr->MaxKey())
//	//	return RecursiveSearch(curr->C[curr->ChildIndex-1], val);
//	//else
//	//{
//	//	for (int i = 0; i < curr->KeyIndex - 1; i++)
//	//		if (val > curr->Keys[i] && val < curr->Keys[i + 1])
//	//			return RecursiveSearch(curr->Children[i+1], val);
//	//}
//}
//
//template<class data>
//inline BTNode<data>* BTree<data>::search(data k)
//{
//    if (root == nullptr) {
//        return nullptr;
//    }
//    else {
//        return root->SearchNode(k);
//    }
//}
//
//template<class data>
//inline BTree<data>::BTree(int _t, const string str) : DefinedBy(str)
//{
//    root = NULL;
//    t = _t;
//}
//
//template<class data>
//inline void BTree<data>::traverse()
//{
//    if (root != NULL)
//        root->traverse();
//}
//
//template<class data>
//inline void BTree<data>::Search(data k)
//{
//    BTNode<data>* curr = search(k);
//    if (curr == nullptr)return;
//    for (int i = 0; i < t; i++)
//        if(curr->keys[i] == NULL)
//            break;
//        else 
//          if (curr->keys[i] == k) {
//            cout << curr->keys[i]; break;
//        }
//}
//
//// Insert operation
//template <class data>
//void BTree<data>::Insert(data k) {
//    if (root == NULL) {
//        root = new BTNode<data>(t, true);
//        root->keys[0] = k;
//        root->n = 1;
//    }
//    else {
//        if (root->n == 2 * t - 1) {
//            BTNode<data>* s = new BTNode<data>(t, false);
//
//            s->C[0] = root;
//
//            s->splitChild(0, root);
//
//            int i = 0;
//            if (s->keys[0] < k)
//                i++;
//            s->C[i]->insertNonFull(k);
//
//            root = s;
//        }
//        else
//            root->insertNonFull(k);
//    }
//}
//
//// Insert non full
//template <class data>
//void BTNode<data>::insertNonFull(data k) {
//    int i = n - 1;
//
//    if (leaf == true) {
//        while (i >= 0 && keys[i] > k) {
//            keys[i + 1] = keys[i];
//            i--;
//        }
//
//        keys[i + 1] = k;
//        n = n + 1;
//    }
//    else {
//        while (i >= 0 && keys[i] > k)
//            i--;
//
//        if (C[i + 1]->n == 2 * t - 1) {
//            splitChild(i + 1, C[i + 1]);
//
//            if (keys[i + 1] < k)
//                i++;
//        }
//        C[i + 1]->insertNonFull(k);
//    }
//}
//
//// Split child
//template <class data>
//void BTNode<data>::splitChild(int i, BTNode<data>* y) {
//    BTNode<data>* z = new BTNode<data>(y->t, y->leaf);
//    z->n = t - 1;
//
//    for (int j = 0; j < t - 1; j++)
//        z->keys[j] = y->keys[j + t];
//
//    if (y->leaf == false) {
//        for (int j = 0; j < t; j++)
//            z->C[j] = y->C[j + t];
//    }
//
//    y->n = t - 1;
//
//    for (int j = n; j >= i + 1; j--)
//        C[j + 1] = C[j];
//
//    C[i + 1] = z;
//
//    for (int j = n - 1; j >= i; j--)
//        keys[j + 1] = keys[j];
//
//    keys[i] = y->keys[t - 1];
//
//    n = n + 1;
//}
//
//// Traverse
//template <class data>
//void BTNode<data>::traverse() {
//    int i;
//    for (i = 0; i < n; i++) {
//        if (leaf == false)
//            C[i]->traverse();
//        cout << " " << keys[i];
//    }
//
//    if (leaf == false)
//        C[i]->traverse();
//}
//
//// Delete Operation
//template <class data>
//void BTree<data>::Delete(data k) {
//    if (!root) {
//        cout << "The tree is empty\n";
//        return;
//    }
//
//    root->Delete(k);
//
//    if (root->n == 0) {
//        BTNode<data>* tmp = root;
//        
//
//        if (root->leaf)
//            root = nullptr;
//        else
//            root = root->C[0];
//
//
//        delete tmp;
//    }
//    return;
//}
//
//
//template<class data>
//inline void BTree<data>::LoadTree()
//{
//    string filename = "IndexTrees/AVLTree_" + DefinedBy + ".csv";
//    ifstream file(filename, ios::in);
//    if (file.fail())
//    {
//        cout << "Unable to Open File" << endl;
//        return;
//    }
//
//    data Record;
//    string RecordData;
//    while (!file.eof())
//    {
//        getline(file, RecordData);
//        Record = CreateLoadNode(RecordData, Record.Data);
//        Insert(Record);
//    }
//    file.close();
//}
//template<class data>
//inline void BTree<data>::SaveTree()
//{
//    ofstream file("IndexTrees/BTree_" + DefinedBy + ".csv", ios::out);
//    if (file.fail())
//    {
//        cout << "Unable to Open File" << endl;
//        return;
//    }
//
//    string Record;
//    Queue<BTPtr> Que;
//    BTNode<data>* curr = root;
//    Que.Enqueue(curr);
//
//    while (!Que.IsEmpty())
//    {
//        curr = Que.Peek();
//        Que.Dequeue();
//
//        for (int i = 0; i < t; i++)
//        {
//            Record = CreateRecord(curr->keys[i]);
//            file.write(Record.c_str(), Record.size());
//        }
//
//        for (int i = 0; i < curr->n; i++)
//            if (curr->C[i] != nullptr)
//                Que.Enqueue(curr->C[i]);
//
//    }
//
//    file.close();
//}
//
////template<class data> inline Field<data>
////SearchKeys(BTNode<Field<data>>* Node, const string& OldVal, const int FieldNumber, const string& field, const int idx, const string& DefinedBy)
////{
////	if (Node->keys == nullptr || field == DefinedBy)
////		return Node->keys[idx];
////
////	string Tuple = Node->keys[idx].ReadTuple(), Record, CurrentVal;
////
////	Field<data> curr = Node->keys[idx];
////	Tuple = curr.ReadTuple();
////	CurrentVal = CurrFieldEntry(Tuple, FieldNumber);
////	if (CompareStr(CurrentVal, OldVal))
////		return curr;
////
////	return Field<data>();
////	return Node->Keys->SearchFields(OldVal, FieldNumber);
////}