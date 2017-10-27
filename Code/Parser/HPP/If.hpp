#pragma once
#include "Environment.hpp"
#include "Expression.hpp"
#include "CreateObject.hpp"
#include "Single.hpp"
namespace yt
{
	namespace Parser
	{
		class Block;
		class If :public Stmt
		{
		public:
			If(Environment *env);
			void execute()override;
			~If();
		private:
			Expression *condition;
			Environment *environment;
			Block *block;
		};
	}
}