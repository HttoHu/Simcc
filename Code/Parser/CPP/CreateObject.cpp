#include "..\HPP\CreateObject.hpp"
using namespace Simcc::Parser;
using namespace Simcc;
void Simcc::Parser::CreateBasicTypeObject::execute()
{
	for (auto & a : vtable)
	{
		environment->stack_block.push(a.first, a.second->GetResult());
	}
}

Lexer::Token * Simcc::Parser::CreateBasicTypeObject::next_token()
{
	return environment->token_stream->operator[](environment->current_pos++);
}
Lexer::Token * Simcc::Parser::CreateBasicTypeObject::this_token()
{
	return environment->token_stream->operator[](environment->current_pos);
}
