#include "..\HPP\Assign.hpp"
using namespace yt;
Lexer::Token * yt::Parser::Assign::next_token()
{
	return environment->token_stream->operator[](environment->current_pos++);
}

bool yt::Parser::Assign::match(Lexer::Tag t)
{
	if ((environment->token_stream)->operator[](environment->current_pos++)->get_tag() == t)
	{
		return true;
	}
	return false;
}
