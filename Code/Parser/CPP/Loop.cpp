#include "../HPP/Loop.hpp"
#include "../HPP/Block.hpp"
using namespace yt::Parser;

yt::Parser::While::While(Environment * env):environment(env)
{
	environment->match(Lexer::TWhile);
	environment->match(Lexer::Lk);
	environment->current_pos--;
	condition = new Expression(env);
	environment->current_pos--;
	environment->match(Lexer::Rk);
	block = new Block(env);
}

void yt::Parser::While::execute()
{
	while (1)
	{
		auto a = condition->GetResult();
		if (a->to_bool())
			block->execute();
		else
		{
			delete a;
			return;
		}
		delete a;
	}
}

yt::Parser::While::~While() {
	delete condition;
	delete block;
}