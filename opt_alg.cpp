#include"opt_alg.h"
double* expansion(matrix(*ff)(matrix, matrix, matrix), double x0, double d, double alpha, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		double* p = new double[2]{ 0,0 };
		int i = 0;
		solution X0(x0), X1(x0 + d);
		X0.fit_fun(ff, ud1, ud2);
		X1.fit_fun(ff, ud1, ud2);
		if (X0.y == X1.y)
		{
			p[0] = m2d(X0.x);
			p[1] = m2d(X1.x);
			return p;
		}
		if (X0.y < X1.y)
		{
			d *= -1;
			X1.x = X0.x + d;
			X1.fit_fun(ff, ud1, ud2);
			if (X1.y >= X0.y)
			{
				p[0] = m2d(X1.x);
				p[1] = m2d(X0.x) - d;
				return p;
			}
		}
		solution X2;
		while (true)
		{
			++i;
			X2.x = x0 + pow(alpha, i) * d;
			X2.fit_fun(ff, ud1, ud2);
			if (X2.y >= X1.y || solution::f_calls > Nmax)
				break;
			X0 = X1;
			X1 = X2;
		}
		d > 0 ? p[0] = m2d(X0.x), p[1] = m2d(X2.x) : (p[0] = m2d(X2.x), p[1] = m2d(X0.x));
		return p;
	}
	catch (string ex_info)
	{
		throw ("double* expansion(...):\n" + ex_info);
	}
}

solution fib(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		Xopt.ud = b - a;
		int n = static_cast<int>(ceil(log2(sqrt(5) * (b - a) / epsilon) / log2((1 + sqrt(5)) / 2)));
		int* F = new int[n] {1, 1};
		for (int i = 2; i < n; ++i)
			F[i] = F[i - 2] + F[i - 1];
		solution A(a), B(b), C, D;
		C.x = B.x - 1.0 * F[n - 2] / F[n - 1] * (B.x - A.x);
		D.x = A.x + B.x - C.x;
		C.fit_fun(ff, ud1, ud2);
		D.fit_fun(ff, ud1, ud2);
		for (int i = 0; i <= n - 3; ++i)
		{
			if (C.y < D.y)
				B = D;
			else
				A = C;
			C.x = B.x - 1.0 * F[n - i - 2] / F[n - i - 1] * (B.x - A.x);
			D.x = A.x + B.x - C.x;
			C.fit_fun(ff, ud1, ud2);
			D.fit_fun(ff, ud1, ud2);

			Xopt.ud.add_row((B.x - A.x)());
		}
		Xopt = C;
		Xopt.flag = 0;
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution fib(...):\n" + ex_info);
	}

}

solution lag(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, double gamma, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		Xopt.ud = b - a;
		solution A(a), B(b), C, D, D_old(a);
		C.x = (a + b) / 2;
		A.fit_fun(ff, ud1, ud2);
		B.fit_fun(ff, ud1, ud2);
		C.fit_fun(ff, ud1, ud2);
		//solution A1, B1, C1, D1;
		double l, m;
		while (true)
		{
			l = m2d(A.y * (pow(B.x) - pow(C.x)) + B.y * (pow(C.x) - pow(A.x)) + C.y * (pow(A.x) - pow(B.x)));
			m = m2d(A.y * (B.x - C.x) + B.y * (C.x - A.x) + C.y * (A.x - B.x));
			if (m <= 0)
			{
				Xopt = D_old;
				Xopt.flag = 2;
				return Xopt;
			}
			D.x = 0.5 * l / m;
			D.fit_fun(ff, ud1, ud2);
			if (A.x <= D.x && D.x <= C.x)
			{
				if (D.fit_fun(ff, ud1, ud2) < C.fit_fun(ff, ud1, ud2)) {
					A = A;
					C = D;
					B = C;
				}
				else {
					A = D;
					C = C;
					B = B;
				}
			}
			else if (C.x <= D.x && D.x <= B.x)
			{
				if (D.fit_fun(ff, ud1, ud2) < C.fit_fun(ff, ud1, ud2)) {
					A = C;
					C = D;
					B = B;
				}
				else {
					A = A;
					C = C;
					B = D;
				}
			}
			else
			{
				Xopt = D_old;
				Xopt.flag = 2;
				return Xopt;
			}
			Xopt.ud.add_row((B.x - A.x)());
			if (B.x - A.x < epsilon || abs(D.x() - D_old.x()) < gamma)
			{
				Xopt = D;
				Xopt.flag = 0;
				break;
			}
			if (solution::f_calls > Nmax)
			{
				Xopt = D;
				Xopt.flag = 1;
				break;
			}
			D_old = D;
		}
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution lag(...):\n" + ex_info);
	}
}

solution HJ(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution HJ(...):\n" + ex_info);
	}
}

solution HJ_trial(matrix(*ff)(matrix, matrix, matrix), solution XB, double s, matrix ud1, matrix ud2)
{
	try
	{
		//Tu wpisz kod funkcji

		return XB;
	}
	catch (string ex_info)
	{
		throw ("solution HJ_trial(...):\n" + ex_info);
	}
}

solution Rosen(matrix(*ff)(matrix, matrix, matrix), matrix x0, matrix s0, double alpha, double beta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Rosen(...):\n" + ex_info);
	}
}

solution pen(matrix(*ff)(matrix, matrix, matrix), matrix x0, double c, double dc, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try {
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution pen(...):\n" + ex_info);
	}
}

solution sym_NM(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double beta, double gamma, double delta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution sym_NM(...):\n" + ex_info);
	}
}

solution SD(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution SD(...):\n" + ex_info);
	}
}

solution CG(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution CG(...):\n" + ex_info);
	}
}

solution Newton(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix),
	matrix(*Hf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Newton(...):\n" + ex_info);
	}
}

solution golden(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution golden(...):\n" + ex_info);
	}
}

solution Powell(matrix(*ff)(matrix, matrix, matrix), matrix x0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Powell(...):\n" + ex_info);
	}
}

solution EA(matrix(*ff)(matrix, matrix, matrix), int N, matrix limits, int mi, int lambda, matrix sigma0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution EA(...):\n" + ex_info);
	}
}
