#include "..\HPP\Action.hpp"

Simcc::Runtime::Action::Action(Parser::Environment * env):environment(env)
{
	switch (env->this_token()->get_tag())
	{
	case Lexer::PP:
		action_type = FP;
		env->current_pos++;
		id = env->this_token();
		return;
	case Lexer::MM:
		action_type = FM;
		env->current_pos++;
		id = env->this_token();
		return;
	case Lexer::Id:
		env->current_pos++;
		switch (env->this_token()->get_tag())
		{
		case Lexer::Lk:
			action_type = CALL;
			param = new Parser::Param(env);
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
		throw std::runtime_error("runtime_error23");
	}
}