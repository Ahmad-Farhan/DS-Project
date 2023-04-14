#pragma once
#include "LinkedList.h"

template <class data>
class BTree;

template <class data>
class BTNode {
public:
	data* Keys;
	BTNode<data>** Children;
	LinkedList<data>** Links;
	short int KeyIndex;
	short int ChildIndex;
	const short int Order;

	ostream& operator<<(ostream& output)
	{
		output << this->ID;
		this->DisplayKeys();
	}
	void InitLinks();
	void InitChildren();
	void InsertSorted(BTNode<data>**& Arr, const int Index);
	void ClearNulls(BTNode<data>**&, short int&);
public:
	BTNode(const int);
	BTNode(const int, const data);
	void InsertKey(const data);
	void InsertKey(const data, LinkedList<data>*&);
	void InsertLink(const data val);
	void InsertChild(BTNode<data>*);
	void DeleteChild(const int);
	int DeleteKey(const data);

	const data MidKey();
	const data MaxKey();
	const data MinKey();
	bool SearchKeys(const data val);
	bool NoChildSpace();
	bool NoKeySpace();
	bool KeysFull();
	bool ChildrenFull();
	bool IsLeafNode();
	void MergeNodes(BTNode<data>*);

	void DeleteLinks(const int);
	void DisplaySpecific(const data);
	void DisplayKeys();
	void Display();
	~BTNode();

	friend const Field<int> DefKey(BTNode<data>* Child, Field<int>);
	friend const Field<char> DefKey(BTNode<data>* Child, Field<char>);
	friend const Field<double> DefKey(BTNode<data>* Child, Field<double>);
	friend const Field<string> DefKey(BTNode<data>* Child, Field<string>);
	friend class BTree<data>;
};

template<class data>
inline void BTNode<data>::InitLinks()
{
	for (int i = 0; i < Order; i++)
		Links[i] = nullptr;
}

template<class data>
inline void BTNode<data>::InitChildren()
{
	for (int i = 0; i <= Order; i++)
		Children[i] = nullptr;
}

inline const Field<int> DefKey(BTNode<Field<int>>* Child, Field<int>)
{
	if (Child == nullptr) return 1000000;
	if (Child->Keys == nullptr) return 10000000;
	else return Child->Keys[0];
}

inline const Field<double> DefKey(BTNode<Field<double>>* Child, Field<double>)
{
	if (Child == nullptr) return 1000000;
	if (Child->Keys == nullptr) return 10000000;
	else return Child->Keys[0];
}

inline const Field<string> DefKey(BTNode<Field<string>>* Child, Field<string>)
{
	if (Child == nullptr) return string("AAAAAAAAAAAAAAA");
	if (Child->Keys == nullptr) return string("AAAAAAAAAAAAAAAAA");
	else return Child->Keys[0];
}

inline const Field<char> DefKey(BTNode<Field<char>>* Child, Field<char>)
{
	if (Child == nullptr) return 256;
	if (Child->Keys == nullptr) return 256;
	else return Child->Keys[0];
}

template<class data>
inline void SortedInsertion(data*& Array, LinkedList<data>**& links,int index)		//SortsKeys
{
	data temp;
	LinkedList<data>* tlink;
	while (index > 0 && (Array[index] < Array[index - 1] || Array[index-1] < data()))
	{
		temp = Array[index];
		Array[index] = Array[index - 1];
		Array[index - 1] = temp;

		tlink = links[index];
		links[index] = links[index - 1];
		links[index - 1] = tlink;

		index--;
	}
}

inline void SortedInsertion(Field<string>*& Array, LinkedList<Field<string>>**& links, int index)		//SortsKeys
{
	Field<string> temp;
	LinkedList<Field<string>>* tlink;
	while (index > 0 && (Array[index] < Array[index - 1]))
	{
		temp = Array[index];
		Array[index] = Array[index - 1];
		Array[index - 1] = temp;

		tlink = links[index];
		links[index] = links[index - 1];
		links[index - 1] = tlink;

		index--;
	}
}

template <class data>
void ShiftRight(BTNode<data>**& Array, const int index, const int size)
{
	BTNode<data>* temp;
	for (int i = size; i >= index; i--)
		Array[i] = Array[i - 1];
}

template <class data>
void ShiftLeft(BTNode<data>**& Array, const int index, const int size)
{
	BTNode<data>* temp;
	for (int i = index; i < size - 1; i++)
		Array[i] = Array[i + 1];
	Array[size - 1] = nullptr;
}

