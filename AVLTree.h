#pragma once
#include "Queue.h"
#include "LinkedList.h"

template <typename data>
class AVLNode {
public:
	data Data;
	LinkedList<data>* Keys;
	int Height;
	AVLNode* Left;
	AVLNode* Right;

	AVLNode(const data val, AVLNode<data>* l = nullptr, AVLNode<data>* r = nullptr, const int h = 0) : Data(val)
	{
		Keys = nullptr;
		Left = l;
		Right = r;
		Height = h;
	}
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

template <typename data>
class AVLTree{
private:
	AVLNode<data>* root;
	const string DefinedBy;

	typedef AVLNode<data>* NPtr;

	AVLNode<data>* RecursiveInsert(AVLNode<data>*&, const data);
	AVLNode<data>* RecursiveDelete(AVLNode<data>*&, const data);
	AVLNode<data>* RecursiveSearch(AVLNode<data>*&, const data);
	void LDRTraversal(AVLNode<data>*);
	void DLRTraversal(AVLNode<data>*);
	void LRDTraversal(AVLNode<data>*);
	void MakeDeletion(AVLNode<data>*&);
	void RotateLL(AVLNode<data>*&);
	void RotateRR(AVLNode<data>*&);
	void RotateRL(AVLNode<data>*&);
	void RotateLR(AVLNode<data>*&);
	AVLNode<data>* GetMin(AVLNode<data>*);
	AVLNode<data>* GetMax(AVLNode<data>*);
	const int NodeHeight(const AVLNode<data>*);
	void RecursiveRange(const AVLNode<data>*, const data, const data);

public:
	AVLTree(const string& str);
	void Insert(const data Val);
	void Delete(const data Val);

	AVLNode<data>* Retrieve(const data Val);
	void RangeSearch(const data, const data);
	void Search(const data Val);
	const string GetDefinedBy();
	const bool IsNull();

	const data GetMinimum();
	const data GetMaximum();
	const int TreeHeight();


	void LevelOrderTraversal();
	void PostOrderTraversal();
	void PreOrderTraversal();
	void InOrderTraversal();

