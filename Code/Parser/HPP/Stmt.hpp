#pragma once
#include "../../Runtime/HPP/Memory.hpp"
namespace yt
{
	namespace Parser
	{
		class Stmt
		{
		public:
			virtual void execute() {};
			virtual ~Stmt() {};
		};
	}
}