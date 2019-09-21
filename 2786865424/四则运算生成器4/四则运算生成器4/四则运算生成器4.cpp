

#include "pch.h"
#include <iostream>
#include<string>
#include<ctime>
#include<stack>
#include<fstream>
#define random()(rand()%1000)
using namespace std;

stack<int> s1;
stack<char> s2;
typedef struct node {
	int sss[4];
	char oppp[3];
	int result;
	int ca;
}T;
T k[50];

char op(int a)
{
	char c[4] = { '+','-','*','/' };
	return c[a];
}
string formula(int n)
{
	string suanshi;
	int num1, num2, temp, a, t, count, i, j, Q;
	k[n].sss[0] = random() % 100 + 1;
	suanshi += to_string(k[n].sss[0]);
	do {
		count = random() % 3 + 1;
	} while (count == 1);
	k[n].ca = count;
	for (i = 0; i < count; i++)
	{
		char c;
		a = random() % 4;
		c = op(a);
		k[n].oppp[i] = c;
		k[n].sss[i + 1] = random() % 100 + 1;
		if (c == '/')
		{
			while(k[n].sss[i] < k[n].sss[i+1]){
				k[n].sss[i+1] = random() % 100 + 1;
			}
			while (k[n].sss[i] % k[n].sss[i+1] != 0)
			{
				Q = k[n].sss[i] % k[n].sss[i+1];
				k[n].sss[i+1]= Q;
			}
		}
		suanshi+= op(a) + to_string(k[n].sss[i+1]);
	}
	return suanshi;
}

void wenjian(string s[], int n)
{
	int i;
	ofstream out;
	out.open("daan.txt");
	for (i = 0; i < n; i++)
	{
		out<<s[i]<<endl;
	}
	out.close();
}

void Result(T k[], int n) {
	int i, top = 0, a, b;
	char c;
	for (i = 0; i < n; i++)
	{
		if (top == 0)
		{
			c = k[i].oppp[top];
			s1.push(k[i].sss[top]);
			s1.push(k[i].sss[top + 1]);
			s2.push(c);
			if (c== '*')
			{
				s2.top();
				a = s1.top();
				b = s1.top();
				k[i].result = a * b;
				s1.push(k[i].result);
			}
			if (c == '/')
			{
				s2.top();
				a = s1.top();
				b = s1.top();
				k[i].result = b/ a;
				s1.push(k[i].result);
			}
			top++;
		}
		else if (top > 0 && top < k[i].ca - 1)
		{
			s2.push(k[i].oppp[top]);
			s1.push(k[i].sss[top + 1]);
			if (k[i].oppp[top + 1] == '/' || k[i].oppp[top + 1] == '*')
			{	
				if (k[i].oppp[top] == '*')
				{
					s2.top();
					a = s1.top();
					b = s1.top();
					k[i].result = a * b;
					s1.push(k[i].result);
				}
				if (k[i].oppp[top] == '/')
				{
					s2.top();
					a = s1.top();
					b = s1.top();
					k[i].result = b / a;
					s1.push(k[i].result);
				}
				top++;
			}
			else
			{
				if (k[i].oppp[top] = '-')
				{
					s2.pop();
					a = s1.top();
					b = s1.top();
					k[i].result = b - a;
					s1.push(k[i].result);
				}

			}
		}
		else if (top == k[i].ca - 1)
		{
			s1.push(k[i].sss[top + 1]);
			s2.push(k[i].oppp[top]);
			c = s2.top();
			do {
				a = s1.top();
				b = s1.top();
				if (c == '-')
				{
					k[i].result = b - a;
					s1.push(k[i].result);
				}
				if (c == '+')
				{
					k[i].result = b + a;
					s1.push(k[i].result);
				}
				if (c== '*')
				{
					k[i].result = b * a;
					s1.push(k[i].result);
				}
				if (c== '/')
				{
					k[i].result = b / a;
					s1.push(k[i].result);
				}
			} while (!s2.empty());
		}
		s1.empty();
	}
}




int main()
{
	srand((unsigned)time(0));
	int i, n;
	cout << "需要生成多少道题目（小于50）：";
	cin >> n;
	string c;
	string s[50];
	c = "=";
	for (i = 0; i < n; i++)
	{
		s[i] = formula(i)+c;
		cout << s[i] << endl;
	}
	//Result(k, n);
	wenjian(s, n);
	

	
	return 0;
}