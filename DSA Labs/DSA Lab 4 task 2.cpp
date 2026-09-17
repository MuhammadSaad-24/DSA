#include <iostream>

using namespace std;

template <class Type>
class CL
{
private:
    class Node;
    class ListIterator;
    Node* tail;
    Node* head;
    int size;
public:
    typedef ListIterator Iterator;
    CL();
    void InsertAtStart(const Type&);
    void InsertAtEnd(const Type&);
    void InsertBefore(const Type&,const Type&);
    void Print() const;
    bool IsEmpty() const;
    void DeleteAfter(Iterator&);
    void RemoveDuplicates();
    bool IsCircular() const;
    void SplitList(CL<Type>&,CL<Type>&);
    void Rotate(const Type&);
    Iterator Find(const Type&);
    ~CL();
};

template <typename Type>
class CL<Type>::Node
{
private:
public:
    Type data;
    Node* Next;
    Node(const Type&,Node* n = 0);
    ~Node();
};

template <typename Type>
CL<Type>::Node::Node(const Type& d,Node* n)
{
    data = d;
    Next = n;
}

template <typename Type>
CL<Type>::Node::~Node()
{
    data = 0;
    Next = nullptr;
}

template <typename Type>
class CL<Type>::ListIterator
{
private:
    Node* Iptr;
public:
    friend class CL;
    ListIterator();
    ListIterator(Node*);
    ListIterator operator++();
    ListIterator operator++(int);
    bool operator!() const;
    bool operator!=(const ListIterator) const;
    bool operator==(const ListIterator) const;
    Type& operator*();
    ListIterator operator=(const ListIterator&);
    Node* GetNode() const;
    ~ListIterator();
};


template <typename Type>
CL<Type>::ListIterator::ListIterator()
{
    Iptr = nullptr;
}

template <typename Type>
CL<Type>::ListIterator::ListIterator(Node* other)
{
    Iptr = other;
}

template <typename Type>
typename CL<Type>::ListIterator CL<Type>::ListIterator::operator++()
{
    Iptr = Iptr->Next;
    return Iptr;
}


template <typename Type>
typename CL<Type>::ListIterator CL<Type>::ListIterator::operator++(int)
{
    Node* Old = Iptr;
    Iptr = Iptr->Next;
    return Old;
}

template <typename Type>
bool CL<Type>::ListIterator::operator!() const
{
    return Iptr == nullptr;
}

template <typename Type>
bool CL<Type>::ListIterator::operator!=(const ListIterator other) const
{
    return Iptr != other.Iptr;
}
template <typename Type>
bool CL<Type>::ListIterator::operator==(const ListIterator other) const
{
    return Iptr == other.Iptr;
}

template <typename Type>
typename CL<Type>::ListIterator CL<Type>::ListIterator::operator=(const ListIterator& other)
{
    Iptr = other.Iptr;
    return *this;
}

template <typename Type>
Type& CL<Type>::ListIterator::operator*()
{
    if (!Iptr)
    {
        throw runtime_error("Derefrencing a Null Pointer");
    }

    return Iptr->data;
}


template <typename Type>
typename CL<Type>::Node* CL<Type>::ListIterator::GetNode() const
{
    return Iptr;
}

template <typename Type>
CL<Type>::ListIterator::~ListIterator()
{
    Iptr = nullptr;
}

template <typename Type>
CL<Type>::CL()
{
    tail = nullptr;
    size = 0;
}

template <typename Type>
void CL<Type>::InsertAtStart(const Type& data)
{
    if(!tail)
    {
        tail = new Node(data);
        tail->Next = tail;
    }
    else
        tail->Next = new Node(data,tail->Next);

    size++;
}

template <typename Type>
void CL<Type>::InsertAtEnd(const Type& data)
{
    if(!tail)
    {
        tail = new Node(data);
        tail->Next = tail; 
    }
    else
    {
        tail->Next = new Node(data,tail->Next);
        tail = tail->Next; 
    }
    size++;

}

