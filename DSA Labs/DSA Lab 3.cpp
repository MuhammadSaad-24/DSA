#include <iostream>
using namespace std;

template <typename Type> class DLL
{
private:
    class Node;
    Node *Head;
    Node *Tail;
    int size;

public:
    DLL();
    int CountNodes() const;
    
	int SearchByID(const Type &) const;//Tells Position in Link List if present
    Node *Find(const Type &) const;//Finds Data if present
    
	Type& ReturnMiddle() const;
    
	void DisplayNextPrevious(const Type &) const;
    
	void AddInSortedOrder(const Type &);
    void Sort();
    void ReverseList();

	void Union(DLL<Type>&);

	void AddInStart(const Type &data);
    void AddNode(const int &key, const Type &data);
    void AddAfter(const int &, const Type &data);
    void AddInEnd(const Type &data);

    void DeleteFromEnd();
    void DeleteFromStart();
    void DeleteNode(const Type &);
    void DeleteBefore(const int &);
    void DeleteAfter(const int &);
    void DeleteDuplicates();
	bool operator!() const;
    
	void TraverseForward() const;
    void Traversebackward() const;
    template <typename T> 
    friend ostream &operator<<(ostream &, const DLL<T> &);

    ~DLL();
};

template <typename Type> DLL<Type>::DLL()
{
    Head = nullptr;
    Tail = nullptr;
    size = 0;
}

template <typename Type> int DLL<Type>::CountNodes() const { return size; }

template <typename Type> int DLL<Type>::SearchByID(const Type &key) const
{
    Node *temp = Head;
    int count = 0;
    while (temp != nullptr)
    {
        if (temp->Data == key)
            return count;
        temp = temp->Next;
        count++;
    }
    return -1;
}

template <typename Type>
Type& DLL<Type>::ReturnMiddle() const
{
    Node *temp = Head;
    Node* Fast = Head;

    while(Fast != nullptr)
    {
        temp = temp->Next;
        if(Fast != Tail)
            Fast = Fast->Next->Next;
        else
            Fast = Fast->Next;
    }

    if(size % 2 != 0)
        return temp->Data;
    else
        return temp->Previous->Data;
}

template <typename Type>
typename DLL<Type>::Node *DLL<Type>::Find(const Type &key) const
{
    Node *temp = Head;
    while (temp != nullptr)
    {
        if (temp->Data == key)
            return temp;

        temp = temp->Next;
    }
    return nullptr;
}

template <typename Type>
void DLL<Type>::DisplayNextPrevious(const Type &key) const
{
    Node *Temp = Find(key);

    if (!Temp)
        cout << "Error::" << key << " Not Found" << endl;
    else
        cout << "Current -> " << Temp->Data << endl;

    if (Temp != Head)
        cout << "Current->Previous-> " << Temp->Previous->Data << endl;
    else
        cout << "No Previous! : " << key << " Is Head->Data" << endl;

    if (Temp != Tail)
        cout << "Current->Next-> " << Temp->Next->Data << endl;
    else
        cout << "No Next! : " << key << " Is Tail->Data" << endl;
}

