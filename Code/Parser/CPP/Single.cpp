#include "..\HPP\Single.hpp"
using namespace yt;
Lexer::Token * yt::Parser::Single::next_token()
{
	return environment->token_stream->operator[](environment->current_pos++);
}

bool yt::Parser::Single::match(Lexer::Tag t)
{
	if ((environment->token_stream)->operator[](environment->current_pos++)->get_tag() == t)
	{
		return true;
	}
	return false;
}

