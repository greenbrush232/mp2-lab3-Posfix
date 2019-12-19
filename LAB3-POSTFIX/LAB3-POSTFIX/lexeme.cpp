#include <math.h>
#include <string>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;
enum lexeme_type 
{
	number,
	plus,
	minus,
	un_minus,
	mult,
	divide,
	power,
	left_br,
	right_br
};

enum status
{
	start,
	waitOperator,
	waitNumber
};

struct lexeme
{
	lexeme_type type;
	double val;
	int pr;
	lexeme() {};
	lexeme(double res)
	{
		type = number;
		val = res;
		pr = -1;
	}
	lexeme(lexeme_type type, double val):type(type), val(val){}
	lexeme(lexeme_type type, int pr):type(type), pr(pr), val(-1.0) {}
};

lexeme getNextLexeme(string s, int pos, int &nexPos)
{
	nexPos = pos;
	char tmp = s[pos];
	lexeme l;
	if (tmp >= '0' || tmp <= '9')
	{
		l = lexeme(number, tmp - '0');
		nexPos++;
	}
	else if (tmp == '+')
	{
		l = lexeme(lexeme_type::plus, 1);
	}
	return l;
}

vector<lexeme> Parse(string s)
{
	lexeme tmp;
	vector<lexeme> res;
	status st = start;
	int pos = 0;
	while (pos != s.size())
	{
		tmp = getNextLexeme(s, pos, pos);
		if (st == start)
		{
			if (tmp.type == number)
			{
				res.push_back(tmp);
				st = waitOperator;
			}
			else if (tmp.type == left_br)
			{
				res.push_back(tmp);
				st = waitNumber;
			}
			else
			{
				throw "error";
			}
		}
		else if (st == waitOperator)
		{
			if (tmp.type == lexeme_type::plus)
			{
				res.push_back(tmp);
			}
		}
		else if (st == waitNumber)
		{

		}
	}
	return res;
}

double PolishCalculate(vector<lexeme> data)
{
	lexeme tmp;
	stack<lexeme> calc;
	for (int i = 0; i < data.size(); i++)
	{
		tmp = data[i];
		if (tmp.type == number)
		{
			calc.push(tmp);
		}
		else if (tmp.type == lexeme_type::plus)
		{
			lexeme tmp1, tmp2;
			tmp2 = calc.top();
			calc.pop();
			tmp1 = calc.top();
			calc.pop();
			calc.push(tmp1.val + tmp2.val);
		}
		else if (tmp.type == lexeme_type::minus)
		{
			lexeme tmp1, tmp2;
			tmp2 = calc.top();
			calc.pop();
			tmp1 = calc.top();
			calc.pop();
			calc.push(tmp1.val - tmp2.val);
		}
		else if (tmp.type == lexeme_type::mult)
		{
			lexeme tmp1, tmp2;
			tmp2 = calc.top();
			calc.pop();
			tmp1 = calc.top();
			calc.pop();
			calc.push(tmp1.val * tmp2.val);
		}
		else if (tmp.type == lexeme_type::divide)
		{
			lexeme tmp1, tmp2;
			tmp2 = calc.top();
			calc.pop();
			tmp1 = calc.top();
			calc.pop();
			calc.push(tmp1.val / tmp2.val);
		}
		else if (tmp.type == lexeme_type::power)
		{
			lexeme tmp1, tmp2;
			tmp2 = calc.top();
			calc.pop();
			tmp1 = calc.top();
			calc.pop();
			calc.push( pow(tmp1.val, tmp2.val) );
		}
	}
	return calc.top().val;
}

int main()
{
	vector<lexeme> data = {lexeme(number, 2), lexeme(number, 3), lexeme(lexeme_type::power, -1), lexeme(number, 5), lexeme(lexeme_type::mult, -1) };
	cout << PolishCalculate(data) << "\n";
	auto vectorLexeme = Parse("5+");
	for (auto l : vectorLexeme)
		cout << l.val << " ";
	system("pause");
	return 0;
}