	void SaveTree();
	void LoadTree();
	~AVLTree();
};

template<typename data>
inline AVLTree<data>::AVLTree(const string& str) : DefinedBy (str)
{
	root = nullptr;
}

template<typename data>
inline void AVLTree<data>::Insert(const data Val)
{
	root = RecursiveInsert(root, Val);
}

template<typename data>
void AVLTree<data>::Delete(const data Val)
{
	RecursiveDelete(root, Val);
	this->SaveTree();
}

template<typename data>
void AVLTree<data>::Search(const data Val)
{
	cout << "Searching for " << DefinedBy << " : " << Val.Data << endl;
	AVLNode<data>* curr = RecursiveSearch(root, Val);
	if (curr == nullptr)
	{
		cout << "No Record Found for : " << DefinedBy << " : " << Val.Data << endl;
		return;
	}
	else if (curr->Data == data())
	{
		cout << "No Record Found for : " << DefinedBy << " : " << Val.Data << endl;
		return;
	}
	cout << curr->Data << endl;
	curr->DisplayKeys();
}

template<typename data>
inline const string AVLTree<data>::GetDefinedBy()
{
	return DefinedBy;
}

template<typename data>
inline const bool AVLTree<data>::IsNull()
{
	return root == nullptr;
}

template<typename data>
inline AVLNode<data>* AVLTree<data>::Retrieve(const data Val)
{
	AVLNode<data>* curr = RecursiveSearch(root, Val);
	if (curr == nullptr)
		return nullptr;
	else return curr;
}

template<typename data>
inline void AVLTree<data>::RangeSearch(const data Min, const data Max)
{
	RecursiveRange(root, Min, Max);
}

template<typename data>
inline void AVLTree<data>::RecursiveRange(const AVLNode<data>* curr, const data Min, const data Max)
{
	if (curr == nullptr)
		return;

	if (curr->Data > Min)
		RecursiveRange(curr->Left, Min, Max);

	if (curr->Data < Max && curr->Data > Min)
	{
		cout << curr->Data << endl;
		if (curr->Keys != nullptr)
			curr->Keys->Display();
	}
	RecursiveRange(curr->Right, Min, Max);
}

template <typename data>
const int getHeight(const AVLNode<data>* curr)
{
	if (curr == nullptr)
		return -1;
	return curr->Height;
}

template <typename data>
const int Max(const data N1, const data N2)
{
	if (N1 > N2) return N1;
	return N2;
}
template<typename data>
void AVLTree<data>::MakeDeletion(AVLNode<data>*& curr)
{
	AVLNode<data>* deltemp = curr;
	if (curr->Right == nullptr)
	{
		curr = curr->Left;
		delete deltemp;
	}
	else if (curr->Left == nullptr)
	{
		curr = curr->Right;
		delete deltemp;
	}
	else
	{
		deltemp->Data.Overwrite();
		deltemp->DeleteKeys();
		deltemp = GetMin(curr->Right);
		curr->Data = deltemp->Data;
		RecursiveDelete(curr->Right, deltemp->Data);
	}
}

template<typename data>
AVLNode<data>* AVLTree<data>::RecursiveDelete(AVLNode<data>*& curr, const data val)
{
	if (curr == nullptr)
		return nullptr;
	else if (val == curr->Data)
		MakeDeletion(curr);
	else if (val < curr->Data)
	{
		curr->Left = RecursiveDelete(curr->Left, val);
		if (getHeight(curr->Left) - getHeight(curr->Right) == 2)
			if (val < curr->Left->Data)
				RotateRR(curr);
			else RotateRL(curr);
	}
	else if (val > curr->Data)
	{
		curr->Right = RecursiveDelete(curr->Right, val);
		if (getHeight(curr->Right) - getHeight(curr->Left) == 2)
			if (val > curr->Right->Data)
				RotateLL(curr);
			else	RotateLR(curr);
	}

	if (curr != nullptr) curr->Height = Max(getHeight(curr->Left), getHeight(curr->Right)) + 1;
	return curr;
}

template<typename data>
inline AVLNode<data>* AVLTree<data>::RecursiveSearch(AVLNode<data>*& curr, const data val)
{
	if (curr == nullptr)
		return nullptr;
	else if (val < curr->Data)
		return RecursiveSearch(curr->Left, val);
	else if (val > curr->Data)
		return RecursiveSearch(curr->Right, val);
	else return curr;
}

template<typename data>
inline void AVLTree<data>::LDRTraversal(AVLNode<data>* curr)
{
	if (curr == nullptr)
		return;

	LDRTraversal(curr->Left);
	std::cout << curr->Data << " ";
	curr->DisplayKeys();
	LDRTraversal(curr->Right);
}

template<typename data>
inline void AVLTree<data>::DLRTraversal(AVLNode<data>* curr)
{
	if (curr == nullptr)
		return;

	std::cout << curr->Data << "\n";
	curr->DisplayKeys();
	DLRTraversal(curr->Left);
	DLRTraversal(curr->Right);
}

template<typename data>
inline void AVLTree<data>::LRDTraversal(AVLNode<data>* curr)
{
	if (curr == nullptr)
		return;

	LRDTraversal(curr->Left);
	LRDTraversal(curr->Right);
	std::cout << curr->Data << "\n";
	curr->DisplayKeys();
}

template<typename data>
AVLNode<data>* AVLTree<data>::GetMin(AVLNode<data>* curr)
{
	if (curr->Left == nullptr)
		return curr;
	else return GetMin(curr->Left);
}

template<typename data>
AVLNode<data>* AVLTree<data>::GetMax(AVLNode<data>* curr)
{
	if (curr->Right == nullptr)
		return curr;
	else return GetMax(curr->Right);
}

//Insertion
template<typename data>
inline AVLNode<data>* AVLTree<data>::RecursiveInsert(AVLNode<data>*& curr, data val)
{
	if (curr == nullptr)
		return new AVLNode<data>(val);
	else if (val == curr->Data)
		curr->InsertKey(val);
	else if (val < curr->Data)
	{
		curr->Left = RecursiveInsert(curr->Left, val);
		if (getHeight(curr->Left) - getHeight(curr->Right) == 2)
			if (val < curr->Left->Data)
				RotateRR(curr);
			else RotateRL(curr);
	}
	else if (val > curr->Data)
	{
		curr->Right = RecursiveInsert(curr->Right, val);
		if (getHeight(curr->Right) - getHeight(curr->Left) == 2)
			if (val > curr->Right->Data)
				RotateLL(curr);
			else	RotateLR(curr);
	}

	curr->Height = Max(getHeight(curr->Right), getHeight(curr->Left)) + 1;
	return curr;
}

template<typename data>		//RR Heavy
void AVLTree<data>::RotateLL(AVLNode<data>*& curr)
{
	AVLNode<data>* temp = curr->Right;
	curr->Right = temp->Left;
	temp->Left = curr;

	curr->Height = Max(getHeight(curr->Left), getHeight(curr->Right)) + 1;
	temp->Height = Max(getHeight(temp->Left), getHeight(temp->Right)) + 1;
	curr = temp;
}

template<typename data>		//LL Heavy
void AVLTree<data>::RotateRR(AVLNode<data>*& curr)
{
	AVLNode<data>* temp = curr->Left;
	curr->Left = temp->Right;
	temp->Right = curr;

	curr->Height = Max(getHeight(curr->Left), getHeight(curr->Right)) + 1;
	temp->Height = Max(getHeight(temp->Left), getHeight(temp->Right)) + 1;
	curr = temp;
}

template<typename data>		//RL Heavy
void AVLTree<data>::RotateLR(AVLNode<data>*& curr)
{
	RotateRR(curr->Right);
	RotateLL(curr);
}

template<typename data>		//LRHeavy
void AVLTree<data>::RotateRL(AVLNode<data>*& curr)
{
	RotateLL(curr->Left);
	RotateRR(curr);
}

template<typename data>
const int AVLTree<data>::TreeHeight()
{
	if (root == nullptr) return 0;
	return NodeHeight(root);
}

template<typename data>
const data AVLTree<data>::GetMinimum()
{
	if (root == nullptr)	return NULL;
	return GetMin(root)->Data;
}

template<typename data>
const data AVLTree<data>::GetMaximum()
{
	if (root == nullptr) return NULL;
	return GetMax(root)->Data;
}

template<typename data>
const int AVLTree<data>::NodeHeight(const AVLNode<data>* curr)
{
	unsigned short int LH, RH;
	if (curr == nullptr)
		return -1;
	else if (curr->Left == nullptr && curr->Right == nullptr)
		return 0;

	LH = NodeHeight(curr->Left) + 1;
	RH = NodeHeight(curr->Right) + 1;
	return Max(LH, RH);
}

template<typename data>
inline void AVLTree<data>::PostOrderTraversal()
{
	LRDTraversal(root);
	std::cout << std::endl;
}

template<typename data>
inline void AVLTree<data>::PreOrderTraversal()
{
	DLRTraversal(root);
	std::cout << std::endl;
}

template<typename data>
inline void AVLTree<data>::InOrderTraversal()
{
	LDRTraversal(root);
	std::cout << std::endl;
}

template<typename data>
inline void AVLTree<data>::LevelOrderTraversal()
{
	Queue<NPtr> Que;
	AVLNode<data>* curr = root;
	Que.Enqueue(curr);

	while (!Que.IsEmpty())
	{
		curr = Que.Peek();
		Que.Dequeue();

		std::cout << curr->Data << "  " << curr->Height << std::endl;
		curr->DisplayKeys();

		if (curr->Left != nullptr)
			Que.Enqueue(curr->Left);
		if (curr->Right != nullptr)
			Que.Enqueue(curr->Right);
	}
}

template<typename data>
inline void AVLTree<data>::SaveTree()
{
	ofstream file("IndexTrees/AVLTree_" + DefinedBy + ".csv", ios::out);
	if (file.fail())
	{
		cout << "Unable to Open File" << endl;
		return;
	}

	string Record;
	Queue<NPtr> Que;
	AVLNode<data>* curr = root;
	Que.Enqueue(curr);

	while (!Que.IsEmpty())
	{
		curr = Que.Peek();
		Que.Dequeue();

		Record = CreateRecord(curr->Data);
		file.write(Record.c_str(), Record.size());
		curr->SaveKeys(file);


		if (curr->Left != nullptr)
			Que.Enqueue(curr->Left);
		if (curr->Right != nullptr)
			Que.Enqueue(curr->Right);
	}

	file.close();
}

template<typename data>
inline void AVLTree<data>::LoadTree()
{
	string filename = "IndexTrees/AVLTree_" + DefinedBy + ".csv";
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

template<typename data>
inline AVLTree<data>::~AVLTree()
{
	if (root == nullptr)
		return;
	Queue<NPtr> Que;
	AVLNode<data>* curr = root;
	Que.Enqueue(curr);

	while (!Que.IsEmpty())
	{
		curr = Que.Peek();
		Que.Dequeue();


		if (curr->Left != nullptr)
			Que.Enqueue(curr->Left);
		if (curr->Right != nullptr)
			Que.Enqueue(curr->Right);

		delete curr;
	}
}