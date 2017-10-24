#pragma once
#include "Stmt.hpp"
#include "Environment.hpp"
#include "Expression.hpp"
namespace yt
{
	namespace Parser
	{
		class Assign :public Stmt
		{
		public:
			Assign(Environment *env) :environment(env){}
			void execute()override
			{
				Lexer::Token *id = next_token();
				match(next_token()->get_tag());
				Expression expr(environment);
				*environment->stack_block.find_variable(id) = *expr.GetResult();
			}
			Lexer::Token* next_token();
			bool match(Lexer::Tag t);
		private:
			Environment *environment;

		};
	}
}