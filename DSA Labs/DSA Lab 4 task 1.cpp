#include <iostream>
using namespace std;


template <typename Type> class DLL
{
private:
    class Node;
    class ListIterator;
    Node* Head;
    Node* Tail;
    int size;

public:
    typedef ListIterator Iterator;
    DLL();
    DLL(DLL<Type>&);
    void PlaceNode(Node*,Node*);
    int CountNodes() const;
    void ReorderList();
    Iterator Begin();
    Iterator End();

    int SearchByID(const Type&) const;//Tells Position in Link List if present
    Iterator Find(const Type&) const;//Finds Data if present

    void AddInStart(const Type& data);
    void AddInEnd(const Type& data);

    void DeleteFromEnd();
    void DeleteFromStart();
    void DeleteNode(Iterator&);
    bool operator!() const;

    void TraverseForward() const;
    void Traversebackward() const;

    bool operator>(const Type& other) const { return size > other; }
    bool operator<(const Type& other) const { return size < other; }
    template <typename T>
    friend bool operator>(const Type& key, const DLL<T> data) { return key > data.size; }
    template <typename T>
    friend bool operator<(const Type& key, const DLL<T> data) { return key < data.size; }

    template <typename T>
    friend ostream& operator<<(ostream&, const DLL<T>&);

    void MergeLists(DLL<Type>&);
    DLL<Type> ReverseList();
    bool IsEqual(const DLL<Type>&) const;
    DLL<Type> Union(DLL<Type>&);
    DLL<Type> Intersection(const DLL<Type>&);
    DLL<Type> Difference(const DLL<Type>&);
    ~DLL();
};


template <typename Type>
class DLL<Type>::Node
{
public:
    Type Data;
    Node* Next;
    Node* Previous;
    Node(Type&, Node* = 0, Node* = 0);
    Node(const Type&, Node* = 0, Node* = 0);
    ~Node();
};

template <typename Type>
DLL<Type>::Node::Node(Type& d, Node* p, Node* n)
{
    Data = d;
    Next = n;
    Previous = p;
}

template <typename Type>
DLL<Type>::Node::Node(const Type& d, Node* p, Node* n)
{
    Data = d;
    Next = n;
    Previous = p;
}

template <typename Type>
DLL<Type>::Node::~Node()
{
    Next = nullptr;
    Previous = nullptr;
}


template <typename Type>
class DLL<Type>::ListIterator
{
    //friend dll
private:
    Node* Iptr;
public:
    ListIterator();
    ListIterator(Node*);
    ListIterator operator++();
    ListIterator operator++(int);
    ListIterator operator--();
    ListIterator operator--(int);
    bool operator!() const;
    bool operator!=(const ListIterator) const;
    bool operator==(const ListIterator) const;
    Type& operator*();
    Iterator operator=(const ListIterator&);
    bool IsNext() const;
    bool IsHead() const;
    bool IsTail() const;
    bool IsNull() const;
    Node* GetNode() const;
    ~ListIterator();
};

template <typename Type>
DLL<Type>::ListIterator::ListIterator()
{
    Iptr = nullptr;
}

template <typename Type>
DLL<Type>::ListIterator::ListIterator(Node* other)
{
    Iptr = other;
}

template <typename Type>
typename DLL<Type>::ListIterator DLL<Type>::ListIterator::operator++()
{
    Iptr = Iptr->Next;
    return Iptr;
}


template <typename Type>
typename DLL<Type>::ListIterator DLL<Type>::ListIterator::operator++(int)
{
    Node* Old = Iptr;
    Iptr = Iptr->Next;
    return Old;
}

template <typename Type>
typename DLL<Type>::ListIterator DLL<Type>::ListIterator::operator--()
{
    Iptr = Iptr->Previous;
    return Iptr;
}


template <typename Type>
typename DLL<Type>::ListIterator DLL<Type>::ListIterator::operator--(int)
{
    Node* Old = Iptr;
    Iptr = Iptr->Previous;
    return Old;
}

template <typename Type>
bool DLL<Type>::ListIterator::operator!() const
{
    return Iptr == nullptr;
}

template <typename Type>
bool DLL<Type>::ListIterator::operator!=(const ListIterator other) const
{
    return Iptr != other.Iptr;
}
template <typename Type>
bool DLL<Type>::ListIterator::operator==(const ListIterator other) const
{
    return Iptr == other.Iptr;
}

template <typename Type>
typename DLL<Type>::Iterator DLL<Type>::ListIterator::operator=(const ListIterator& other)
{
    Iptr = other.Iptr;
    return *this;
}

template <typename Type>
Type& DLL<Type>::ListIterator::operator*()
{
    if (!Iptr)
    {
        throw runtime_error("Derefrencing a Null Pointer");
    }

    return Iptr->Data;
}

template <typename Type>
bool DLL<Type>::ListIterator::IsHead() const
{
    return Iptr && Iptr->Previous == nullptr;
}

