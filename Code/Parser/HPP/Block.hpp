#pragma once
#include "Environment.hpp"
#include "Expression.hpp"
#include "CreateObject.hpp"
#include "Single.hpp"
#include "Loop.hpp"
namespace Simcc
{
	namespace Parser
	{
		class Block
		{
		public:
			class Return :public Stmt
			{
			public:
				Return(Environment *env) {
					env->match(Lexer::TReturn);
					if (env->match_noexcept(Lexer::EndStmt))
					{
						env->current_pos++;
						expr = nullptr;
					}
					expr = new Expression(env);
				}
				void execute()override {
					throw expr->GetResult();
				}
			private:
				Expression *expr;
			};
			class Break :public Stmt
			{
			public:
				Break(Environment *env) {
					env->match(Lexer::TBreak);
					env->match(Lexer::EndStmt);
				}
				void execute()override {
					throw (char)1;
				}
			private:
			};
			class Continue :public Stmt
			{
			public:
				Continue(Environment *env) {
					env->match(Lexer::TContinue);
					env->match(Lexer::EndStmt);
				}
				void execute()override {
					throw (char)2;
				}
			private:
			};
			Block(Environment *env);
			void execute()
			{
				index = 0;
				for (const auto & a : stmts)
				{
					a->execute();
				}
			}
			void break_block()
			{
				index = stmts.size();
			}
			~Block() {
				for (auto &a : stmts)
					delete a;
			}
		private:
			std::deque<Stmt*> stmts;
			size_t index = 0;
			Environment *environment;
		};
	}
}