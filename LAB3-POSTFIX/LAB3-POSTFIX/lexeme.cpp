#include <math.h>
#include <string>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;
enum lexeme_type 
{
	number,            // 0
	plus,              // 1
	minus,             // 2
	un_minus,          // 3
	mult,              // 4
	divide,            // 5
	power,             // 6
	left_br,           // 7
	right_br           // 8
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
	int pr = -1;
	int s = -1;
	lexeme() {};
	lexeme(double res)
	{
		type = number;
		val = res;
		pr = -1;
	}
	lexeme(lexeme_type type, double val):type(type), val(val), pr(-1){}                         // числа
	lexeme(lexeme_type _type, int _pr)
	{
		type = _type;
		val = -1.0;
		if (type == number) { val = _pr; pr = -1; }
		else if (type == lexeme_type::plus) { pr = 2; }
		else if (type == lexeme_type::minus) { pr = 2; }
		else if (type == lexeme_type::mult) { pr = 3; }
		else if (type == lexeme_type::divide) { pr = 3; }
		else if (type == lexeme_type::power) { pr = 4; }
		else if (type == lexeme_type::left_br) { pr = -2; }
		else if (type == lexeme_type::right_br) { pr = -3; }
		
	}            
	lexeme(lexeme_type type, int s, double val):type(type),val(val),s(s) {}
 

};

lexeme getNextLexeme(string s, int pos, int &nexPos)
{
	int j = -1;
	char tmp = s[pos];
	double d = 0;
	lexeme l;
	if (tmp == '0' || tmp == '1' || tmp == '2' || tmp == '3' || tmp == '4' 
		|| tmp == '5' || tmp == '6' || tmp == '7' || tmp == '8' || tmp == '9')     
	{
		l = lexeme(number, (double)(tmp - '0'));
		if (  (    (pos + 1) != s.size() ) && (s[pos+1] =='0' || s[pos + 1] == '1' || s[pos + 1] == '2' || s[pos + 1 ]== '3' || s[pos + 1] == '4'
			|| s[pos + 1] == '5' || s[pos + 1] == '6' || s[pos + 1] == '7' || s[pos + 1] == '8' || s[pos + 1] == '9'))
		{
			int i = pos;
			d = (double)(s[pos]-'0');

			while ((   (i + 1) != s.size() )&& (s[i + 1] == '0' || s[i + 1] == '1' || s[i + 1] == '2' || s[i + 1] == '3' || s[i + 1] == '4'
				|| s[i + 1] == '5' || s[i + 1] == '6' || s[i + 1] == '7' || s[i + 1] == '8' || s[i + 1] == '9'))
			{
				d = d * 10 + (double)(s[i + 1]-'0');	
				i++;                                 
			}		
			 j = i - pos + 1;			
		}		                                                                         
	}
	else if (tmp == '+')
	{
		l = lexeme(lexeme_type::plus, 1);
	}
	else if (tmp == '-')
	{
		l = lexeme(lexeme_type::minus, 1);
		
	}
	else if (tmp == '*')
	{
		l = lexeme(lexeme_type::mult, 2);
	}
	else if (tmp == '/')
	{
		l = lexeme(lexeme_type::divide, 2);
	}
	else if (tmp == '^')
	{
		l = lexeme(lexeme_type::power, 3);
	}
	else if (tmp == '(')
	{
		l = lexeme(lexeme_type::left_br, 4);
	}
	else if (tmp == ')')
	{
		l = lexeme(lexeme_type::right_br, 4);
	}
	
	if(d != 0)
	{
		
		lexeme o;
		o = lexeme(number, j, d);
		
		return o;
	}
	else
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
				if (tmp.s == -1)
				{
					res.push_back(tmp);
			        st = waitOperator;
				}
				else
				{
					pos = pos + tmp.s - 1;
					res.push_back(tmp);
					st = waitOperator;
					
				}
				
				
			}
			else if (tmp.type == left_br)
			{
				res.push_back(tmp);
				st = waitNumber;                                  
				
			}
			else if (tmp.type == lexeme_type::minus)
			{
				
				pos++;
				tmp = getNextLexeme(s, pos, pos);
				tmp.val = tmp.val - (2 * tmp.val);
				if (tmp.s == -1)
				{
					res.push_back(tmp);
					st = waitOperator;
				}
				else
				{
					pos = pos + tmp.s - 1;
					res.push_back(tmp);
					st = waitOperator;
					
				}

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
				st = waitNumber;
				
			}
			else if (tmp.type == right_br)
			{
				res.push_back(tmp);
				st = waitOperator;
				
			}
			else if (tmp.type == lexeme_type::minus)
			{
				res.push_back(tmp);
				st = waitNumber;
				
			}
			else if (tmp.type == lexeme_type::mult)
			{
				res.push_back(tmp);
				st = waitNumber;
			}
			else if (tmp.type == lexeme_type::divide)
			{
				res.push_back(tmp);
				st = waitNumber;
			}
			else if (tmp.type == lexeme_type::power)
			{
				res.push_back(tmp);
				st = waitNumber;
			}
			else
			{
				
				throw "error";
				
			}
			
		}
		else if (st == waitNumber)
		{
			
			if (tmp.type == number)
			{
				if (tmp.s == -1)
				{
					res.push_back(tmp);
					st = waitOperator;
				}
				else
				{
					pos = pos + tmp.s - 1;
					res.push_back(tmp);
					st = waitOperator;

				}
			}
			else if (tmp.type == left_br)
			{
				res.push_back(tmp);
				st = waitNumber;
			}
			else if (tmp.type == lexeme_type::minus) 
			{
				                  
				pos++;
				tmp = getNextLexeme(s, pos, pos);
				tmp.val = tmp.val - (2 * tmp.val);
				
				if (tmp.s == -1)
				{
					res.push_back(tmp);
					st = waitOperator;
				}
				else
				{ 
					pos = pos + tmp.s-1;                   
					res.push_back(tmp);
					st = waitOperator;
					
				}
				
				

			}
			
		}
		pos++;
		
	}
	
	return res;
}