template <class data>
void ShiftLeft(data*& Array, LinkedList<data>**& links,const int index, int size)
{
	for (int i = index; i < size - 1; i++)
	{
		Array[i] = Array[i + 1];
		links[i] = links[i + 1];
	}
	//links[size - 1].~LinkedList();			//
	links[size - 1] = nullptr;
	Array[size - 1] = 0;
	size--;
}

template <class data>
inline void BTNode<data>::InsertSorted(BTNode<data>**& Array, int index)	//SortsChildren
{
	bool Swap = false;
	BTNode<data>* temp;

	for (int i = 0; i < index; i++)
		for (int j = i + 1; j < index; j++)
			if (Array[j] == nullptr)
				continue;
			else if (DefKey(Array[i], data()) > DefKey(Array[j], data()))
			{
				temp = Array[i];
				Array[i] = Array[j];
				Array[j] = temp;
			}
}


template<class data>
inline BTNode<data>::BTNode(const int size) : Order(size)
{
	Keys = new data[Order];
	Links = new LinkedList<data>*[Order];
	Children = new BTNode<data> *[Order+1];
	KeyIndex = 0;
	InitLinks();
	ChildIndex = 0;
	InitChildren();
}

template<class data>
inline BTNode<data>::BTNode(const int size, const data InitVal) : Order(size)
{
	Keys = new data[Order];
	Links = new LinkedList<data>*[Order];
	Children = new BTNode<data> *[Order+1];
	KeyIndex = 0;
	ChildIndex = 0;
	InitLinks();
	InitChildren();
	InsertKey(InitVal);
}

template<class data>
inline void BTNode<data>::InsertKey(const data val)
{
	if (NoKeySpace())
		return;

	Keys[KeyIndex++] = val;
	SortedInsertion(Keys, Links, KeyIndex - 1);
}

template<class data>
inline void BTNode<data>::InsertKey(const data val, LinkedList<data>*& link)
{
	if (NoKeySpace())
		return;

	Links[KeyIndex] = link;
	//link = nullptr;
	Keys[KeyIndex++] = val;
	SortedInsertion(Keys, Links, KeyIndex - 1);
}

template<class data>
inline void BTNode<data>::InsertLink(const data val)
{
	for (int i = 0; i < KeyIndex; i++)
		if (Keys[i] == val)
		{
			if (Links[i] == nullptr)
				Links[i] = new LinkedList<data>;
			Links[i]->Insert(val);
			break;
		}
}

template <class data>
void BTNode<data>::ClearNulls(BTNode<data>**& Array, short int& index)
{
	for (int i = 0; i < index; i++)
		if (Array[i] == nullptr)
			ShiftLeft(Array, i, index);
}

template<class data>
inline void BTNode<data>::InsertChild(BTNode<data>* curr)
{
	if (NoChildSpace())
		return;

	Children[ChildIndex++] = curr;

	if (curr == nullptr) ChildIndex--;
	ClearNulls(Children, ChildIndex);
	InsertSorted(Children, ChildIndex);
}

template <class data>
void FillDeletionSpace(BTNode<data>**& Array, int StartIndex, const int size)
{
	for (; StartIndex < size; StartIndex++)
		Array[StartIndex] = Array[StartIndex + 1];
	Array[StartIndex+1] = nullptr;
}

template<class data>
inline void BTNode<data>::DeleteChild(const int index)
{
	if (index >= ChildIndex)
		return;
	cout << "Deleteing : "; Children[index]->Display();cout << endl;

	delete Children[index];
	Children[index] = nullptr;
	FillDeletionSpace(Children, index, ChildIndex);
	ChildIndex--;
}

template<class data>
inline int BTNode<data>::DeleteKey(const data val)
{
	for (int i = 0; i < KeyIndex; i++)
		if (Keys[i] == val)
		{
			Keys[i].Overwrite();
			DeleteLinks(i);
			Links[i] = nullptr;
			//ShiftLeft(Keys, i, KeyIndex--);
			return i;
		}
}

template<class data>
inline const data BTNode<data>::MidKey()
{
	if (Keys == nullptr)
		return data();
	return Keys[KeyIndex/2];
}

template<class data>
inline const data BTNode<data>::MaxKey()
{
	if (Keys == nullptr)
		return data();
	return Keys[KeyIndex - 1];
}

template<class data>
inline const data BTNode<data>::MinKey()
{
	if (Keys == nullptr)
		return data();
	return Keys[0];
}

