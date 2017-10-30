#include "../HPP/Block.hpp"
using namespace yt::Parser;
Block::Block(Environment *env) :environment(env)
{
	environment->current_pos++;
	bool isSingle = !(env->this_token()->get_tag() == Lexer::Tag::BlockBegin);
	while (isSingle)
	{
		switch (env->this_token()->get_tag())
		{
		case Lexer::Tag::TBreak:
			stmts.push_back(new Break(environment));
			environment->current_pos++;
			return;
		case Lexer::Tag::TContinue:
			stmts.push_back(new Continue(environment));
			environment->current_pos++;
			return;
		case Lexer::Tag::Endl:
			environment->current_pos++;
			break;
		case Lexer::Tag::TWhile:
			stmts.push_back(new yt::Parser::While(environment));
			environment->current_pos++;
			return;
		case Lexer::Tag::TIf:
			stmts.push_back(new yt::Parser::If(environment));
			environment->current_pos++;
			return;
		case Lexer::Tag::TFor:
			stmts.push_back(new yt::Parser::For(environment));
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
			if(environment->token_stream->at(environment->current_pos+1)->get_tag()==Lexer::Assign)
				stmts.push_back(new Assign(environment));
			else
			{
				stmts.push_back(new Single(environment));
			}
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
		case Lexer::Tag::TBreak:
			stmts.push_back(new Break(environment));
			break;
		case Lexer::Tag::TContinue:
			stmts.push_back(new Continue(environment));
			break;
		case Lexer::Tag::BlockEnd:
			environment->current_pos++;
			return;
		case Lexer::Tag::Endl:
			environment->current_pos++;
			continue;
		case Lexer::Tag::TWhile:
			stmts.push_back(new yt::Parser::While(environment));
			break;
		case Lexer::Tag::TIf:
			stmts.push_back(new yt::Parser::If(environment));
			break;
		case Lexer::Tag::TFor:
			stmts.push_back(new yt::Parser::For(environment));
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
			if (environment->token_stream->at(environment->current_pos + 1)->get_tag() == Lexer::Assign)
				stmts.push_back(new Assign(environment));
			else
				stmts.push_back(new Single(environment));
			continue;
		default:
			throw std::runtime_error("\n" + environment->this_token()->to_string() + "runtime_error14");
		}
	}
}