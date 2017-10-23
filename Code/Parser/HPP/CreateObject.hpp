#pragma once
#include "Expression.hpp"
#include "Stmt.hpp"
namespace yt
{
	namespace Parser
	{
		class CreateBasicTypeObject:public Stmt
		{
		public:
			CreateBasicTypeObject(Environment *env) :environment(env) {}
			void execute()override;
			void CreateObject();
			Lexer::Token* next_token();
			bool match(Lexer::Tag t);
		private:
			Lexer::Tag t;
			Environment *environment;
		};
	}
}