template <class data>
bool AllRightNull(BTNode<data>**& Array, const int index, const int size)
{
	for (int i = index; i < size; i++)
		if (Array[i] != nullptr)
			return false;
	return true;
}

template<class data>
inline bool BTNode<data>::SearchKeys(const data val)
{
	for (int i = 0; i < KeyIndex; i++)
		if (val == Keys[i])
			return true;
	return false;
}

template<class data>
inline bool BTNode<data>::NoChildSpace()
{
	return (KeyIndex == Order+1);
}

template<class data>
inline bool BTNode<data>::NoKeySpace()
{
	return (KeyIndex == Order);
}

template<class data>
inline bool BTNode<data>::KeysFull()
{
	return (KeyIndex == Order - 1);
}

template<class data>
inline bool BTNode<data>::ChildrenFull()
{
	return (ChildIndex == Order);
}

template<class data>
inline bool BTNode<data>::IsLeafNode()
{
	if (this == nullptr) return false;
	return (Children[0] == nullptr);
}

template<class data>
inline void BTNode<data>::MergeNodes(BTNode<data>* Other)
{
	if (this == Other)
		return;

	for (int i = 0; i < Other->KeyIndex; i++)
		InsertKey(Other->Keys[i], Other->Links[i]);


	for (int i = 0; i < Other->ChildIndex; i++)
		InsertChild(Other->Children[i]);
}

template<class data>
inline void BTNode<data>::DeleteLinks(const int index)
{
	if (Links[index] == nullptr)
		return;

	data DatField;
	while (!Links[index]->IsEmpty())
	{
		DatField = Links[index]->Front();
		DatField.Overwrite();
		Links[index]->Delete();
	}
}

template<class data>
inline void BTNode<data>::DisplaySpecific(const data req)
{
	for (int i = 0; i < KeyIndex; i++)
		if (Keys[i]== req)
		{
			cout << Keys[i] << endl;
			if(Links[i]!= nullptr)
				Links[i]->Display();
			break;
		}
}

template<class data>
inline void BTNode<data>::DisplayKeys()
{
	for (int i = 0; i < KeyIndex; i++)
	{
		cout << Keys[i];
		Links[i]->Display();
	}
}

template<class data>
inline void BTNode<data>::Display()
{
	if (this == nullptr) return;
	if (IsLeafNode())
		cout << "Leaf : ";

	for (int i = 0; i < Order; i++)
	{
		cout << Keys[i] << "  ";
		Links[i].Display();
	}
	cout << endl;
	cout << "|";
	for (int i = 0; i < Order; i++)
		Children[i]->Display();
}

template<class data>
inline BTNode<data>::~BTNode()
{
	delete[] Keys;
	delete[] Children;
	//delete Links;


	Children = nullptr;
	Links = nullptr;
	Keys = nullptr;
	ChildIndex = 0;
	KeyIndex = 0;
}

//======================================================================//

template <class data>
class BTree {

public:
	const int Min;
	const int Order;
	BTNode<data>* root;
	const string DefinedBy;

	BTNode<data>* RecursiveInsert(BTNode<data>*&, const data, bool&);
	BTNode<data>* RecursiveDelete(BTNode<data>*&, const data, bool&);
	BTNode<data>* RecursiveSearch(BTNode<data>*&, const data);
	BTNode<data>* SplitInTwo(BTNode<data>*);
	void LDRTraversal(BTNode<data>*&);
	void AttemptBorrow(BTNode<data>*&, const int);
	void RecursiveRange(const BTNode<data>*, const data, const data);

	typedef BTNode<data>* BTPtr;
public:
	BTree(const int, const string);
	//~BTree();

	bool IsNull();
	void Insert(const data val);
	void Delete(const data val);
	void Search(const data val);
	BTNode<data>* Retrieve(const data val);

	string GetDefinedBy();
	void RangeSearch(const data, const data);
	void InOrderTraversal();
	void SaveTree();
	void LoadTree();
};

template<class data>
inline BTNode<data>* BTree<data>::RecursiveSearch(BTNode<data>*& curr, const data val)
{
	if (curr == nullptr)
		return nullptr;
	else if (curr->SearchKeys(val))
		return curr;
	else if (val < curr->MinKey() )
		return RecursiveSearch(curr->Children[0], val);
	else if (val > curr->MaxKey())
		return RecursiveSearch(curr->Children[curr->ChildIndex-1], val);
	else
	{
		for (int i = 0; i < curr->KeyIndex - 1; i++)
			if (val > curr->Keys[i] && val < curr->Keys[i + 1])
				return RecursiveSearch(curr->Children[i+1], val);
	}
}

