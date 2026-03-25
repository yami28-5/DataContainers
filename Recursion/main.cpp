#include<iostream>
using namespace std;


void Elevator(int floor);
int Factorial(int n);
double Power(double a, int n);

void main()
{
	setlocale(LC_ALL, "");
	cout << "Hello World!";
	int n;
	int a;
	//cout << "Введите номер этажа: "; cin >> a;
	//Elevator(n);
	//cout << "Введите число: "; cin >> n;
	//cout << Factorial(n) << endl;
	cout << "Введите основание степени: "; cin >> a;
	cout << "Введите показатель степени: "; cin >> n;
	cout << Power(a, n) << endl;

}

void Elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже" << endl;
	Elevator(floor - 1);
	cout << "Вы на " << floor << " этаже" << endl;
}
int Factorial(int n)
{
	return n == 0 ? 1 : n * Factorial(n - 1);
}
double Power(double a, int n)
{
	if (n == 0)return 1;
	else if (n > 0)return a * Power(a, n - 1);
	else return 1 / Power(a, -n);
}