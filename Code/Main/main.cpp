#include "..\Parser\HPP\Parser.hpp"
#include <fstream>
#include <time.h>
#include <Windows.h>
using namespace yt::Runtime;
std::string get_file_content(const std::string & filename)
{
	using namespace std;
	ifstream ifs(filename);
	std::string file_content((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
	return file_content;
}
int lexer_test()
{
	try
	{
		time_t s = clock();
		std::string str = get_file_content("Text.txt");
		yt::Lexer::Lexer lex(str);
		lex.init_token_stream();
		std::cout << "lexer completed.\n" << "Time:" << double(clock() - s) / CLK_TCK << "s";
		//lex.debug();
	}
	catch (const std::exception & e)
	{
		std::cout << e.what();
	}
	std::cin.get();
	return 0;
}
int expression_test()
{
	try
	{
		time_t s = clock();
		std::string str = get_file_content("Text.txt");
		yt::Lexer::Lexer lex(str);
		lex.init_token_stream();
		//lex.debug();
		yt::Parser::Environment ev(&lex.token_stream);
		for (int i = 0; i < 100000; i++)
		{
			ev.current_pos = 1;
			yt::Parser::Expression expr(&ev);
			expr.CreateExpressionStack();
			expr.Translate();
			expr.debug();
		}
		std::cout << "\ncompleted.\n" << "Time:" << double(clock() - s) / CLK_TCK << "s\n press any key to exit";
	}
	catch (const std::exception & e)
	{
		std::cout << e.what();
	}
	std::cin.get();
	return 0;
}
void create_basic_object_test()
{
	time_t s = clock();
	std::string str = get_file_content("Text.txt");
	yt::Lexer::Lexer lex(str);
	lex.init_token_stream();
	lex.debug();
	yt::Parser::Environment ev(&lex.token_stream);

	while (1)
	{
		ev.stack_block.newBlock();
		ev.current_pos=1;
		yt::Parser::CreateBasicTypeObject cto(&ev);
		cto.execute();
		ev.stack_block.endBlock();

		//ev.stack_block.
	}
	ev.stack_block.debug();
}
void assign_test()
{
	time_t s = clock();
	std::string str = get_file_content("Text.txt");
	yt::Lexer::Lexer lex(str);
	lex.init_token_stream();
	lex.debug();
	yt::Parser::Environment ev(&lex.token_stream);
	yt::Parser::Parser parser(&ev);
	parser.execute();
	//ev.stack_block.debug();
	std::cin.get();
	std::cin.get();
	std::cin.get();
}
int main()
{
	try
	{
		assign_test();
		std::cin.get();

	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	Sleep(1000000);
	return 0;
}