template<class data>
inline void BTree<data>::Insert(const data val)
{
	bool NodesSplit = false;
	if (root == nullptr)
		root = new BTNode<data>(Order, val);
	else
	{
		BTNode<data>* res = RecursiveInsert(root, val, NodesSplit);
		if (!NodesSplit) root->MergeNodes(res);
		else root = res;
	}
	//cout << endl;
	//root->Display();
	//cout << endl;
}

template<class data>
inline BTNode<data>* BTree<data>::RecursiveInsert(BTNode<data>*& curr, const data val, bool& Split)
{
	BTNode<data>* res;
	if (curr->SearchKeys(val))
		curr->InsertLink(val);
	else if (curr->IsLeafNode() && !curr->KeysFull())
		return new BTNode<data>(Order, val);
	else if (curr->IsLeafNode() && curr->KeysFull())
	{
		curr->InsertKey(val);
		res = SplitInTwo(curr);
		delete curr;
		curr = nullptr;
		Split = true;
		return res;
	}
	else if (val < curr->Keys[0])
	{
		res = RecursiveInsert(curr->Children[0], val, Split);
		if (Split)
		{
			curr->InsertChild(nullptr);
			curr->ChildIndex--;
			curr->MergeNodes(res);
		}
		else curr->Children[0]->MergeNodes(res);
		Split = false;
	}
	else if (val > curr->Keys[curr->KeyIndex-1])
	{
		res = RecursiveInsert(curr->Children[curr->ChildIndex-1], val, Split);
		if (Split)
		{
			curr->InsertChild(nullptr);
			curr->ChildIndex--;
			curr->MergeNodes(res);
		}
		else curr->Children[curr->ChildIndex - 1]->MergeNodes(res);
		Split = false;
	}
	else
	{
		for (int i = 0; i < curr->KeyIndex - 1; i++)
			if (val > curr->Keys[i] && val < curr->Keys[i + 1])
			{
				res = RecursiveInsert(curr->Children[i + 1], val, Split);
				if (Split)
				{
					curr->InsertChild(nullptr);
					curr->ChildIndex--;
					curr->MergeNodes(res);
				}
				else curr->Children[i+1]->MergeNodes(res);
				Split = false;
				break;
			}
	}
	if (curr->NoKeySpace())
	{
		res = SplitInTwo(curr);
		delete curr;
		curr = nullptr;
		Split = true;
		return res;
	}
	return curr;
}
template<class data>
inline void BTree<data>::Delete(const data val)
{
	bool Merger = false;
	RecursiveDelete(root, val, Merger);
}

template <class data>
void BTree<data>::AttemptBorrow(BTNode<data>*& curr, const int index)
{
	data temp;
	if (curr->Children[index - 1]->KeyIndex - 1 > Min)
	{
		temp = curr->Children[index - 1]->MaxKey();
		curr->InsertKey(temp);
		curr->Children[index - 1]->DeleteKey(temp);
	}
	else if (curr->Children[index]->KeyIndex-1 > Min)
	{
		temp = curr->Children[index]->MaxKey();
		curr->InsertKey(temp);
		curr->Children[index]->DeleteKey(temp);
	}
	else
	{
		curr->Children[index - 1]->MergeNodes(curr->Children[index]);
		temp = curr->Children[index - 1]->MidKey();
		curr->InsertKey(temp);
		curr->Children[index - 1]->DeleteKey(temp);
		curr->Children[index] = nullptr;
		curr->InsertChild(nullptr);
	}
}

template<class data>
inline BTNode<data>* BTree<data>::RecursiveDelete(BTNode<data>*& curr, const data val, bool& NodesMerged)
{
	BTNode<data>* res;
	if (curr == nullptr)
		return nullptr;
	else if (curr->SearchKeys(val))
		curr->DeleteKey(val);
	else if (val < curr->MinKey())
		return RecursiveDelete(curr->Children[0], val, NodesMerged);
	else if (val > curr->MaxKey())
		return RecursiveDelete(curr->Children[curr->ChildIndex - 1], val, NodesMerged);
	else for (int i = 0; i < curr->KeyIndex - 1; i++)
			if (val > curr->Keys[i] && val < curr->Keys[i + 1])
				return RecursiveDelete(curr->Children[i + 1], val, NodesMerged);

	return curr;
}

