#include "../HPP/If.hpp"
using namespace yt::Parser;
IfBlock::IfBlock(Environment *env):environment(env)
{
	environment->current_pos++;
	bool isSingle = !(env->this_token()->get_tag() == Lexer::Tag::BlockBegin);
	while (isSingle)
	{
		switch (env->this_token()->get_tag())
		{
		case Lexer::Tag::Endl:
			environment->current_pos++;
			break;
		case Lexer::Tag::TIf:
			stmts.push_back(new yt::Parser::If(environment));
			environment->current_pos++;
			return;
		case Lexer::Tag::SBool:
		case  Lexer::Tag::SInt:
		case  Lexer::Tag::SDouble:
		case  Lexer::Tag::SString:
		case  Lexer::Tag::SChar:
		case  Lexer::Tag::SLong:
			stmts.push_back(new CreateBasicTypeObject(environment));
			environment->current_pos++;
			return;
		case Lexer::Tag::MM:
		case Lexer::Tag::PP:
		case Lexer::Tag::Id:
			stmts.push_back(new Single(environment));
			return;
		default:
			throw std::runtime_error("\n" + environment->this_token()->to_string() + "runtime_error13");
		}
	}
	environment->current_pos++;
	while (!isSingle)
	{
		if (environment->current_pos >= environment->token_stream->size())
			throw std::runtime_error("runtime_error15");
		switch (env->this_token()->get_tag())
		{
		case Lexer::Tag::BlockEnd:
			environment->current_pos++;
			return;
		case Lexer::Tag::Endl:
			environment->current_pos++;
			continue;
		case Lexer::Tag::TIf:
			stmts.push_back(new yt::Parser::If(environment));
			break;
		case Lexer::Tag::SBool:
		case  Lexer::Tag::SInt:
		case  Lexer::Tag::SDouble:
		case  Lexer::Tag::SString:
		case  Lexer::Tag::SChar:
		case  Lexer::Tag::SLong:
			stmts.push_back(new CreateBasicTypeObject(environment));
			continue;
		case Lexer::Tag::MM:
		case Lexer::Tag::PP:
		case Lexer::Tag::Id:
			stmts.push_back(new Single(environment));
			continue;
		default:
			throw std::runtime_error("\n" + environment->this_token()->to_string() + "runtime_error14");
		}
	}
}