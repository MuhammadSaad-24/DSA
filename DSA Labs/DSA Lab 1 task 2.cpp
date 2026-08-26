#include <iostream>
#include<iomanip>
using namespace std;

template <typename Type>
class Matrix
{
private:
	Type** matrix;
	int rows;
	int cols;
public:

	Matrix(int r, int c)
	{
		rows = r;
		cols = c;
		matrix = new Type *[rows];
		
		for (int i = 0; i < rows; i++)
		{
			matrix[i] = new Type[cols];
		}

		cout << "Enter Matrix Entries :\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << "Matrix [" << i << "][" << j << "] : ";
				cin >> matrix[i][j];
			}
		}
	}
	
	void Display()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << matrix[i][j];
			}
			cout << endl;
		}
	}

	void SetElement()
	{
		cout << "Enter Matrix Entries :\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << "Matrix [" << i << "][" << j << "] : ";
				cin >> matrix[i][j];
			}
		}
	}

	int CountGreater() 
	{
		Type num;
		int count = 0;
	
		cout << "Entery Greater Than : ";
		cin >> num;

		cout << "Number Greater : ";

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (num < matrix[i][j])
				{
					cout << matrix[i][j] << ' ';
					count++;
				}
			}
		}
		cout << endl;

		return count;
	}

	int CountLesser()
	{
		int count = 0;
		Type num;
		cout << "Enter Number : ";
		cin >> num;

		cout << "Numbers Lesser : ";

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (num > matrix[i][j])
				{
					cout << matrix[i][j] << ' ';
					count++;
				}
			}
		}
		
		cout << endl;

		return count;
	}

	~Matrix()
	{
		for (int i = 0; i < rows; i++)
		{
			delete matrix[i];
			matrix[i] = nullptr;
		}

		delete matrix;
		matrix = nullptr;
	}

};
int main()
{
	Matrix<int> M1(3, 3);
	Matrix<char> M2(3, 3);

	cout << "Orignal Matrix : \n";
	M1.Display();

	int countG = M1.CountGreater();
	cout << "Number Greater : " << countG << endl;
	
	int countL = M1.CountLesser();
	cout << "Number Lesser : " << countL << endl;


	cout << "Orignal Matrix : \n";
	M2.Display();

	cin.ignore();

	int CountG = M2.CountGreater();
	cout << "Total Characters Greater : " << CountG << endl;
	
	int CountL = M2.CountLesser();
	cout << "Total Characters Lesser : " << CountL << endl;

}
