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
			Assign() 
			{
				id_name = Environment::this_token();
				Environment::current_pos++;
				Environment::match(Lexer::Assign);
				expr = new Expression();
				Environment::match(Lexer::EndStmt);
			}
			void execute()override
			{
				auto result = expr->GetResult();
				*Environment::stack_block.find_variable(id_name) = *result;
				delete result;
			}
			~Assign() { delete expr; }
		private:
			Expression *expr;
			Lexer::Token *id_name;
		};
		class Single :public Stmt
		{
		public:
			Single()
			{
				expr = new Expression();
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
			Expression *expr;
		};
	}
}