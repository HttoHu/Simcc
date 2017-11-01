#pragma once
#include "Stmt.hpp"
#include "Environment.hpp"
#include "Block.hpp"
#include "../../Runtime/HPP/IdTypeTable.hpp"
namespace Simcc
{
	namespace Parser
	{
		//ʵ��
		class Param
		{
		public:
			Param(Environment *env);
			std::vector<Simcc::Runtime::ObjectBase*>& get_list();
			~Param();
		private:
			std::vector<Lexer::Token* > param_list;
			std::vector<Simcc::Runtime::ObjectBase*> obj_list;
			Environment *environment;
		};
		//�β�
		class Argument
		{
		public:
			Argument(Environment *env);
			void CreateVariable(Param &param);
		private:
			Environment *environment;
			std::vector<std::pair<Lexer::Token*, Lexer::Token*>> arg_list;
		};
		class Function
		{
		public:
			Function(Environment *env);
			Runtime::ObjectBase* execute(Param *param);
		private:
			size_t type;
			Environment *environment;
			Block *funcBlock;
			Argument * args;
		};

	}
}