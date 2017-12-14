#include "../HPP/Environment.hpp"
using namespace Simcc;
using namespace Simcc::Environment;
std::vector<Simcc::Stmt*> Simcc::Environment::stmt_stream;
std::vector<Simcc::Lexer::Token*> Simcc::Environment::token_stream;
size_t Simcc::Environment::token_stream_index=0;

Lexer::Token * Simcc::Environment::this_token()
{
	return token_stream[token_stream_index];
}

void Simcc::Environment::next_token()
{
	token_stream_index++;
}

void Simcc::Environment::match(Lexer::Tag t)
{
	if (this_token()->get_tag() == t)
	{
		token_stream_index++;
		return;
	}
	else if (this_token()->get_tag() == Lexer::Endl)
	{
		token_stream_index++;
		match(t);
	}
	else
		throw std::runtime_error("hey damn it .void Simcc::Environment::match ");
}

bool Simcc::Environment::expect(Lexer::Tag t)
{
	if (this_token()->get_tag() == t)
	{
		return true;
	}
	else if (this_token()->get_tag() == Lexer::Endl) {
		token_stream_index++;
		return expect(t);
	}
	return false;
}
