#pragma once
#include "Stmt.hpp"
#include "Environment.hpp"
#include "../../Runtime/HPP/Object.hpp"
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
			Param(Environment *env) :environment(env)
			{
				environment->match(Lexer::Lk);
				while (1)
				{
					switch (environment->this_token()->get_tag())
					{
					case Lexer::Id:
					case Lexer::TLiteralChar:
					case Lexer::TLiteralDouble:
					case Lexer::TLiteralLong:
					case Lexer::TLiteralInt:
					case Lexer::TLiteralString:
					case Lexer::True:
					case Lexer::False:
						param_list.push_back(environment->this_token());
						break;
					default:
						return;
					}
					if (environment->match_noexcept(Lexer::Comma))
						continue;
					else
						break;
				}
				environment->match(Lexer::Rk);
			}
			std::vector<Simcc::Runtime::ObjectBase*>& get_list()
			{
				for (auto & a : param_list)
				{
					switch (a->get_tag())
					{
					case Lexer::Id:
						obj_list.push_back(new Simcc::Runtime::ObjectBase(*environment->stack_block.find_variable(a)));
						break;
					case Lexer::TLiteralInt:
						obj_list.push_back(new Simcc::Runtime::ObjectBase(*(int*)a->get_value()));
						break;
					case Lexer::TLiteralChar:
						obj_list.push_back(new Simcc::Runtime::ObjectBase(*(char*)a->get_value()));
						break;
					case Lexer::TLiteralLong:
						obj_list.push_back(new Simcc::Runtime::ObjectBase(*(int64_t*)a->get_value()));
						break;
					case Lexer::TLiteralDouble:
						obj_list.push_back(new Simcc::Runtime::ObjectBase(*(double*)a->get_value()));
						break;
					case Lexer::TLiteralString:
						obj_list.push_back(new Simcc::Runtime::ObjectBase(*(std::string*)a->get_value()));
						break;
					default:
						throw std::runtime_error("RuntimeError");
						break;
					}
				}
			}
			~Param()
			{
				for (auto & a : obj_list)
					delete a;
			}

		private:
			std::vector<Lexer::Token* > param_list;
			std::vector<Simcc::Runtime::ObjectBase*> obj_list;
			Environment *environment;
		};
		//形参
		class Argument
		{
		public:
			Argument(Environment *env) :environment(env) {
				environment->match(Lexer::Lk);
				while (1)
				{
					std::pair<Lexer::Token*, Lexer::Token*> tmp;
					switch (environment->this_token()->get_tag())
					{
					case Lexer::SInt:
					case Lexer::SDouble:
					case Lexer::SLong:
					case Lexer::SChar:
					case Lexer::SString:
					case Lexer::SBool:
						tmp.first = environment->this_token();
						break;
					default:
						return;
					}
					environment->current_pos++;
					auto id_name = environment->this_token();
					environment->match(Lexer::Id);
					tmp.second = environment->this_token();
					arg_list.push_back(tmp);
					if (environment->match_noexcept(Lexer::Comma))
						continue;
					break;
				}
				environment->match(Lexer::Rk);
			}
			void CreateVariable(Param &param)
			{
				auto p_list = param.get_list();
				if (arg_list.size() != p_list.size())
					throw std::runtime_error("RUntimeError22");
				for (size_t i=0;i<p_list.size();i++)
				{
					environment->stack_block.push(arg_list[i].second, p_list[i]);
				}
			}
		private:
			Environment *environment;
			std::vector<std::pair<Lexer::Token*, Lexer::Token*>> arg_list;
		};
		class Function
		{
		public:
			Function(Environment *env) :environment(env) {
				type = Runtime::IdTypeTable::find_type(environment->this_token());
				environment->current_pos++;
				environment->match(Lexer::Id);
				args = new Argument(environment);
				funcBlock = new Block(environment);
			}
			Runtime::ObjectBase* execute(Param *param)
			{
				environment->stack_block.newBlock();
				args->CreateVariable(*param);
				try
				{
					funcBlock->execute();
				}
				catch (Runtime::ObjectBase* return_value)
				{
					environment->stack_block.endBlock();
					return return_value;
				}
				environment->stack_block.endBlock();
				return nullptr;
			}
		private:
			size_t type;
			Environment *environment;
			Block *funcBlock;
			Argument * args;
		};

	}
}