#pragma once
#include "Environment.hpp"
#include "Expression.hpp"
#include "CreateObject.hpp"
#include "Single.hpp"
namespace yt
{
	namespace Parser
	{
		class If;
		class IfBlock
		{
		public:
			IfBlock(Environment *env);
			void execute()
			{
				//environment->stack_block.newBlock();
				for (; index < stmts.size(); index++)
				{
					stmts[index]->execute();
				}
				//environment->stack_block.endBlock();
			}
			void break_block()
			{
				index = stmts.size();
			}
		private:
			std::deque<Stmt*> stmts;
			size_t index = 0;
			Environment *environment;
		};
		class If :public Stmt
		{
		public:
			If(Environment *env) :environment(env)
			{
				environment->match(Lexer::TIf);
				environment->current_pos++;
				environment->match(Lexer::Lk);
				condition = new Expression(env);
				environment->match(Lexer::Rk);
				block = new IfBlock(env);
			}
			void execute()override
			{
				auto a = condition->GetResult();
				if (a->to_bool())
					block->execute();
				delete a;
			}
		private:
			Expression *condition;
			Environment *environment;
			IfBlock *block;
		};
	}
}