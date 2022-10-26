/*********************************************
Kod stanowi uzupe³nienie materia³ów do æwiczeñ
w ramach przedmiotu metody optymalizacji.
Kod udostêpniony na licencji CC BY-SA 3.0
Autor: dr in¿. £ukasz Sztangret
Katedra Informatyki Stosowanej i Modelowania
Akademia Górniczo-Hutnicza
*********************************************/

#include"opt_alg.h"

void lab1();
void lab2();
void lab3();
void lab4();
void lab5();
void lab6();

int main()
{
	try
	{
		lab1();
	}
	catch (string EX_INFO)
	{
		cerr << "ERROR:\n";
		cerr << EX_INFO << endl << endl;
	}
	system("pause");
	return 0;
}

void lab1()
{
	//Funkcja testowa
	double x0 = m2d(100), d = 1.0, alpha = 2, epsilon = 1e-5, gamma = 1e-200;
	int Nmax = 1000;
	double* ab;
	solution opt;
	cout << x0 << endl << endl;
	ab = expansion(ff1T, x0, d, alpha, Nmax);
	cout << ab[0] << '\t' << ab[1] << endl << endl;
	solution::clear_calls();

	opt = fib(ff1T, 10, 100, epsilon);
	cout << opt << endl << endl;
	solution::clear_calls();

	opt = lag(ff1T, -100, 100, 0.001, 1e-7, Nmax);
	cout << opt << endl;
	solution::clear_calls();

	//Zbiorniki
	//epsilon = 1e-10;
	//opt = fib(ff1R, 1e-4, 1e-2, epsilon);
	//cout << opt << endl << endl;
	//solution::clear_calls();
	////opt = lag(ff1R, 1e-4, 1e-2, epsilon, gamma, Nmax);
	////cout << opt << endl << endl;
	//solution::clear_calls();
}

void lab2()
{

}

void lab3()
{

}

void lab4()
{

}

void lab5()
{

}

void lab6()
{

}