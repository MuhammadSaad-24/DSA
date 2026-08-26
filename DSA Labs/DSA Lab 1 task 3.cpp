#include <iostream>
using namespace std;

template <typename Type>
class Inventory
{
private:
    Type* Data;
    int Capacity;
    int ItemCount;
public:
    
    Inventory(const int& cap)
    {
        Capacity = cap;
        ItemCount = 0;
        Data = new Type[cap];
    }
    
    int GetItemCount()
    {
        return ItemCount;
    }
    
    int GetCapacity()
    {
        return Capacity;
    }

    void AddItem(const int& Newitem)
    {
        if(Capacity > ItemCount)
        {
            Data[ItemCount++] = Newitem; 
        }

        else
        {
            Type* NewData = new Type[Capacity * 2];

            for(int i = 0;i < Capacity;i++)
            {
                NewData[i] = Data[i];
            }

            delete[] Data;
            Data = NewData;

            Data[ItemCount++] = Newitem; 

            Capacity *= 2;

        }
    }

    template <typename T>
    friend ostream& operator<<(ostream& out,const Inventory<T>& other)
    {
        for(int i = 0;i < other.ItemCount;i++)
        {
            if(i != other.ItemCount - 1)
                out << other.Data[i] << ',';

            else
                out << other.Data[i];    
        }

        out << "\n\nCapacity : " << other.Capacity << endl;
        out << "ItemCount : " << other.ItemCount << endl;

        return out;
    }

    Inventory& operator=(const Inventory& other)
    {
        if(this == &other)
            return *this;
        
        if(Data != nullptr)
        {
            delete[] Data;
            Data = nullptr;            
        }   

        Capacity = other.Capacity;
        ItemCount = other.ItemCount;

        Data = new Type[Capacity];

        for(int i = 0;i < Capacity;i++)
        {
            Data[i] = other.Data[i];
        }
        
        return *this;
    }

    ~Inventory()
    {
        try
        {
            if(Data != nullptr)
            {
                delete[] this->Data;
                Data = nullptr;    
            }
        }
        catch(exception& e)
        {
            cout << e.what();
        }
    }
};

int main()
{
    Inventory<int> inventory1(2);
    
    inventory1.AddItem(101);
    inventory1.AddItem(205);
    inventory1.AddItem(310);
    
    cout << inventory1 << endl;

    Inventory<int> inventory2(3);
    inventory2 = inventory1;

    inventory2.AddItem(676);
    inventory2.AddItem(574);

    cout << inventory2 << endl;
    
    return 0;
}