#pragma once
#include "Object.hpp"
#include "../../Parser/HPP/Environment.hpp"
#include "../../Parser/HPP/Function.hpp"
namespace Simcc
{
	namespace Runtime
	{
		class Action
		{
		public:
			enum  ActionType
			{
				FP,FM,BP,BM,CALL,ID,
			};
			Action(Parser::Environment *env);
			ObjectBase* get_result()
			{
				switch (action_type)
				{
				case FP:
					ObjectBase *obj = environment->stack_block.find_variable(id);
					return &(++*obj);
				case BP:
					ObjectBase *obj = environment->stack_block.find_variable(id);
					return &(*obj++);
				case FM:
					ObjectBase *obj = environment->stack_block.find_variable(id);
					return &(--*obj);
				case BM:
					ObjectBase *obj = environment->stack_block.find_variable(id);
					return &(*obj--);
				case CALL:
					return nullptr;
				case ID:
					return environment->stack_block.find_variable(id);
				default:
					break;
				}
			}
		private:
			Parser::Environment *environment;
			ActionType action_type;
			Lexer::Token *id;
			Parser::Param *param=nullptr;
		};
	}
}