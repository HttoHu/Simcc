#include "..\Lexer\HPP\Lexer.hpp"
#include "..\Runtime\HPP\Object.hpp"
#include <fstream>
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
		std::string str = get_file_content("Text.txt");
		yt::Lexer::Lexer lex(str);
		lex.init_token_stream();
		std::cout << "parse completed.";
		lex.debug();
	}
	catch (const std::exception & e)
	{
		std::cout << e.what();
	}
	std::cin.get();
	return 0;
}
int object_test()

