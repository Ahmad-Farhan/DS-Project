#pragma once
#pragma once
#include <iostream>

template <typename data>
class Queue {
	class QNode {
	public:
		data Data;
		QNode* Next;

		QNode(const data val, QNode* curr = nullptr)
		{
			Data = val;
			Next = curr;
		}
	};

private:
	QNode* Front;
	QNode* Rear;

public:
	Queue();
	void Display();
	bool IsEmpty();
	void  Dequeue();
	const data Peek();
	void Dequeue(data);
	void Enqueue(const data);
	~Queue();

};

template<typename data>
inline Queue<data>::Queue()
{
	Front = Rear = nullptr;
}

template<typename data>
inline void Queue<data>::Enqueue(const data val)
{
	QNode* curr = new QNode(val);
	if (IsEmpty())
	{
		Front = Rear = curr;
		return;
	}

	Rear->Next = curr;
	Rear = curr;
}

template<typename data>
inline void Queue<data>::Dequeue()
{
	if (IsEmpty())
		return;
	else if (Front == Rear)
	{
		delete Rear;
		Front = Rear = nullptr;
		return;
	}

	QNode* curr = Front;
	Front = Front->Next;
	delete curr;
}

template<typename data>
inline const data Queue<data>::Peek()
{
	if (!IsEmpty())
		return Front->Data;
	return NULL;
}

template<typename data>
inline void Queue<data>::Dequeue(data ResVar)
{
	ResVar = Front->Data;
	this->Dequeue();
}

template<typename data>
inline void Queue<data>::Display()
{
	for (QNode* curr = Front; curr != nullptr; curr = curr->Next)
		std::cout << curr->Data << "  ";
}

template<typename data>
inline bool Queue<data>::IsEmpty()
{
	return (Front == nullptr) && (Rear == nullptr);
}

template<typename data>
inline Queue<data>::~Queue()
{
	while (Front != nullptr)
		Dequeue();

	Front = Rear = nullptr;
}