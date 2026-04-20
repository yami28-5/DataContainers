#include<iostream>
using namespace std;

//Ðåêóðñèâíàÿ
//Èòåðàöèîííàÿ
//Ñòåê âûçîâîâ (Call stack)
//Stack overflow exception

class Fibonacci
{
	static void Calculate(int n, int a, int b)
	{
		if (a > n)return;
		cout << a << "\t";
		Calculate(n, b, a + b);
	}
public:
	static void Calculate(int n)
	{
		Calculate(n, 0, 1);
		cout << endl;
	}
};

void Elevator(int floor);
int Factorial(int n);
double Power(double a, int n);
void Fibonacci(int n, int a = 0, int b = 1);

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello World!";
	int n;
	int a;
	//cout << "Ââåäèòå íîìåð ýòàæà: "; cin >> n;
	//Elevator(n);
	//cout << "Ââåäèòå ÷èñëî: "; cin >> n;
	//cout << Factorial(n) << endl;
	/*cout << "Ââåäèòå îñíîâàíèå ñòåïåíè: "; cin >> a;
	cout << "Ââåäèòå ïîêàçàòåëü ñòåïåíè: "; cin >> n;
	cout << Power(a, n) << endl;*/
	cout << "Ââåäèòå ïðåäåë ðÿäà Ôèáîíà÷÷è: "; cin >> n;
	Fibonacci::Calculate(n);
	//Fibonacci(n, 22, 33);
	cout << endl;

	main();
}

void Elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Âû â ïîäâàëå" << endl;
		return;
	}
	cout << "Âû íà " << floor << " ýòàæå" << endl;
	Elevator(floor - 1);
	cout << "Âû íà " << floor << " ýòàæå" << endl;
}
int Factorial(int n)
{
	return n == 0 ? 1 : n * Factorial(n - 1);
	/*if (n == 0)return 1;
	else return n*Factorial(n - 1);*/
}
double Power(double a, int n)
{
	return n == 0 ? 1 : n > 0 ? a * Power(a, n - 1) : 1 / Power(a, -n);
	/*if (n == 0)return 1;
	else if(n>0)return a * Power(a, n - 1);
	else return 1 / Power(a, -n);*/
	//else return 1 / a * Power(a, n + 1);
}
void Fibonacci(int n, int a, int b)
{
	if (a > n)return;
	cout << a << "\t";
	Fibonacci(n, b, a + b);
}