#pragma once
#pragma once
#include <iostream>

template <typename data>
class Stack {
	class SNode {
	public:
		data Data;
		SNode* Next;

		SNode(const data val = 0, SNode* nex = nullptr)
		{
			Data = val;
			Next = nex;
		}
	};

private:
	SNode* Top;
public:
	Stack();
	void Pop();
	void Display();
	bool IsEmpty();
	void Pop(data);
	const data Peek();
	void Push(const data);
	~Stack();
};

template<typename data>
inline Stack<data>::Stack()
{
	Top = nullptr;
}

template<typename data>
inline void Stack<data>::Push(const data val)
{
	SNode* temp = new SNode(val, Top);
	Top = temp;
}

template<typename data>
inline void Stack<data>::Pop()
{
	if (IsEmpty())
		return;
	SNode* temp = Top;
	Top = Top->Next;
	delete temp;
}

template<typename data>
inline bool Stack<data>::IsEmpty()
{
	return Top == nullptr;
}

template<typename data>
inline const data Stack<data>::Peek()
{
	if (!IsEmpty())
		return Top->Data;
	return (-1);
}

template<typename data>
inline void Stack<data>::Display()
{
	for (SNode* curr = Top; curr != nullptr; curr = curr->Next)
		std::cout << curr->Data << "  ";
}

template<typename data>
inline Stack<data>::~Stack()
{
	SNode* temp;
	while (Top != nullptr)
	{
		temp = Top;
		Top = Top->Next;
		delete temp;
	}
}

template<typename data>
inline void Stack<data>::Pop(data ResVar)
{
	ResVar = Top->Data;
	this->Pop();
}
