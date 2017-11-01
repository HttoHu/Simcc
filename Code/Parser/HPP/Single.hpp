#pragma once
#include "Stmt.hpp"
#include "Environment.hpp"
#include "Expression.hpp"
namespace Simcc
{
	namespace Parser
	{
		class Assign :public Stmt
		{
		public:
			Assign(Environment *env) :environment(env)
			{
				id_name = env->this_token();
				env->current_pos++;
				env->match(Lexer::Assign);
				expr = new Expression(env);
				env->match(Lexer::EndStmt);
			}
			void execute()override
			{
				auto result = expr->GetResult();
				*environment->stack_block.find_variable(id_name) = *result;
				delete result;
			}
			~Assign() { delete expr; }
		private:
			Environment *environment;
			Expression *expr;
			Lexer::Token *id_name;
		};
		class Single :public Stmt
		{
		public:
			Single(Environment *env) :environment(env)
			{
				expr = new Expression(env);
				match(Lexer::EndStmt);
			}
			void execute()override
			{
				delete expr->GetResult();
			}
			Lexer::Token* next_token();
			bool match(Lexer::Tag t);
			~Single()
			{
				delete expr;
			}
		private:
			Environment *environment;
			Expression *expr;
		};
	}
}