template <typename Type> void DLL<Type>::Sort()
{
   Node *Temp = Head;
   while (Temp != Tail)
   {
      Node *Temp2 = Temp;
      Node *Minptr = Temp2;
      while (Temp2)
      {
         if (Temp2->Data < Minptr->Data)
            Minptr = Temp2;
   
         Temp2 = Temp2->Next;
      }

      if(Temp != Minptr)
      {
         //Change the next and previous pointes of nodes next and previous to temp and Minptr
      
         if(Minptr != Tail)
            Minptr->Next->Previous = Temp;

         if(Minptr != Head && Minptr->Previous != Temp)
            Minptr->Previous->Next = Temp;
         //else if(Minptr != Head)

         if(Temp != Head)
            Temp->Previous->Next = Minptr;
   
         if(Temp->Next != Minptr && Minptr->Previous != Temp)
            Temp->Next->Previous = Minptr;////
         
         Node* Temp1 = Minptr->Next;//to hold the addresses of next and previous value of Minptr
         Temp2 = Minptr->Previous;//otherwise they would be lost
         
         if(Minptr->Previous != Temp)
            Minptr->Next = Temp->Next;//safely swapping
         else
            Minptr->Next = Temp;
         
         Minptr->Previous = Temp->Previous;
         
         if(Temp->Next != Minptr)
            Temp->Previous = Temp2;
         else
            Temp->Previous = Minptr;

         Temp->Next = Temp1;
      

         if (Temp == Head)
            Head = Minptr;

         if (Minptr == Tail)
            Tail = Temp;

         Traversebackward();
         cout << *this;

      }
      
      Temp = Minptr->Next;
   }
}

template <typename Type> void DLL<Type>::AddInSortedOrder(const Type & data) 
{
   Node* Temp = Head;

   while(Temp->Data < data && Temp != nullptr)
   {
      Temp = Temp->Next;
   }

   if(Temp == Head)
      AddInStart(data);
   
   else if(Temp == nullptr)
      AddInEnd(data);
   
   else
   {
      Node* NewNode = new Node(data,Temp->Previous,Temp);
      Temp->Previous = NewNode;
      NewNode->Previous->Next = NewNode;
   }

}

template <typename Type> 
void DLL<Type>::ReverseList()
{
	Node* temp = Head;
	Node* swap = Tail;
	//Node* next,current,previous;
	Tail = Head;
	Head = swap;

	//temp = Head;

	while(temp != nullptr)
	{
		swap = temp->Next;
		temp->Next = temp->Previous;
		temp->Previous = swap;

		temp = temp->Previous;
	}
}

template <typename Type> 
void DLL<Type>::Union(DLL<Type>& other)
{
    DeleteDuplicates();

	Node* l1 = Head;

	while(l1 != nullptr && other.Head != nullptr)
	{
    	Node* l2 = other.Head;

		if(l1->Data == l2->Data)
		{
			l1 = l1->Next;
            
            other.Head = l2->Next;
            
            delete l2;
            other.size--;
            if(other.Head != nullptr)
                other.Head->Previous = nullptr;

		}
		else if(l1->Data > l2->Data)
		{
            other.Head = l2->Next;
            other.size--;

            l2->Previous = l1->Previous;
            l2->Next = l1; 

            if(l1 != Head)
                l1->Previous->Next = l2;
            
            l1->Previous = l2;

            if(other.Head != nullptr)
                other.Head->Previous = nullptr;

            if(l1 == Head)
                Head = l2;
            size++;

		}
        else
            l1 = l1->Next;
	}

    if(l1 == nullptr && other.Head != nullptr)
    {
        Tail->Next = other.Head;
        Tail->Next->Previous = Tail;
        Tail = other.Tail;
        size += other.size;
    }


    other.Head = other.Tail = nullptr;
}

template <typename Type> 
void DLL<Type>::AddInStart(const Type &data)
{
    Node *NewNode = new Node(data);
    if (Head == nullptr)
        Head = Tail = NewNode;
    else
    {
        Head->Previous = NewNode;
        NewNode->Next = Head;
        Head = NewNode;
    }
    size++;
}

template <typename Type>
void DLL<Type>::AddNode(const int &Key, const Type &data)
{
    Node *RequiredPlace = Find(Key);
    if (!RequiredPlace)
    {
        cout << "Error:: " << Key << " Not Found!!" << endl;
        return;
    }

    Node *NewNode = new Node(data);
    if (Head == RequiredPlace)
        AddInStart(data);
    else if (RequiredPlace)
    {
        NewNode->Previous = RequiredPlace->Previous;
        NewNode->Next = RequiredPlace;
        RequiredPlace->Previous->Next = NewNode;
        RequiredPlace->Previous = NewNode;
        size++;
    }
}

