#include "..\Parser\HPP\CreateObject.hpp"
#include <fstream>
#include <time.h>
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
		for (int i=0;i<100000;i++)
		{
			ev.current_pos=1;
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
	ev.current_pos++;
	yt::Parser::CreateBasicTypeObject cto(&ev);
	cto.execute();
	ev.stack_block.debug();
}
int main()
{
	try
	{
		create_basic_object_test();
		std::cin.get();
		return 0;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}

