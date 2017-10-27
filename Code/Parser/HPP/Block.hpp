#pragma once
#include "Environment.hpp"
#include "Expression.hpp"
#include "CreateObject.hpp"
#include "Single.hpp"
#include "Loop.hpp"
namespace yt
{
	namespace Parser
	{
		class Block
		{
		public:
			Block(Environment *env);
			void execute()
			{
				index = 0;
				//environment->stack_block.newBlock();
				for (const auto & a:stmts)
				{
					a->execute();
				}
				//environment->stack_block.endBlock();
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