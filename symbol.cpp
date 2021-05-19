#include "symbol.h"
#include "strings.h"

Type Symbol::getType()
{
	return type;
}
int Symbol::getSymbol()
{
	return symbol;
}
void Symbol::printSymbol()
{
	// we will do switch case for the type
	//TERM , NONTERM
	switch (type)
	{
	case TERM:
		cout << terminalStrings[symbol] << " ";
		break;
	case NONTERM:
		cout << tokenStrings[symbol] << " ";
		break;
	default:
		cout << "syntax error";
		break;
	}

}