vector<lexeme> VectorToStack(vector<lexeme> data)
{
	vector<lexeme> res; 
	stack<lexeme> ser;
	int ii=0;
	for (int i = 0; i < data.size(); i++)
	{
		
		if (data[i].pr == -2) // (
		{
			   ser.push(data[i]);
		}
			                                                                      
		else if ((data[i].pr == 2) || (data[i].pr == 3) || (data[i].pr == 4))
		{
			while ( (!ser.empty()) && (ser.top().pr > data[i].pr))
			{
				ii++;
				res.push_back(ser.top());    
				ser.pop();
			}
			ser.push(data[i]);                                                           
			                                                                          
		}
		else if(data[i].pr == -3) // )
		{
			while ((!ser.empty()) && (ser.top().pr != -2))
			{
				ii++;
				res.push_back(ser.top());
				ser.pop();
			}
			
			ser.pop();
			
		}
		else
		{
			res.push_back(data[i]);                                               
			ii++;
			
		}
		
	}
	while (!ser.empty())
	{
		ii++;
		res.push_back(ser.top());
		ser.pop();
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
		else if (tmp.type == lexeme_type::un_minus)
		{
			lexeme tmp1, tmp2;
			tmp2 = calc.top();
			calc.pop();
			tmp1 = calc.top();
			calc.pop();
			calc.push(tmp1.val - tmp2.val);
		}
		
	}	
	return calc.top().val;
}

int main()
{
	string s;
	cin >> s;
	vector<lexeme> vectorLexeme = Parse(s);
	vector<lexeme> pep = VectorToStack(vectorLexeme);
	cout<< "\n" << PolishCalculate(pep) << "\n";
	system("pause");
	return 0;
}