#include "..\HPP\If.hpp"
#include "../HPP/Block.hpp"
using namespace Simcc::Parser;
If::If(Simcc::Parser::Environment *env) :environment(env)
{
	environment->match(Lexer::TIf);
	environment->match(Lexer::Lk);
	// ���ڱ��ʽ���ܻ�ʶ��if�е� )��������Ҳ������(ʹ�ñ��ʽƽ��.
	auto cond = new Expression(env);
	environment->match(Lexer::Rk);
	block.push_back({ cond,new Block(env) });
	while (true)
	{
		if (environment->match_noexcept(Lexer::TElif))
		{
			environment->current_pos++;
			environment->match(Lexer::Lk);
			environment->current_pos--;
			auto cond = new Expression(env);
			environment->current_pos--;
			environment->match(Lexer::Rk);
			block.push_back({ cond,new Block(env) });
			continue;
		}
		else if (environment->match_noexcept(Lexer::TElse))
		{
			std::cout << "SHIT2" << std::endl;
			environment->current_pos++;
			Else = new Block(env);
			return;
		}
		return;
	}

}


void Simcc::Parser::If::execute()
{
	for (auto & a : block)
	{
		if (a.first->GetResult()->to_bool())
		{
			a.second->execute();
			return;
		}

	}
	if (Else != nullptr)
		Else->execute();
}

Simcc::Parser::If::~If() {
	for (auto &a : block)
	{
		delete a.first;
		delete a.second;
	}
	if (Else != nullptr)
		delete Else;
}
