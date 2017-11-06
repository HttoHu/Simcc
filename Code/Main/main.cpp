#include "../Runtime/HPP/Object.hpp"
#include <fstream>
using namespace Simcc;
std::string get_file_content(const std::string & filename)
{
	using namespace std;
	ifstream ifs(filename);
	std::string file_content((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
	return file_content;
}
int main()
{
	Lexer::Lexer *lex = new Lexer::Lexer(get_file_content("Text.txt"));
	lex->init_token_stream();
	Environment::token_stream = &lex->token_stream;
	for (int i = 0; i < 10000000; i++)
	{
		Runtime::Basic bc(i);
	}
	std::cout << Environment::stack_block->pc;
	std::cout << *(int*)Environment::stack_block->find(sizeof(int)*10000);
	std::cin.get();
}