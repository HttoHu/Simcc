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
		//for (int i = 0; i < 100000; i++)
		//{
		ev.current_pos = 1;
		yt::Parser::Expression expr(&ev);
		//expr.CreateExpressionStack();
		//expr.Translate();
		expr.debug();
		std::cout << expr.GetResult()->to_string();
		//}
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
	ev.stack_block.newBlock();
	ev.current_pos = 1;
	yt::Parser::CreateBasicTypeObject cto(&ev);
	cto.execute();
	ev.current_pos++;
	//std::cout<<"\n\nend"<<ev.token_stream->operator[](ev.current_pos)->to_string();
	yt::Parser::CreateBasicTypeObject cto2(&ev);
	cto2.execute();
	ev.stack_block.debug();
	ev.stack_block.endBlock();
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
	std::cout << "\n";
	ev.stack_block.debug();
}
int main()
{
	/* Text.txt ÄÚÈÝ
	*
	int a=23;
	int b=2*a;
	*/
	try
	{
		create_basic_object_test();
		std::cin.get();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	Sleep(1000000);
	return 0;
}

