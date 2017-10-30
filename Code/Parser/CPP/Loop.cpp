#include "../HPP/Loop.hpp"
#include "../HPP/Block.hpp"
using namespace yt::Parser;

yt::Parser::While::While(Environment * env) :environment(env)
{
	environment->match(Lexer::TWhile);
	environment->match(Lexer::Lk);
	condition = new Expression(env);
	environment->match(Lexer::Rk);
	block = new Block(env);
}

void yt::Parser::While::execute()
{
	auto a = condition->GetResult();
	while (a->to_bool())
	{
		try
		{
			block->execute();
			delete a;
			a = condition->GetResult();
		}
		catch (char ch)
		{
			switch (ch)
			{
			case 1:
				return;
			case 2:
				continue;
			default:
				break;
			}
		}

	}
}

yt::Parser::While::~While() {
	delete condition;
	delete block;
}

yt::Parser::For::For(Environment * env) :environment(env)
{
	environment->match(Lexer::TFor);
	environment->match(Lexer::Lk);
	if (environment->match_noexcept(Lexer::EndStmt))
		cbt = nullptr;
	else
	{
		cbt = new CreateBasicTypeObject(environment);
	}
	condition = new Expression(environment);
	environment->match(Lexer::EndStmt);
	if (environment->match_noexcept(Lexer::EndStmt))
	{
		environment->current_pos++;
		step_action = nullptr;
	}
	else
	{
		step_action = new Expression(environment);
	}

	environment->match(Lexer::Rk);
	block = new Block(env);

}

void yt::Parser::For::execute()
{
	if (cbt != nullptr)
		cbt->execute();
	if (step_action != nullptr)
	{
		auto a = condition->GetResult();
		while (a->to_bool())
		{
			block->execute();
			delete step_action->GetResult();
			delete a;
			a = condition->GetResult();
		}
	}
	else
	{
		auto a = condition->GetResult();
		while (a->to_bool())
		{
			block->execute();
			delete a;
			a = condition->GetResult();
		}
	}
}

yt::Parser::For::~For()
{
	if (step_action != nullptr)
		delete step_action;
	if (cbt != nullptr)
		delete cbt;
	delete condition;
}
