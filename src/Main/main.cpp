#include <iostream>
#include "../Lexer/HPP/Lexer.hpp"
int main()
{
	Simcc::Lexer::lex_init("Lex.sic");
	Simcc::Lexer::debug();
	std::cin.get();
	return 0;
}