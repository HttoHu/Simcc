#pragma once
#include "Stmt.hpp"
#include "Environment.hpp"
#include "Block.hpp"
#include "../../Runtime/HPP/IdTypeTable.hpp"
namespace Simcc
{
	namespace Parser
	{
		//实参
		class Param
		{
		public:
			Param(const std::vector<Simcc::Runtime::ObjectBase*> & ol) :obj_list(ol) {}
			Param();
			std::vector<Simcc::Runtime::ObjectBase*>& get_list();
			~Param();
		private:
			std::vector<Lexer::Token* > param_list;
			std::vector<Simcc::Runtime::ObjectBase*> obj_list;
		};
		//形参
		class Argument
		{
		public:
			Argument();
			void CreateVariable(Param &param);
		private:
			std::vector<std::pair<Lexer::Token*, Lexer::Token*>> arg_list;
		};
		class Function
		{
		public:
			static std::map<Lexer::Token*, Function*> function_table;
			Function();
			Runtime::ObjectBase* execute(Param *param);
			Runtime::ObjectBase* execute();
		private:
			size_t type;
			Block *funcBlock;
			Argument * args;
		};

	}
}