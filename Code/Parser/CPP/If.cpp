#include "..\HPP\If.hpp"
#include "../HPP/Block.hpp"
using namespace yt::Parser;
If::If(yt::Parser::Environment *env) :environment(env)
{
	environment->match(Lexer::TIf);
	environment->match(Lexer::Lk);
	environment->current_pos--;
	// 由于表达式可能会识别if中的 )所以我们也将加入(使得表达式平衡.
	condition = new Expression(env);
	environment->current_pos--;
	environment->match(Lexer::Rk);
	block = new Block(env);
}


void yt::Parser::If::execute()
{
	auto a = condition->GetResult();
	if (a->to_bool())
		block->execute();
	delete a;
}

yt::Parser::If::~If() {
	delete condition;
	delete block;
}