template<class data>
inline BTNode<data>* BTree<data>::SplitInTwo(BTNode<data>* curr)
{
	int MidPt;
	if (curr->Order % 2 == 0) MidPt = (curr->Order + 1) / 2;
	else MidPt = (curr->Order) / 2;

	BTNode<data>*  Parent = new BTNode<data>(Order, curr->Keys[MidPt]);
	Parent->InsertChild(new BTNode<data>(Order));
	Parent->InsertChild(new BTNode<data>(Order));
	Parent->Links[0] = curr->Links[MidPt];

	for (int i = 0; i < MidPt; i++)
	{
		Parent->Children[0]->InsertKey(curr->Keys[i], curr->Links[i]);
		Parent->Children[0]->InsertChild(curr->Children[i]);
	}
	Parent->Children[0]->InsertChild(curr->Children[MidPt]);

	for (int i = MidPt + 1; i < Order; i++)
	{
		Parent->Children[1]->InsertKey(curr->Keys[i], curr->Links[i]);
		Parent->Children[1]->InsertChild(curr->Children[i]);
	}
	Parent->Children[1]->InsertChild(curr->Children[Order]);

	return Parent;
}

template<class data>
inline void BTree<data>::LDRTraversal(BTNode<data>*& curr)
{
	if (curr == nullptr)
		return;

	curr->Display();
	cout << endl;

	for (int index = 0; index < curr->ChildIndex; index++)
		LDRTraversal(curr->Children[index]);
}

template<class data>
inline BTree<data>::BTree(const int size, const string Def) : Order(size) , DefinedBy(Def),
Min(size % 2 == 0 ? (size+1)/2 : (size)/2) {root = nullptr;}

template<class data>
inline bool BTree<data>::IsNull()
{
	return root == nullptr;
}
template<class data>
inline void BTree<data>::Search(const data val)
{
	BTNode<data>* curr = RecursiveSearch(root, val);
	if (curr == nullptr)
	{
		cout << "No Record Found for : " << DefinedBy << " : " << val.Data << endl;
		return;
	}
	curr->DisplaySpecific(val);
}

template<class data>
inline BTNode<data>* BTree<data>::Retrieve(const data val)
{
	return RecursiveSearch(root,val);
}

template<class data>
inline string BTree<data>::GetDefinedBy()
{
	return DefinedBy;
}

template<class data>
inline void BTree<data>::RangeSearch(const data Min, const data Max)
{
	RecursiveRange(root, Min, Max);
}

template<typename data>
inline void BTree<data>::RecursiveRange(const BTNode<data>* curr, const data Min, const data Max)
{
	if (curr == nullptr)
		return;

	if (curr->Keys[0] > Min)
		RecursiveRange(curr->Children[0], Min, Max);

	for(int i=0 ;i<curr->KeyIndex;i++)
		if(curr->Keys[i] < Max && curr->Keys[i] > Min)
		{
			cout << curr->Keys[i] << endl;
			if (curr->Links[i] != nullptr)
				curr->Links[i]->Display();
		}

	for (int i = 1; i < curr->ChildIndex; i++)
		RecursiveRange(curr->Children[i], Min, Max);
}

template<class data>
inline void BTree<data>::InOrderTraversal()
{
	if (root == nullptr)
		return;
	root->Display();
}

template<class data>
inline void BTree<data>::LoadTree()
{
    string filename = "IndexTrees/BTree_" + DefinedBy + ".csv";
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
inline void BTree<data>::SaveTree()
{
	ofstream file("IndexTrees/BTree_" + DefinedBy + ".csv", ios::out);
	if (file.fail())
	{
		cout << "Unable to Open File" << endl;
		return;
	}

	string Record;
	Queue<BTPtr> Que;
	BTNode<data>* curr = root;
	Que.Enqueue(curr);

	while (!Que.IsEmpty())
	{
		curr = Que.Peek();
		Que.Dequeue();

		for (int i = 0; i < curr->KeyIndex; i++)
		{
			Record = CreateRecord(curr->Keys[i]);
			file.write(Record.c_str(), Record.size());
			if(curr->Links[i] != nullptr) curr->Links[i]->SaveFields(file);
		}

		for (int i = 0; i < curr->ChildIndex; i++)
			if (curr->Children[i] != nullptr)
				Que.Enqueue(curr->Children[i]);
	}

	file.close();
}