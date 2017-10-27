#include "..\Parser\HPP\If.hpp"
<<<<<<< HEAD
#include "../Parser/HPP/Block.hpp"
=======
>>>>>>> add58c8a2fa8ca203a69411286a9ed6d8c15d4e3
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
<<<<<<< HEAD

	std::string str = get_file_content("Text.txt");
	yt::Lexer::Lexer lex(str);
	lex.init_token_stream();
	lex.debug();
	yt::Parser::Environment ev(&lex.token_stream);
	yt::Parser::Block block(&ev);
	time_t s = clock();
	block.execute();
=======
	time_t s = clock();
	std::string str = get_file_content("Text.txt");
	yt::Lexer::Lexer lex(str);
	lex.init_token_stream();
	//lex.debug();
	yt::Parser::Environment ev(&lex.token_stream);
	yt::Parser::IfBlock block(&ev);
	block.execute();
	std::cout << "\n";
>>>>>>> add58c8a2fa8ca203a69411286a9ed6d8c15d4e3
	ev.stack_block.debug();
	std::cout << (double)(clock()-s)/CLK_TCK<<"\n";
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

