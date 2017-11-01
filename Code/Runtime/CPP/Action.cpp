#include "..\HPP\Action.hpp"
using namespace Simcc::Parser;
Simcc::Runtime::Action::Action()
{
	switch (Environment::this_token()->get_tag())
	{
	case Lexer::PP:
		action_type = FP;
		Environment::current_pos++;
		content = Environment::this_token();
		return;
	case Lexer::MM:
		action_type = FM;
		Environment::current_pos++;
		content = Environment::this_token();
		return;
	case Lexer::Id:
		content = Environment::this_token();
		Environment::current_pos++;
		switch (Environment::this_token()->get_tag())
		{
		case Lexer::Lk:
			action_type = CALL;
			param = new Parser::Param();
			return;
		case Lexer::PP:
			action_type = BP;
			return;
		case Lexer::MM:
			action_type = BM;
			return;
		default:
			action_type = ID;
			return;
		}
	default:
		content = Environment::this_token();
		action_type = Action::CS;
		return;
	}
}