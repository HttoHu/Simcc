#pragma once
#include "Block.hpp"
#include "If.hpp"
#include "Single.hpp"
namespace Simcc
{
	namespace Parser
	{

		class Block;
		class While :public Stmt
		{
		public:
			While(Environment *env);
			void execute()override;
			~While();
		private:
			Expression *condition;
			Environment *environment;
			Block *block;
		};
		class For:public Stmt
		{
		public:
			For(Environment *env);
			void execute()override;
			~For();
		private:
			CreateBasicTypeObject *cbt;
			Expression *condition;
			Expression *step_action;
			Environment *environment;
			Block *block;
		};
	}
}