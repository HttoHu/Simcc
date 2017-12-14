#include <iostream>
#include "../Lexer/HPP/Lexer.hpp"
#include "../Context/HPP/Type.hpp"
#include "../Parser/HPP/Statement.hpp"
using namespace Simcc;
using namespace Lexer;
int main()
{
	try
	{
		Parser::statement_test();
		//Expression::trans_expr_tree_test();
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
	std::cin.get();
	return 0;
}