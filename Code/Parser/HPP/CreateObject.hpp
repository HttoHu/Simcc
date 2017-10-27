#pragma once
#include "Expression.hpp"
#include "Stmt.hpp"
namespace yt
{
	namespace Parser
	{
		class CreateBasicTypeObject :public Stmt
		{
		public:
			CreateBasicTypeObject(Environment *env) :environment(env)
			{
				type = next_token();
				while (true)
				{
					Lexer::Token *tok = next_token();
					Lexer::Tag tag = next_token()->get_tag();
					Expression *expr = new Expression(environment);
					
					vtable.push_back({ tok,expr });
					if (tag != Lexer::Assign)
					{
						throw std::runtime_error("runtime_error14");
					}
					tag = next_token()->get_tag();
					if (tag == Lexer::Comma)
						continue;
					else if (tag == Lexer::EndStmt)
						return;
					else
					{ 
						std::cout << this_token()->to_string();
						throw std::runtime_error("runtime_error13");
					}
				}
			}
			void execute()override;
			Lexer::Token* next_token();
			Lexer::Token* this_token();
		private:
			Lexer::Token* type;
			Environment *environment;
			std::list < std::pair<Lexer::Token*, Expression*>> vtable;
		};
	}
}