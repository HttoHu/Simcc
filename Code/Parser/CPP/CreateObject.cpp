#include "..\HPP\CreateObject.hpp"
using namespace yt::Parser;
using namespace yt;
void yt::Parser::CreateBasicTypeObject::execute()
{
	t = next_token()->get_tag();
	CreateObject();
}

void yt::Parser::CreateBasicTypeObject::CreateObject()
{
	Lexer::Token *id = next_token();
	if (match(Lexer::Tag::Assign))
	{
		Expression value(environment);
		Runtime::ObjectBase* obj = nullptr;
		Runtime::ObjectBase* tmp = value.GetResult();
		switch (t)
		{
		case Lexer::Tag::SInt:
			obj = new Runtime::ObjectBase(tmp->to_int());
			environment->stack_block.push(id->to_string(), obj);
			break;
		case Lexer::Tag::SDouble:
			obj = new Runtime::ObjectBase(tmp->to_double());
			environment->stack_block.push(id->to_string(), obj);
			break;
		case Lexer::Tag::SString:
			obj = new Runtime::ObjectBase(tmp->to_string());
			environment->stack_block.push(id->to_string(), obj);
			break;
		case Lexer::Tag::SChar:
			obj = new Runtime::ObjectBase(tmp->get_value<char>());
			environment->stack_block.push(id->to_string(), obj);
			break;
		default:
			throw std::runtime_error("runtime_error10");
			break;
		}
		if (match(Lexer::Tag::Comma))
		{
			CreateObject();
		}
		return;
	}
}

Lexer::Token * yt::Parser::CreateBasicTypeObject::next_token()
{
	return environment->token_stream->operator[](environment->current_pos++);
}

bool yt::Parser::CreateBasicTypeObject::match(Lexer::Tag t)
{
	if ((environment->token_stream)->operator[](environment->current_pos++)->get_tag() == t)
	{
		return true;
	}
	return false;
}