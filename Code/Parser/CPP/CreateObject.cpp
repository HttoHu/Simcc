#include "..\HPP\CreateObject.hpp"
using namespace yt::Parser;
using namespace yt;
void yt::Parser::CreateBasicTypeObject::execute()
{
	for (auto & a : vtable)
	{
		environment->stack_block.push(a.first->to_string(), a.second->GetResult());
	}
}

Lexer::Token * yt::Parser::CreateBasicTypeObject::next_token()
{
	return environment->token_stream->operator[](environment->current_pos++);
}
Lexer::Token * yt::Parser::CreateBasicTypeObject::this_token()
{
	return environment->token_stream->operator[](environment->current_pos);
}
