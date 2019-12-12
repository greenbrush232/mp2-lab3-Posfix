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
	mult,
	divide,
	power
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
	}
	lexeme(lexeme_type type, double val):type(type), val(val){}
};

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
	cout << PolishCalculate(data);
	system("pause");
	return 0;
}