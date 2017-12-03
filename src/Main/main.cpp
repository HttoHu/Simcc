#include <iostream>
#include "../Lexer/HPP/Lexer.hpp"
#include "../Parser/HPP/Expression.hpp"
using namespace Simcc;
using namespace Lexer;
using namespace ExprTree;
int main()
{
	try
	{
		Simcc::Lexer::lex_init("Lex.sic");
		Simcc::Expression::set_expr_tree(Simcc::Lexer::token_stream)->print(" ", false);
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
	std::cin.get();
	return 0;
}