template <typename Type>
void DLL<Type>::AddAfter(const int &Key, const Type &data)
{
    Node *RequiredPlace = Find(Key);
    if (!RequiredPlace)
    {
        cout << "Error:: " << Key << " Not Found!!" << endl;
        return;
    }

    Node *NewNode = new Node(data);
    if (Tail == RequiredPlace)
        AddInEnd(data);
    else if (RequiredPlace)
    {
        NewNode->Next = RequiredPlace->Next;
        NewNode->Previous = RequiredPlace;
        RequiredPlace->Next->Previous = NewNode;
        RequiredPlace->Next = NewNode;
        size++;
    }
}

template <typename Type> void DLL<Type>::AddInEnd(const Type &data)
{
    if (Head == nullptr)
        Head = Tail = new Node(data);
    else
    {
        Tail->Next = new Node(data, Tail);
        Tail = Tail->Next;
    }
    size++;
}

template <typename Type> void DLL<Type>::DeleteFromEnd()
{
    if (Head != Tail) // handles when list is empty or has more than one entry
    {
        Tail = Tail->Previous;
        delete Tail->Next;
        Tail->Next = nullptr;
    }
    else if (Head != nullptr) // when Head == Tail but not empty
    {
        delete Head;
        Head = Tail = nullptr;
    }
    size--;
}

template <typename Type> void DLL<Type>::DeleteFromStart()
{
    if (Head != Tail) // handles when list is empty or has more than one entry
    {
        Head = Head->Next;
        delete Head->Previous;
        Head->Previous = nullptr;
    }
    else if (Head != nullptr) // when Head == Tail but not empty
    {
        delete Head;
        Head = Tail = nullptr;
    }
    size--;
}

template <typename Type> void DLL<Type>::DeleteBefore(const int &Key)
{
    Node *RequiredPlace = Find(Key);
    if (!RequiredPlace)
        cout << "Error:: " << Key << " Not Found!!" << endl;
    else if (RequiredPlace == Head)
    {
        cout << "Error:: Cannot Delete Data Before Head!!!" << endl;
        return;
    }
    else if (RequiredPlace == Head->Next)
        DeleteFromStart();
    else
    {
        Node *temp = RequiredPlace->Previous;
        temp->Previous->Next = RequiredPlace;
        RequiredPlace->Previous = temp->Previous;
        delete temp;
        temp = nullptr;
        size--;
    }
}

template <typename Type> void DLL<Type>::DeleteAfter(const int &Key)
{
    Node *RequiredPlace = Find(Key);
    if (!RequiredPlace)
        cout << "Error:: " << Key << " Not Found!!" << endl;
    else if (Tail == RequiredPlace)
        cout << "Error::Cannot Delete Data after Tail!!" << endl;
    else if (Tail->Previous == RequiredPlace)
        DeleteFromEnd();
    else
    {
        Node *temp = RequiredPlace->Next;
        temp->Next->Previous = RequiredPlace;
        RequiredPlace->Next = temp->Next;
        delete temp;
        temp = nullptr;
        size--;
    }
}

template <typename Type> void DLL<Type>::DeleteNode(const Type &Key)
{
    Node *RequiredPlace = Find(Key);
    if (!RequiredPlace)
        cout << "Error:: " << Key << " Not Found!!" << endl;
    else if (Tail == RequiredPlace)
        DeleteFromEnd();
    else if (Head == RequiredPlace)
        DeleteFromStart();
    else
    {
        RequiredPlace->Previous->Next = RequiredPlace->Next;
        RequiredPlace->Next->Previous = RequiredPlace->Previous;
        delete RequiredPlace;
        RequiredPlace = nullptr;
        size--;
    }
}