template <typename Type>
bool DLL<Type>::ListIterator::IsTail() const
{
    return Iptr && Iptr->Next == nullptr;
}

template <typename Type>
bool DLL<Type>::ListIterator::IsNull() const
{
    return Iptr == nullptr;
}

template <typename Type>
bool DLL<Type>::ListIterator::IsNext() const
{
    return Iptr->Next != nullptr;
}

template <typename Type>
typename DLL<Type>::Node* DLL<Type>::ListIterator::GetNode() const
{
    return Iptr;
}

template <typename Type>
DLL<Type>::ListIterator::~ListIterator()
{
    Iptr = nullptr;
}

template <typename Type> DLL<Type>::DLL()
{
    Head = nullptr;
    Tail = nullptr;
    size = 0;
}

template <typename Type> 
DLL<Type>::DLL(DLL<Type>& other)
{
    Head = Tail =nullptr;

    Node* temp = nullptr,*previous = nullptr;

    for (Iterator it = other.Begin(); it != nullptr;it++,temp = temp->Next)
    {
        if (it.IsHead())
        {
            Head = new Node(*it);
            temp = Head;
        }
        else
        {
            temp = new Node(*it,previous);
            temp->Previous->Next = temp;
        }

        if(it.IsTail())
            Tail = temp;

        previous = temp;
    }

    size = other.size;
}

template <typename Type> 
int DLL<Type>::CountNodes() const { return size; }


template <typename Type> 
void DLL<Type>::ReorderList()
{
    if(!Head)
        return;
    for(Iterator fit = Head->Next;fit != Tail && fit != nullptr;fit++)
    {    
        Node* key = fit.GetNode();
        
        Tail = Tail->Previous;
        PlaceNode(key,Tail->Next);
        Tail->Next = nullptr;
        
    }
}

template <typename Type> 
void DLL<Type>::PlaceNode(Node* key,Node* other)
{
    if(key == other)
        return;

    if(key->Previous == other)
        return;

    other->Next = key;
    other->Previous = key->Previous;
    
    if(key->Previous != nullptr)
        key->Previous->Next = other;
    
    key->Previous = other;
}

template <typename Type>
typename DLL<Type>::ListIterator DLL<Type>::Begin()
{
    if (!Head)
        cout << "Error::No Node Exist for Head To Point\n";

        return Iterator(Head);
}

template <typename Type>
typename DLL<Type>::ListIterator DLL<Type>::End()
{
    if (!Tail)
        cout << "Error::No Node Exist To Point Tail\n";

    return Iterator(Tail);
}

template <typename Type>
int DLL<Type>::SearchByID(const Type& key) const
{
    Iterator itr = Head;
    int count = 1;

    while (itr != nullptr)
    {
        if (*itr == key)
            return count;
        itr++;
        count++;
    }
    
    return -1;
}

template <typename Type>
typename DLL<Type>::ListIterator DLL<Type>::Find(const Type& key) const
{
    Iterator itr = Head;

    while (itr != nullptr)
    {
        if (*itr == key)
            return itr;

        itr++;
    }
    
    return nullptr;
}

