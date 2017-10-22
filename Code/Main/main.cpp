#include "..\Lexer\HPP\Lexer.hpp"
#include "..\Runtime\HPP\Object.hpp"
#include "..\Parser\HPP\Environment.hpp"
#include "..\Parser\HPP\Expression.hpp"
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
		std::cout << "lexer completed.\n"<<"Time:"<< double(clock()-s)/CLK_TCK<<"s";
		//lex.debug();
	}
	catch (const std::exception & e)
	{
		std::cout << e.what();
	}
	std::cin.get();
	return 0;
}
int main()
{
	try
	{
		time_t s = clock();
		std::string str = get_file_content("Text.txt");
		yt::Lexer::Lexer lex(str);
		lex.init_token_stream();
		yt::Parser::Environment ev(&lex.token_stream);
		ev.current_pos++;
		yt::Parser::Expression expr(&ev);
		expr.CreateExpressionStack();
		expr.Translate();
		std::cout << "Result:" << expr.GetResult()->to_string() << std::endl;
		expr.debug();
		std::cout << "\ncompleted.\n" << "Time:" << double(clock() - s) / CLK_TCK << "s\n press any key to exit";
	}
	catch (const std::exception & e)
	{
		std::cout << e.what();
	}
	std::cin.get();
	return 0;
}

