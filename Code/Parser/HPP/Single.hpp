#pragma once
#include "Stmt.hpp"
#include "Environment.hpp"
#include "Expression.hpp"
namespace yt
{
	namespace Parser
	{
		class Single :public Stmt
		{
		public:
			Single(Environment *env) :environment(env)
			{
				expr = new Expression(env);
				//std::cout << std::endl;
				//expr->debug();
				match(Lexer::EndStmt);
			}
			void execute()override
			{
				expr->GetResult();
			}
			Lexer::Token* next_token();
			bool match(Lexer::Tag t);
		private:
			Environment *environment;
			Expression *expr;
		};
	}
}