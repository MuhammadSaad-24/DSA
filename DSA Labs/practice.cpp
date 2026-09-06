#include<iostream>
#include<iomanip>
using namespace std;

template<class Type>
class DLL
{
private:
    class Node;
    Node* Head;
    Node* Tail;
public:
    DLL();
    Node* Find(const Type&);
    void AddInStart(const Type& data);
    void AddBefore(const Type& key,const Type& data);
    void AddAfter(const Type&,const Type& data);
    void AddInEnd(const Type& data);
    void DeleteFromEnd();
    void DeleteFromStart();
    void DeleteBefore(const Type&);
    void DeleteAfter(const Type&);
    bool operator!();
    template <typename T>
    friend ostream& operator<<(ostream&, const DLL<T>&);
    ~DLL();
};

template <typename Type>
DLL<Type>::DLL()
{
    Head = nullptr;
    Tail = nullptr;
}

template <typename Type>
typename DLL<Type>::Node* DLL<Type>::Find(const Type& key)
{
    Node* temp = Head;

    while(temp != nullptr)
    {
        if(temp->Data == key)
            return temp;

        temp = temp->Next;
    }

    return nullptr;
}

template <typename Type>
void DLL<Type>::AddInStart(const Type& data)
{
    Node* NewNode = new Node(data);

    if(Head == nullptr)
        Head = Tail = NewNode;
    else
    {
        Head->Previous = NewNode;
        NewNode->Next = Head;
        Head = NewNode;
    }

}

template <typename Type>
void DLL<Type>::AddBefore(const Type& Key,const Type& data)
{
    Node* RequiredPlace = Find(Key);

    if(!RequiredPlace)
    {
        cout << "Error:: "<< Key << " Not Found!!" << endl;
        return;
    }

    Node* NewNode = new Node(data);

    if(Head == RequiredPlace)
        AddInStart(data);

    else if(RequiredPlace)
    {
        NewNode->Previous = RequiredPlace->Previous;
        NewNode->Next = RequiredPlace;
        RequiredPlace->Previous->Next = NewNode;
        RequiredPlace->Previous = NewNode;
    }

}

template <typename Type>
void DLL<Type>::AddAfter(const Type& Key,const Type& data)
{
    Node* RequiredPlace = Find(Key);
    
    if(!RequiredPlace)
    {
        cout << "Error:: "<< Key << " Not Found!!"  << endl;
        return;
    } 

    Node* NewNode = new Node(data);

    if(Tail == RequiredPlace)
        AddInEnd(data);

    else if(RequiredPlace)
    {
        NewNode->Next = RequiredPlace->Next;
        NewNode->Previous = RequiredPlace;
        RequiredPlace->Next->Previous = NewNode;
        RequiredPlace->Next = NewNode;
    }

}
template <typename Type>
void DLL<Type>::AddInEnd(const Type& data)
{
    if(Head == nullptr)
        Head = Tail = new Node(data);
    else
    {
        Tail->Next = new Node(data,Tail);
        Tail = Tail->Next;
    }
}

template <typename Type>
void DLL<Type>::DeleteFromEnd()
{
    if(Head != Tail)// handles when list is empty or has more than one entry
    {
        Tail = Tail->Previous;
        delete Tail->Next;
        Tail->Next = nullptr;
    }
    else if(Head != nullptr)// when Head == Tail but not empty
    {
        delete Head;
        Head = Tail = nullptr;
    }
    
}

template <typename Type>
void DLL<Type>::DeleteFromStart()
{
    if(Head != Tail)// handles when list is empty or has more than one entry
    {
        Head = Head->Next;
        delete Head->Previous;
        Head->Previous = nullptr;
    }
    else if(Head != nullptr)// when Head == Tail but not empty
    {
        delete Head;
        Head = Tail = nullptr;
    }
}

template <typename Type>
void DLL<Type>::DeleteBefore(const Type& Key)
{
    Node* RequiredPlace = Find(Key);

    if(!RequiredPlace)
        cout << "Error:: "<< Key << " Not Found!!" << endl;

    else if(RequiredPlace == Head)
    {
        cout << "Error:: Cannot Delete Data Before Head!!!" << endl;
        return;
    }
    else if(RequiredPlace == Head->Next)
        DeleteFromStart();
    else
    {
        Node* temp = RequiredPlace->Previous;
        temp->Previous->Next = RequiredPlace;
        RequiredPlace->Previous = temp->Previous;
        delete temp;
        temp = nullptr;
    }
}

template <typename Type>
void DLL<Type>::DeleteAfter(const Type& Key)
{
    Node* RequiredPlace = Find(Key);
    
    if(!RequiredPlace)
        cout << "Error:: "<< Key << " Not Found!!" << endl;
    
    else if(Tail == RequiredPlace)
        cout << "Error::Cannot Delete Data after Tail!!" << endl;

    else if(Tail->Previous == RequiredPlace)
        DeleteFromEnd();
    
    else
    {
        Node* temp = RequiredPlace->Next;
        temp->Next->Previous = RequiredPlace;
        RequiredPlace->Next = temp->Next;
        delete temp;
        temp = nullptr; 
    }
}

template <typename Type>
bool DLL<Type>::operator!()
{
    return Head != nullptr;
}

template <typename Type>
ostream& operator<<(ostream& out, const DLL<Type>& DATA)
{
    typename DLL<Type>::Node* Temp = DATA.Head;

    while(Temp != nullptr)
    {
        if(Temp != DATA.Tail)
            out << Temp->Data << "->";
        else
            out << Temp->Data;
            
        Temp = Temp->Next;
    }
    out << endl;
    return out;
}

template <typename Type>
DLL<Type>::~DLL()
{
    Node* temp = Head;

    while(Head != nullptr)
    {
        temp = Head;
        Head = Head->Next;
        delete temp;
    }

    Head = Tail = nullptr; 
}


template<class Type>
class DLL<Type>:: Node
{
public:
    Type Data;
    Node* Next;
    Node* Previous;
    Node(const Type&,Node* = 0,Node* = 0);
    ~Node();
};

template <class Type>
DLL<Type>::Node::Node(const Type& d,Node* p,Node* n)
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

int main()
{
    DLL<int> DL1;
    DLL<int> DL2;

    DL1.AddInEnd(2);
    DL1.AddInEnd(4);
    DL1.AddInEnd(6);
    DL1.AddInEnd(8);
    DL1.AddInEnd(10);
    cout << DL1;
    DL1.AddAfter(10,12);
    cout << DL1;
    DL1.AddBefore(2,0);
    cout << DL1;

    DL2.AddInStart(1);
    DL2.AddInStart(2);
    DL2.AddInStart(3);
    DL2.AddInStart(4);
    DL2.AddInStart(5);
    cout << DL2;
    DL2.AddBefore(5,6);
    cout << DL2;
    DL2.AddAfter(1,0);
    cout << DL2;

    DL1.DeleteFromEnd();
    cout << DL1;
    DL1.DeleteFromStart();
    cout << DL1;
    DL1.DeleteAfter(4);
    cout << DL1;
    DL1.DeleteBefore(4);
    cout << DL1;

    DL2.DeleteFromEnd();
    cout << DL2;
    DL2.DeleteFromStart();
    cout << DL2;
    DL2.DeleteAfter(0);
    cout << DL2;
    DL2.DeleteBefore(0);
    cout << DL2;

}