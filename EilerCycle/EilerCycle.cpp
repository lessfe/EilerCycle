#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <fstream>
#include <conio.h>
#include <stack>
using namespace std;
int i, j;
int n;
bool point;

void show_graphsmezh(int n, vector<vector<bool>> a)
{
	cout << "--------Матрица смежности--------" << endl;
	for (i = 0; i < n; i++)
	{
		cout << "\t";
		for (j = 0; j < n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << " " << endl;
	}
	cout << endl;

}

vector<vector<bool>> set_graphsmezh()
{
	bool z;
	n = 0;	
	cout <<"Введите количество вершин матрицы смежности: "; cin >> n;
	vector<vector<bool>> a(n, vector<bool>(n));
		for (i = 0; i< n; i++)
		{
			for (j = 0; j <n; j++)
			{
				cin>> z; 
					
				a[i][j] = z; 
			}
		}
		cout << endl;
		point = 1; 
		show_graphsmezh(n, a);
		cout << endl;
	return a;
}

vector<vector<bool>> get_graphf() 
{
	bool b;
	n = 36;
	
	ifstream f("C:\\Users\\vladi\\source\\repos\\EilerCycle\\graph.txt");
	if (!f.is_open())
	{
		cout << "Ошибка";
	}
	else
	{		
		n = sqrt(n);
		vector<vector<bool>> a(n, vector<bool>(n)); 

		for (i = 0; i < n; i++)
		{
			for (j = 0; j< n; j++)
			{
				f >> b;
				a[i][j] = b;
			}
			
		}

		f.close();
		point = 1; 
			show_graphsmezh(n, a);
		return a;
	}
}

void eilerpath(vector<vector<bool>> a, int v) 
{
	vector<vector<bool>> e(n, vector<bool>(n)); 
		for (i = 0; i< n; i++)
		{
			for (j = 0; j< n; j++)
			{
				e[i][j] = a[i][j]; 
			}
		}
	vector<int> check; 
		vector<int> vert; 
		int f;
		for (i = 0; i< n; i++)
		{
			f = 0;
			for (j = 0; j <n; j++)
			{
				if (e[i][j] == 1 && i != j) 
				{
					f++;
				}
			}
			check.push_back(f);
		}
	f = 0;
	for (i = 0; i < n; i++)
	{
		if (check[i] % 2 != 0) 
		{
			f++;
		}
	}
	for (i = 0; i< n; i++)
	{
		if (check[i] == 0) 
		{
			cout <<"Цикла Эйлера не существует" <<  endl;
			return;
		}
	}
	if (f > 0 , i == v) 
	{
		cout <<"Цикла Эйлера не существует" << endl;
		return;
	}
	stack<int> stck;
		stck.push(v); 
		while (!stck.empty())
		{
			for (i = 0; i< n; i++)
			{
				for (i = 0; i< n; i++)
				{
					if (e[stck.top()][i])
					{
						break;
					}
				}
				if (i == n)
				{
					vert.push_back(stck.top());
					stck.pop();
				}
				else 
				{
					e[stck.top()][i] = 0;
					e[i][stck.top()] = 0;
					stck.push(i);
				}
			}
		}
		cout << "-----------Цикл Эйлера-----------" << endl << "\t";
	for (i = 0; i < vert.size(); i++) 
	{
		if (i != vert.size() - 1)
		{
			cout << vert[i] << "-";
		}
		else
		{
			cout << vert[i] << endl;
		}
	}
	cout << endl;
	e.clear();
}

int main()
{
	int r = 0;
	int c;
	setlocale(LC_ALL, "ru");
	point = 0;
	vector<vector<bool>> a(n, vector<bool>(n));

	do
	{
		cout <<"1 - Ввод графа с клавиатуры" <<  endl;
		cout <<"2 - Ввод из файла" << endl;
		cout <<"3 - Цикл Эйлера" << endl;
		cout <<"4 - Выход" << endl;
		cin >> c;

		switch (c)
		{
		case 1:
			{
				a = set_graphsmezh();
			}
			break;
			case 2:
			{
				a = get_graphf();
			}
			break;
			case 3:
			{
				if (point == 1)
				{
					cout <<"Введите начальную вершину: ";
					cin >> r;
					cout << endl;
					
					eilerpath(a, r);
				}
				else
				{
					cout <<"!Граф отсутствует" << endl; break;
				}
			}
			break;
			case 4:
			{
				return(0);
			}
			default: cout <<"Ошибка" << endl; break;
		}
	} while (c != 0);
}