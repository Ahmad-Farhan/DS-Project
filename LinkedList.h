#pragma once
#include "General.h"

template <class data>
class LinkedList;

template <typename data>
class LLNode {
	data Data;
	LLNode* Next;

	LLNode(const data dataVal, LLNode* next = nullptr): Data(dataVal)
	{	Next = next;	}

	friend class LinkedList<data>;
};

template <typename data>
class LinkedList {
	LLNode<data>* Head;
	LLNode<data>* Tail;

public:
	LinkedList();
	bool IsEmpty();
	const data Front();

	void Insert(const data);
	void InsertH(const data);
	void InsertAt(const data, const int);
	void Delete();
	void DeleteAt(const int);
	void DeleteValue(const data);

	const int Length();
	bool Search(const data);
	const data ValueAt(const int);
	void Display();
	
	void SaveFields(ofstream&);
	void DisplaySpFields(const string&, const int);
	data SearchFields(const string&, const int);

	~LinkedList();
};

template <typename data>
LinkedList<data>::LinkedList()
{
	Head = nullptr;
	Tail = nullptr;
}

template <typename data>
void LinkedList<data>::InsertAt(const data dataVal, const int index)
{
	LLNode<data>* Current = Head;
	if (Head == nullptr || index == 0)
		Insert(dataVal);
	else
	{
		for (int i = 1; Current->Next != nullptr && i < index; i++)
			Current = Current->Next;

		LLNode<data>* Post = Current->Next;
		Current->Next = new LLNode<data>(dataVal);
		Current->Next->Next = Post;
	}
}

template <typename data>
void LinkedList<data>::InsertH(const data dataVal)
{
	LLNode<data>* Current = new LLNode<data>(dataVal);
	Current->Next = Head;
	Head = Current;
}

template <typename data>
void LinkedList<data>::Insert(const data dataVal)
{
	if (Head == nullptr)
	{
		Head = new LLNode<data>(dataVal);
		Tail = Head;
		return;
	}
	Tail->Next = new LLNode<data>(dataVal);
	Tail = Tail->Next;
}

template<typename data>
inline void LinkedList<data>::Delete()
{
	if (Head == nullptr)
		return;

	LLNode<data>* curr = Head;
	Head = Head->Next;
	delete curr;
}

template <typename data>
void LinkedList<data>::DeleteAt(const int index)
{
	LLNode<data>* Current = Head;
	for (int i = 1; i < index; i++)
		Current = Current->Next;

	if (Current == Head)
	{
		Head = Head->Next;
		delete Current;
		return;
	}

	LLNode<data>* Post = Current->Next;
	Current->Next = Post->Next;
	delete Post;
}

template <typename data>
void LinkedList<data>::DeleteValue(const data Value)
{
	LLNode<data>* Current = Head;
	for (int i = 0; Current->Next != nullptr; i++)
		if (Current->Data.MatchAll(Value))
		{
			Current = Current->Next;
			DeleteAt(i);
			i--;
			return;
		}
		else Current = Current->Next;
}

template <typename data>
bool LinkedList<data>::Search(const data dataVal)
{
	LLNode<data>* Current = Head;
	while (Current != nullptr)
	{
		if (Current->Data == dataVal)
			return true;
		Current = Current->Next;
	}
	return false;
}

template<typename data>
inline bool LinkedList<data>::IsEmpty()
{
	return Head == nullptr;
}

template<typename data>
inline const data LinkedList<data>::Front()
{
	return Head->Data;
}

template <typename data>
const data LinkedList<data>::ValueAt(const int index)
{
	LLNode<data>* Current = Head;
	for (int i = 0; i < index && Current != nullptr; i++)
		Current = Current->Next;

	if (Current == nullptr)
		return (-1);

	return Current->Data;
}

template<typename data>
inline void LinkedList<data>::DisplaySpFields(const string& Searchfor, const int FieldNumber)
{
	string Tuple, Required;
	LLNode<data>* Current = Head;
	while (Current != nullptr)
	{
		Tuple = Current->Data.ReadTuple();
		if (CompareStr(Searchfor, CurrFieldEntry(Tuple, FieldNumber)))
			cout << Current->Data << endl;
		Current = Current->Next;
	}
}

template<typename data>
inline data LinkedList<data>::SearchFields(const string& Searchfor, const int FieldNumber)
{
	string Tuple, Required;
	LLNode<data>* Current = Head;
	while (Current != nullptr)
	{
		Tuple = Current->Data.ReadTuple();
		if (CompareStr(Searchfor, CurrFieldEntry(Tuple, FieldNumber)))
			return Current->Data;
		Current = Current->Next;
	}
	return data();
}

template<typename data>
inline void LinkedList<data>::SaveFields(ofstream& file)
{
	if (Head == nullptr)
		return;

	string Record;
	LLNode<data>* Current = Head;
	for (int i = 0; Current != nullptr; i++)
	{
		Record = CreateRecord(Current->Data);
		file.write(Record.c_str(), Record.size());
		Current = Current->Next;
	}
}

template <typename data>
const int LinkedList<data>::Length()
{
	int length;
	for (LLNode<data>* curr = Head, length = 0; curr != nullptr; curr = curr->Next, length++);
	return length;
}

template <typename data>
void LinkedList<data>::Display()
{
	if (Head == nullptr)
		return;

	LLNode<data>* Current = Head;
	for (int i = 0; Current != nullptr; i++)
	{
		std::cout << Current->Data << std::endl;
		Current = Current->Next;
	}
}

template <typename data>
LinkedList<data>::~LinkedList()
{
	if (Head == nullptr) return;
	LLNode<data>* Current = Head;

	while (Current->Next != nullptr)
	{
		while (Current->Next->Next != nullptr)
			Current = Current->Next;

		delete Current->Next;
		Current->Next = nullptr;
		Current = Head;
	}
	delete Head;
	Head = nullptr;
}