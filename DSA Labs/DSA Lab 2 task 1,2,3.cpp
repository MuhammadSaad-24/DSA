#include <iostream>
using namespace std;

template <class Type>
class LinkList
{
private:
	struct Node;
	Node* head;
public:
	
	LinkList()
	{
		head = nullptr;
	}
	
	void InsertAtStart(const Type value)
	{
		head = new Node(value,head);
	}

	void Print()
	{
		cout << "\nLink List : ";

		for (Node* temp = head; temp != nullptr; temp = temp->next)
		{
			if (temp->next != nullptr)
				cout << temp->Data << "->";
			else
				cout << temp->Data;
		}

		cout << endl;
	}

	bool Find(const Type value)
	{
		for (Node* temp = head; temp != nullptr; temp = temp->next)
		{
			if (temp->Data == value)
				return true;
		}

		return false;

	}
	
	bool IsEmpty()
	{
		return head == nullptr;
	}

	void InsertAtEnd(const Type);
	bool InsertBefore(const Type v1, const Type v2);
	void DeleteFromStart();
	void DeleteDuplicates();
	void DeleteInRange(const Type start, const Type end);
	void MergeSort(LinkList& other);
	~LinkList();

};

template <typename Type>
bool LinkList<Type>::InsertBefore(const Type v1, const Type v2)
{
	Node* temp = head;

	if (head->Data == v2)
	{
		head = new Node(v1, head);
		return true;
	}
	while (temp != nullptr)
	{
		if (temp->next != nullptr)
		{
			if (temp->next->Data == v2)
			{
				temp->next = new Node(v1, temp->next);
				return true;
			}
		}

		temp = temp->next;
	}

	if (IsEmpty())
	{
		head = new Node(v1);
		return true;
	}
	else
	{
		cout << v2 << " Not Found";
		return false;
	}
	
}

template <typename Type>
void LinkList<Type>::InsertAtEnd(const Type value)
{
	Node* temp = head;
	Node* previous = nullptr;

	while (temp != nullptr)
	{
		previous = temp;
		temp = temp->next;
	}

	if (!IsEmpty())
	{
		previous->next = new Node(value);

	}
	else
	{
		head = new Node(value);
	}
}

template <typename Type>
void LinkList<Type>::DeleteFromStart()
{
	if (head == nullptr)
		return;
	
	Node* temp = head->next;
	delete head;
	head = temp;
}

template <typename Type>
void LinkList<Type>::DeleteDuplicates()
{
	for (Node* key = head; key != nullptr; key = key->next)
	{
		for (Node* temp = key->next,* previous = key; temp != nullptr ;)
		{
			if (key->Data == temp->Data)
			{
				Node* toDelete = temp;
			
				temp = temp->next;
				previous->next = temp;

				delete toDelete;
				
			}
			else
			{
				previous = temp;
				temp = temp->next;
			}
		}
	}
}

template <typename Type>
void LinkList<Type>::DeleteInRange(const Type start, const Type end)
{
	for (Node* temp = head, *previous = nullptr; temp != nullptr;)
	{
		if (temp->Data >= start && temp->Data < end)
		{
			Node* toDelete = temp;


			if(previous)
				previous->next = temp->next;

			if (temp == head)
			{
				head = temp->next;
			}

			temp = temp->next;

			delete toDelete;

		}
		else
		{
			previous = temp;
			temp = temp->next;
		}
	}
}

template <typename Type>
void LinkList<Type>::MergeSort(LinkList& other)
{
	for (Node* l1 = head,* l2 = other.head,*l1previous = nullptr;l2 != nullptr && l1 != nullptr ;)
	{
		if (l1->Data < l2->Data)
		{
			l1previous = l1;
			l1 = l1->next;
		}
		else
		{
			Node* temp = new Node(l2->Data, l1);
			l1previous->next = temp;
			l1previous = temp;
			l2 = l2->next;
		}
	}
}

template <typename Type>
LinkList<Type>::~LinkList()
{
	for (Node* temp = head; temp != nullptr ;)
	{
		head = temp->next;
		delete temp;
		temp = head;
	}

	head = nullptr;

}


//---------- Struct Node --------------//


template <class Type>
struct LinkList<Type>::Node
{
public:
	Type Data;
	Node* next;
	Node(Type value, Node* n = nullptr)
	{
		Data = value;
		next = n;
	}
};

int main()
{
	LinkList<int> l1;
	l1.InsertAtStart(2);
	l1.InsertAtStart(6);
	l1.InsertAtStart(7);
	l1.InsertAtEnd(9);
	l1.InsertAtStart(7);
	l1.InsertAtStart(8);
	l1.InsertAtStart(9);
	l1.Print();

	cout << "\nInsert 5 Before 9\n";
	l1.InsertBefore(5, 9);
	l1.Print();
	
	cout << "2 Found? " << l1.Find(2) << endl;
	cout << "5 Found? " << l1.Find(5) << endl;
	cout << "10 Found? " << l1.Find(10) << endl;
	cout << "9 Found? " << l1.Find(9) << endl;
	
	cout << "\nDelete Duplicates:\n";
	l1.DeleteDuplicates();
	l1.Print();

	//------------ Task 2 -------------//

	cout << "\n\n\nDelete between 3 and 7 Range :\n";
	l1.DeleteInRange(3, 7);
	l1.Print();

	//------------ Task 3 -------------//

	cout << "\n\nMerge Sort : \n";

	
	LinkList<int> l2;
	LinkList<int> l3;
	
	l2.InsertAtEnd(1);
	l2.InsertAtEnd(3);
	l2.InsertAtEnd(5);
	l2.InsertAtEnd(9);
	
	l3.InsertAtEnd(2);
	l3.InsertAtEnd(4);
	l3.InsertAtEnd(6);
	l3.InsertAtEnd(8);


	l2.MergeSort(l3);
	l2.Print();
}