template <typename Type> 
void DLL<Type>::DeleteDuplicates()
{
    Node* key = Head;

    while(key != nullptr)
    {
        Node* IsEqual = key->Next;

        while(IsEqual)
        {
            if(key->Data == IsEqual->Data)
            {
                Node* Temp = IsEqual->Next;

                if(IsEqual != Tail)
                    IsEqual->Next->Previous = IsEqual->Previous;
                else
                    Tail = IsEqual->Previous;

                IsEqual->Previous->Next = IsEqual->Next;
                
                delete IsEqual;
                IsEqual = Temp;
            }
            else
                IsEqual = IsEqual->Next;
        }

        key = key->Next;
    }
}

template <typename Type> 
void DLL<Type>::TraverseForward() const
{
   Node *Temp = Head;
   cout << "Traverse Forward : ";
   while (Temp != nullptr)
   {
      if (Temp != Tail)
         cout << Temp->Data << "->";
      else
         cout << Temp->Data;
      Temp = Temp->Next;

   }

    cout << endl;
}

template <typename Type> void DLL<Type>::Traversebackward() const
{
   Node *Temp = Tail;
   cout << "Traverse Backward : ";
   
   while (Temp != nullptr)
   {
      if (Temp != Head)
         cout << Temp->Data << "->";
      else
         cout << Temp->Data;
      Temp = Temp->Previous;

   }
   
   cout << endl;
}

template <typename Type> bool DLL<Type>::operator!() const
{
    return Head != nullptr;
}

template <typename Type>
ostream &operator<<(ostream &out, const DLL<Type> &DATA)
{
    typename DLL<Type>::Node *Temp = DATA.Head;
    
    out << "Double Link List : ";
    
    while (Temp != nullptr)
    {
        if (Temp != DATA.Tail)
            out << Temp->Data << "->";
        else
            out << Temp->Data;

        Temp = Temp->Next;
    }
    
    out << endl;
    return out;
}

template <typename Type> DLL<Type>::~DLL()
{
    Node *temp = Head;
    while (Head != nullptr)
    {
        temp = Head;
        Head = Head->Next;
        delete temp;
    }
    Head = Tail = nullptr;
    size = 0;
}

template <typename Type> class DLL<Type>::Node
{
public:
   Type Data;
   Node *Next;
   Node *Previous;
   Node(const Type &, Node * = 0, Node * = 0);
   ~Node();
};

template <typename Type> DLL<Type>::Node::Node(const Type &d, Node *p, Node *n)
{
    Data = d;
    Next = n;
    Previous = p;
}

template <typename Type> DLL<Type>::Node::~Node()
{
    Next = nullptr;
    Previous = nullptr;
}

int main()
{
    DLL<int> l1;
    l1.AddInStart(5);
    l1.AddInStart(2);
    l1.AddInStart(6);
    l1.AddInStart(8);
    l1.AddInStart(9);
    l1.AddInStart(10);
    l1.AddInEnd(5);
    l1.TraverseForward();

    cout << "Delete Duplicates : \n";
    l1.DeleteDuplicates();
    l1.TraverseForward();

    cout << "Sort : \n";
    l1.Sort();

    l1.TraverseForward();
    cout << "\n";
    l1.Traversebackward();

    cout << "Add In Sorted Order : \n";
    l1.AddInSortedOrder(7);
    l1.TraverseForward();

    cout << "Delete Node : \n";
    l1.DeleteNode(7);
    l1.TraverseForward();
    
    cout << "Reverse List : \n";
    l1.ReverseList();
    l1.TraverseForward();

    l1.ReverseList();
   
	DLL<int> l2;

    l2.AddInEnd(4);
    l2.AddInStart(3);
    l2.AddInStart(2);
    l2.AddInStart(1);
    l2.AddInEnd(11);
    cout << "l2 \n";
    l2.TraverseForward();

    cout << "Union : \n";
    l1.Union(l2);
    l1.TraverseForward();

    cout << "Display Next and Previous : " << endl;
    l1.DisplayNextPrevious(5);
    
    cout << "\nMiddle Data : " << l1.ReturnMiddle() << endl;

}



