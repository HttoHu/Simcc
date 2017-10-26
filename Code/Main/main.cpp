#include "..\Parser\HPP\If.hpp"
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
void block_test()
{
	time_t s = clock();
	std::string str = get_file_content("Text.txt");
	yt::Lexer::Lexer lex(str);
	lex.init_token_stream();
	//lex.debug();
	yt::Parser::Environment ev(&lex.token_stream);
	yt::Parser::IfBlock block(&ev);
	block.execute();
	std::cout << "\n";
	ev.stack_block.debug();
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
		block_test();
		std::cin.get();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	Sleep(1000000);
	return 0;
}