template <typename Type>
void CL<Type>::InsertBefore(const Type& data,const Type& key)
{
    Iterator it = tail->Next;

    while(it != tail)
    {
        if(it.Iptr->Next->Data == key)
        {
            Node* temp = it.Iptr;
            temp->Next = new Node(data,temp->Next);
        }

        it++;
    }
    size++;

}

template <typename Type>
void CL<Type>::Print() const
{
    Iterator it = tail->Next;

    cout << "Circular List :: ";

    do
    {
        if(it.Iptr != tail)
            cout << *it << "->";
        else
            cout << *it;
        
        it++;
    }while(it != tail->Next);

    cout << endl;
}

template <typename Type>
bool CL<Type>::IsEmpty() const
{
    return tail == nullptr;
}

template <typename Type>
void CL<Type>::DeleteAfter(Iterator& it)
{
    Node* temp = it.Iptr;
    Node* todelete = temp->Next;

    if(temp->Next != nullptr)
        temp->Next = temp->Next->Next;
    
    if(temp->Next == tail)
        tail = it.Iptr;

    delete todelete;
    it++;
    size--;

}

template <typename Type>
void CL<Type>::RemoveDuplicates()
{
    Iterator innerit = tail->Next;

    do
    {
        Iterator oit = innerit;
        oit++;
        do
        {
            if(oit.Iptr->Next->data == *innerit)
            {
                DeleteAfter(oit);
                size--;
                Print();
            }

            oit++;

        }while(oit != tail->Next);

        innerit++;
    }while(innerit != tail->Next);
}

template <typename Type>
bool CL<Type>::IsCircular() const
{
    return tail->Next != nullptr;
}

template <typename Type>
void CL<Type>::SplitList(CL<Type>& l1,CL<Type>& l2)
{
    Iterator it = tail->Next;
    int count = 1;
    while(count < size / 2)
    {
        l1.InsertAtEnd(*it);
        it++;
        count++;
        l1.size++;
    }

    do
    {
        l2.InsertAtEnd(*it);
        it++;
        l2.size++;

    }while(it != tail->Next);

}

template <typename Type>
void CL<Type>::Rotate(const Type& units)
{
    int count = units;
    Iterator it = tail->Next;

    if(units > size)
        count = units % size;
    
    while(count)
    {   
        tail = tail->Next;
        count--;
    }
}

template <typename Type>
typename CL<Type>::Iterator CL<Type>::Find(const Type& key)
{
    Iterator it = tail->Next;

    do
    {
        if(it.Iptr->Data == key)
            return it;
        it++;

    }while(it.Iptr != tail);

    return nullptr;
}

template <typename Type>
CL<Type>::~CL()
{
    Iterator it = tail->Next;
    tail->Next = nullptr;

    while(it.Iptr != nullptr)
    {
        Node* temp = it.Iptr;
        it++;
        delete temp;
    }

    tail = nullptr;
    size = 0;
}

int main()
{
    CL<int> l1,l2;
    l1.InsertAtStart(1);
    l1.InsertAtEnd(2);
    l1.InsertAtEnd(3);
    l1.InsertAtEnd(4);
    l1.InsertAtEnd(5);

    l1.Print();

    l2.InsertAtEnd(10);
    l2.InsertAtStart(9);
    l2.InsertAtStart(8);
    l2.InsertAtStart(7);
    l2.InsertAtStart(6);
    l2.InsertAtStart(5);

    l2.Print();

    cout << "Rotate ::\n";
    l1.Rotate(3);
    l1.Print();

    l2.InsertAtStart(5);
    l2.Print();

    cout << "Remove duplicates::\n";
    l2.RemoveDuplicates();
    l2.Print();

    CL<int> l3,l4;

    cout << "Split L1::\n";

    l1.SplitList(l3,l4);
    cout << "l1::";
    l1.Print();

    cout << "l3::";
    l3.Print();
    
    cout << "l4::";
    l4.Print();

    cout << "Is Circular ? " << l3.IsCircular() << endl;
}