#pragma once
#include "Block.hpp"
#include "If.hpp"
namespace yt
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
	}
}