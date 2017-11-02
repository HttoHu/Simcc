#include "..\Parser\HPP\Function.hpp"
#include "../Parser/HPP/Block.hpp"
#include <fstream>
#include <time.h>
#include <Windows.h>
using namespace Simcc::Runtime;
std::string get_file_content(const std::string & filename);
void block_test()
{

	std::string str = get_file_content("Text.txt");
	Simcc::Lexer::Lexer lex(str);
	lex.init_token_stream();
	lex.debug();
	Simcc::Parser::Environment::token_stream = &lex.token_stream;
	Simcc::Parser::Block block;
	time_t s = clock();
	block.execute();
	std::cout << std::endl<<"====================================="<<std::endl;
	Simcc::Parser::Environment::stack_block.debug();
	std::cout << (double)(clock()-s)/CLK_TCK<<"\n";
}
void lexer_test()
{
	std::string str = get_file_content("Text.txt");
	Simcc::Lexer::Lexer lex(str);
	lex.init_token_stream();
	lex.debug();
}
void function_test()
{
	std::string str = get_file_content("Text.txt");
	Simcc::Lexer::Lexer lex(str);
	lex.init_token_stream();
	lex.debug();
	std::cout << std::endl;
	Simcc::Parser::Environment::token_stream = &lex.token_stream;
	Simcc::Parser::Function fuc;
	fuc.execute(new Simcc::Parser::Param());
}
int main()
{
	/* Text.txt ÄÚÈÝ
	*
	{
	int a=10;
	string str="hello world";
	if(str=="hello world")
	--a;
	}
	*/
	try
	{
		function_test();
		std::cin.get();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	Sleep(1000000);
	return 0;
}

