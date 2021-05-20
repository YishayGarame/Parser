#include "parser.h"
#include <iostream>
#include <stack>
#include "strings.h"

using namespace std;

void Parser::parse()
{
	terminal a = nextToken();
	Symbol dollar(END, TERM);
	Symbol symbolE(E, NONTERM);
	stack.push_back(dollar);
	stack.push_back(symbolE);
	cout << "| E" << endl;
	Symbol x = stack.back();


	// while loop until we get the "$" the end of the stack
	while (!(x.getType() == dollar.getType() && x.getSymbol() == dollar.getSymbol()))
	{
		if (x.getType() == TERM && x.getSymbol() == a)
		{			
			stack.pop_back();
			Symbol aSym(a, TERM);
			accepted.push_back(aSym);
			a = nextToken();

			//print accepted 
			printLM();
			cout << "| ";
			vector<Symbol> tmp;
			//PRINT STACK:
			while (!stack.empty())
			{
				Symbol curr = stack.back();
				stack.pop_back();
				tmp.push_back(curr);
				if (curr.getSymbol() == END && curr.getType() == TERM) continue;

				switch (curr.getType())
				{
				case TERM:
					cout << terminalStrings[curr.getSymbol()] << " ";
					break;
				case NONTERM:
					cout << tokenStrings[curr.getSymbol()] << " ";
					break;
				}

			}

			while (!tmp.empty())
			{
				Symbol curr = tmp.back();
				tmp.pop_back();
				stack.push_back(curr);
			}
			cout << endl;

		}
		//check if x is a terminal
		else if (x.getType() == TERM)
		{
			//error
			cout << "syntax error" << endl;
			return;

		}
		//check if M[x,a] is an error
		else if (table[x.getSymbol()][a] == -1)
		{
			cout << "syntax error" << endl;
			// error
			return;
		}
		//check if M[x,a] is legit derivation
		else
		{
			// holds the rule number from table
			int rule = table[x.getSymbol()][a];
			//pop
			stack.pop_back();

			//print accepted 
			printLM();
			cout << "| ";
			// push into stack the rules symbols
			for (Symbol sym : rules[rule])
			{
				if (sym.getSymbol() == EPSILON) continue;
				stack.push_back(sym);
			}

			//PRINT STACK:
			vector<Symbol> tmp;
			while (!stack.empty())
			{
				Symbol curr = stack.back();
				stack.pop_back();
				tmp.push_back(curr);
				if (curr.getSymbol() == END && curr.getType() == TERM) continue;

				switch (curr.getType())
				{
				case TERM:
					cout << terminalStrings[curr.getSymbol()] << " ";
					break;
				case NONTERM:
					cout << tokenStrings[curr.getSymbol()] << " ";
					break;
				}
				
			}
			while (!tmp.empty())
			{
				Symbol curr = tmp.back();
				tmp.pop_back();
				stack.push_back(curr);
			}
			
			cout << endl;
		}
		// LET X
		x = stack.back();
	}
}

terminal Parser::nextToken()
{
	string s;
	inputFile >> s;
	if (s == "id") return ID;
	if (s == "+") return PLUS;
	if (s == "*") return ASTERISK;
	if (s == "(") return LPAREN;
	if (s == ")") return RPAREN;
	
	return END;
}

void Parser::printLM()
{
	//holds the accepted arguments
	vector<Symbol> tmp;
	while (!accepted.empty())
	{
		Symbol curr = accepted.back();
		accepted.pop_back();
		tmp.push_back(curr);
		
	}
	while (!tmp.empty())
	{
		Symbol curr = tmp.back();
		//cout in the right way not backwords
		cout << terminalStrings[curr.getSymbol()] <<" ";
		tmp.pop_back();
		accepted.push_back(curr);
	}
	return;

}
