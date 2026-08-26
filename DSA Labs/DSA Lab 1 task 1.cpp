#include <iostream>
using namespace std;

class Employee
{
protected:
	const int ID;
	string Name;
	int OverTime[4];
	int Performance[6];
public:
	Employee(const int id, const string name, int overtime[],int performance[]) : ID(id)
	{
		Name = name;

		for (int i = 0; i < 4; i++)
		{
			OverTime[i] = overtime[i];
		}

		for (int i = 0; i < 6; i++)
		{
			Performance[i] = performance[i];
		}
	}

	int CalculateOverTimeHours()
	{
		int totalHours = 0;

		for (int i = 0; i < 4; i++)
		{
			totalHours += OverTime[i];
		}

		return totalHours;
	}

	float CalculateAveragePerformance()
	{
		float average = 0;

		for (int i = 0; i < 6; i++)
		{
			average += Performance[i];
		}

		return (average / 6 );
	}
	virtual double CalculateSalary() = 0;
	virtual void Output() = 0;
};

class FullTimeEmployee : public Employee
{
	double BasicSalary;
public:
	FullTimeEmployee(const int id,string name,double sal,int overtime[],int per[]) : Employee(id, name, overtime, per)
	{
		BasicSalary = sal;
	}

	double CalculateSalary() override
	{
		double FinalSalary = BasicSalary + 0.2 * BasicSalary + 0.1 * BasicSalary + CalculateOverTimeHours() * 500;

		float AveragePerformance = CalculateAveragePerformance();

		if (AveragePerformance > 90)
			FinalSalary += 0.1 * BasicSalary;
		
		else if (AveragePerformance <= 90 && AveragePerformance > 80)
			FinalSalary += 0.07 * BasicSalary;

		else if(AveragePerformance <= 80 && AveragePerformance > 70)
			FinalSalary += 0.05 * BasicSalary;

		return FinalSalary;
	}

	void Output() override
	{
		cout << "Employee ID : " << ID << endl;
		cout << "Name : " << Name << endl;
		cout << "Full Time " << endl << endl;

		float AveragePerformance = CalculateAveragePerformance();
		
		cout << "Average Performance : " << AveragePerformance << endl;

		cout << "Bonous Percentage : ";
		
		if (AveragePerformance > 90)
				cout << "10%";

		else if (AveragePerformance <= 90 && AveragePerformance > 80)
				cout << "7%";

		else if (AveragePerformance <= 80 && AveragePerformance > 70)
				cout << "5%";
		else
			cout << "0";

		cout << endl << endl;

		cout << "\nBasic Salary : " << BasicSalary << endl;
		cout << "HRA : " << BasicSalary * 0.2 << endl;
		cout << "Medical Allowance : " << BasicSalary * 0.1 << endl;
		cout << "OverTime Hours : " << CalculateOverTimeHours() << endl;
		cout << "OverTime Compensation : " << CalculateOverTimeHours() * 500 << endl;

		cout << "Performance Bonous : ";

		if (AveragePerformance > 90)
			cout << 0.1 * BasicSalary;

		else if (AveragePerformance <= 90 && AveragePerformance > 80)
			cout << 0.07 * BasicSalary;

		else if (AveragePerformance <= 80 && AveragePerformance > 70)
			cout << 0.05 * BasicSalary;

		cout << endl << endl;

		cout << "Final Salary : " << CalculateSalary() << endl;

		cout << "Workload Classification :  ";

		if (CalculateOverTimeHours() > 20)
			cout << "Hogh Workload";
		else
			cout << "Normal";

		cout << endl;

	}
};

class PartTimeEmployee : public Employee
{
private:
	int RegularWorkingHours;
	double HourlyWadge;
public:
	
	PartTimeEmployee(const int id, string name, double wadge,int Whours,int overtime[],int perf[]) : Employee(id, name, overtime, perf)
	{
		RegularWorkingHours = Whours;
		HourlyWadge = wadge;
	}

	double CalculateSalary() override
	{
		double RegularSalary = RegularWorkingHours * HourlyWadge;

		double FinalSalary = RegularSalary + CalculateOverTimeHours() * 500;

		float AveragePerformance = CalculateAveragePerformance();

		if (AveragePerformance > 90)
			FinalSalary += 0.1 * RegularSalary;

		else if (AveragePerformance <= 90 && AveragePerformance > 80)
			FinalSalary += 0.07 * RegularSalary;

		else if (AveragePerformance <= 80 && AveragePerformance > 70)
			FinalSalary += 0.05 * RegularSalary;

		return FinalSalary;
	} 

	void Output() override
	{
		cout << "Employee ID : " << ID << endl;
		cout << "Name : " << Name << endl;
		cout << "Part Time " << endl << endl;

		float AveragePerformance = CalculateAveragePerformance();

		cout << "Average Performance : " << AveragePerformance << endl;

		cout << "Bonous Percentage : ";

		if (AveragePerformance > 90)
			cout << "10%";

		else if (AveragePerformance <= 90 && AveragePerformance > 80)
			cout << "7%";

		else if (AveragePerformance <= 80 && AveragePerformance > 70)
			cout << "5%";
		else
			cout << "0";

		cout << endl << endl;

		double RegularSalary = HourlyWadge * RegularWorkingHours;

		cout << "Regular Salary : " << HourlyWadge * RegularWorkingHours << endl;
		cout << "OverTime Hours : " << CalculateOverTimeHours() << endl;
		cout << "OverTime Compensation : " << CalculateOverTimeHours() * 500 << endl;

		cout << "Performance Bonous : ";

		if (AveragePerformance > 90)
			cout << 0.1 * RegularSalary;

		else if (AveragePerformance <= 90 && AveragePerformance > 80)
			cout << 0.07 * RegularSalary;

		else if (AveragePerformance <= 80 && AveragePerformance > 70)
			cout << 0.05 * RegularSalary;

		cout << endl << endl;

		cout << "Final Salary : " << CalculateSalary() << endl;

		cout << "Workload Classification :  ";

		if (CalculateOverTimeHours() > 20)
			cout << "Hogh Workload";
		else
			cout << "Normal";

		cout << endl;
	}
};


int main()
{
	Employee* Employees[2];

	int per1[6] = { 71,34,89,99,100,88 };
	int per2[6] = { 90,80,70,90,100,78 };
	int over1[4] = { 4,5,9,4 };
	int over2[4] = { 5,5,6,2 };
	Employees[0] = new PartTimeEmployee(1, "Sara", 700, 80, over1,per1 );
	Employees[1] = new FullTimeEmployee(2, "Ali", 100000, over2,per2 );

	for (int i = 0; i < 2; i++)
	{
		cout << "--------------------------------------\n";
		Employees[i]->Output();
		cout << endl;
	}

	for (int i = 0; i < 2; i++)
	{
		delete Employees[i];
	}
}