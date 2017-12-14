#include "..\HPP\Statement.hpp"
#include "../../Context/HPP/Environment.hpp"
#include "../../Lexer/HPP/Lexer.hpp"
#include "../HPP/Expression.hpp"
using namespace Simcc;
void Simcc::Parser::trans_statement()
{
	bool ndeduce= false;
	Lexer::Token *ftoken = Environment::this_token();
	if (ftoken->get_tag() == Lexer::SVAR)
	{
		ndeduce = true;
	}
s:	Environment::next_token();
	Lexer::Token *var_name = Environment::this_token();
	Environment::next_token();
	Lexer::Operator::check(Environment::this_token(),Lexer::Assign);
	Environment::next_token();
	auto v = Simcc::Expression::expr();
	if (ndeduce)
	{ 
		Environment::stmt_stream.push_back(new CreateVar(var_name, v));
	}
	else
	{
		Context::Type *t = nullptr;
		switch (ftoken->get_tag())
		{
		case Lexer::SInt:
			t = Context::Type::find_type("int");
			break;
		case Lexer::SBool:
			t = Context::Type::find_type("bool");
			break;
		case Lexer::SString:
			t = Context::Type::find_type("string");
			break;
		case Lexer::SChar:
			t = Context::Type::find_type("char");
			break;
		case Lexer::SDouble:
			t = Context::Type::find_type("double");
			break;
		case Lexer::SREF:
			t = Context::Type::find_type("ref");
			break;
		case Lexer::SLong:
			t = Context::Type::find_type("long");
			break;
		default:
			t = Context::find_id_info(static_cast<Lexer::TId*>(ftoken)).type;
			break;
		}
		Environment::stmt_stream.push_back(new CreateVar(t,var_name, v));
	}
	if (Environment::expect(Lexer::Comma))
		goto s;
	else
		Environment::match(Lexer::EndStmt);
}

void Simcc::Parser::statement_test()
{
	Lexer::lex_init("Lex.sic");
	Lexer::init_token_stream();
	Environment::token_stream_index++;
	Parser::trans_statement();
	for (const auto & a : Environment::stmt_stream)
	{
		std::cout << a->to_string() << std::endl;
	}
}