template <typename Type>
void DLL<Type>::AddInStart(const Type& data)
{
    Iterator itr = Head;
    Node* NewNode = new Node(data);

    if (itr == nullptr)
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
void DLL<Type>::AddInEnd(const Type& data)
{
    Iterator itr = Tail;

    if (itr == nullptr)
        Head = Tail = new Node(data);
    else
    {
        Tail->Next = new Node(data, Tail);
        Tail = Tail->Next;
    }
    size++;
}

template <typename Type> 
void DLL<Type>::DeleteFromEnd()
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

template <typename Type> 
void DLL<Type>::DeleteFromStart()
{
    Iterator itr = Head;

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

template <typename Type>
void DLL<Type>::DeleteNode(Iterator& it)
{
    if (it.IsHead())
    {
        it++;
        DeleteFromStart();
    }
    else if (it.IsTail())
    {
        it--;
        DeleteFromEnd();
    }
    else
    {

        Node* temp = it.GetNode();
        temp->Previous->Next = temp->Next;
        temp->Next->Previous = temp->Previous;
        --it;
        delete temp;
        temp = nullptr;
        size--;
    }
}

template <typename Type>
void DLL<Type>::TraverseForward() const
{
    Node* Temp = Head;
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

template <typename Type> 
void DLL<Type>::Traversebackward() const
{
    Node* Temp = Tail;
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

template <typename Type> 
bool DLL<Type>::operator!() const
{
    return Head != nullptr;
}

template <typename Type>
ostream& operator<<(ostream& out, const DLL<Type>& DATA)
{
    typename DLL<Type>::Node* Temp = DATA.Head;
    
    typename DLL<Type>::Iterator it = DATA.Head;

    out << "Double Link List : ";

    while (it != nullptr)
    {
        if (it.IsNext())
            out << *it << "->";
        else
            out << *it;

        it++;
    }

    out << endl;
    return out;
}

template <typename Type> 
void DLL<Type>::MergeLists(DLL<Type>& other)
{
    Iterator it = Head,oit = other.Head;

    while (it != nullptr)
    {
        if (*it < *oit)
        {
            it++;
        }
        else if (*it > *oit)
        {
            Node* temp = it.GetNode();
            Node* otemp = oit.GetNode();

            oit++;
            //i2.iptr->next
            otemp->Previous = temp->Previous;
            otemp->Next = temp;
            if(temp != Head)
                temp->Previous->Next = otemp;
            temp->Previous = otemp;
            it++;

        }
        else
        {
            other.DeleteNode(oit);
            oit++;
            it++;
        }
    }

    if (oit != nullptr)
    {
        Tail->Next = oit.GetNode();
        Tail->Next->Previous = Tail;
        Tail = other.Tail;
    }

    other.Head = other.Tail = nullptr;
}

template <typename Type> 
DLL<Type> DLL<Type>::ReverseList()
{
    DLL<Type> l;
    Node* temp = nullptr,*previous = nullptr;
    
    l.size = size;
    
    for(Iterator it = End(); !it.IsNull();it--)
    {
        if (it.IsTail())
        {
            l.Head = new Node(*it);
            temp = l.Head;
        }
        else
        {
            temp = new Node(*it,previous);
            temp->Previous->Next = temp;
        }

        if(it.IsHead())
            l.Tail = temp;

        previous = temp;
    }

    return l;
}

template <typename Type> 
bool DLL<Type>::IsEqual(const DLL<Type>& other) const
{
    Iterator it = Head,oit = other.Head;
    
    if(size != other.size)
        return false;

    while(!it.IsNull())
    {
        if(*it != *oit)
            return false;

        it++;
        oit++;
    }

    return true;
}

template <typename Type> 
DLL<Type> DLL<Type>::Union(DLL<Type>& other)
{
    DLL<Type> u(other);

    Iterator it = Head;

    while(it != nullptr)
    {
        if(u.SearchByID(*it) == -1)
            u.AddInEnd(*it);
            
        it++;
    }

    return u;
}

template <typename Type> 
DLL<Type> DLL<Type>::Intersection(const DLL<Type>& other)
{
    DLL<Type> intersection;

    Iterator it = Head,oit = other.Head;

    while(it != nullptr)
    {
        if(other.SearchByID(*it) != -1)
        {
            intersection.AddInEnd(*it);
        }
        it++;
    }

    return intersection;
}

template <typename Type> 
DLL<Type> DLL<Type>::Difference(const DLL<Type>& other)
{
    DLL<Type> difference;

    Iterator it = Head,oit = other.Head;

    while(it != nullptr)
    {
        if(other.SearchByID(*it) == -1)
        {
            difference.AddInEnd(*it);
        }
        it++;
    }

    return difference;
}

template <typename Type> 
DLL<Type>::~DLL()
{
    Node* temp = Head;
    while (Head != nullptr)
    {
        temp = Head;
        Head = Head->Next;
        delete temp;
    }
    Head = Tail = nullptr;
    size = 0;
}


int main()
{
    DLL<int> l1;

    l1.AddInStart(3);
    l1.AddInStart(5);
    l1.DeleteFromStart();

    l1.AddInEnd(6);
    l1.AddInEnd(9);
    l1.AddInStart(2);
    l1.AddInStart(1);

    cout << "Position : " << l1.SearchByID(6) << endl;
    cout << l1;

    DLL<int> l2;

    l2.AddInStart(5);
    l2.AddInStart(7);
    l2.DeleteFromStart();

    l2.AddInEnd(7);
    l2.AddInEnd(10);
    l2.AddInStart(3);
    l2.AddInStart(2);

    cout << l2;

    DLL<int> l3(l1);
    DLL<int> Union = l1.Union(l2);
    cout << "Union::\n";
    cout << Union;
    
    DLL<int> Intersection = l1.Intersection(l2);
    cout << "Intersection::\n";
    cout << Intersection;

    DLL<int> Difference = l1.Difference(l2);
    cout << "Difference::\n";
    cout << Difference;

    cout << "Merge List :: " << endl;
    l1.MergeLists(l2);

    cout << l1;
    l1.Traversebackward();

    DLL<int>::Iterator it = l1.Find(12);
    if(!it.IsNull())
        cout << *it << endl;  
        
    DLL<int> l4;
    l4.AddInEnd(1);
    l4.AddInEnd(2);
    l4.AddInEnd(3);
    l4.AddInEnd(4);
    l4.AddInEnd(5);
    l4.AddInEnd(6);

    l4.ReorderList();
    cout << "Reorder List::\n";
    cout << l4;

    DLL<int> Reverse = l4.ReverseList();
    cout << "Reverse List::\n";
    cout << Reverse;
}