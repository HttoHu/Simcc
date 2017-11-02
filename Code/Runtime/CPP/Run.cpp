#include "..\HPP\Run.hpp"
#include <fstream>
std::string get_file_content(const std::string & filename)
{
	using namespace std;
	ifstream ifs(filename);
	std::string file_content((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
	return file_content;
}
void Simcc::Runtime::Init(const std::string & str)
{
	std::string content = get_file_content(str);
	Simcc::Lexer::Lexer lex(content);
	lex.init_token_stream();
}

void Simcc::Runtime::CreateFunctionTable()
{
	while (Parser::Environment::current_pos < Parser::Environment::token_stream->size())
		Parser::Function::function_table.insert({ nullptr,new Parser::Function() });
}

void Simcc::Runtime::Execute()
{
	
}
