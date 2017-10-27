#include "..\HPP\If.hpp"
#include "../HPP/Block.hpp"
using namespace yt::Parser;
If::If(yt::Parser::Environment *env) :environment(env)
{
	environment->match(Lexer::TIf);
	environment->match(Lexer::Lk);
	environment->current_pos--;
	// ���ڱ��ʽ���ܻ�ʶ��if�е� )��������Ҳ������(ʹ�ñ��ʽƽ��.
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
