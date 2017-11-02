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
				FP,FM,BP,BM,CALL,ID,CS,
			};
			Action();
			Action(Lexer::Token* tok) :content(tok) 
			{
			}
			ObjectBase* get_object_result()
			{
				switch (action_type)
				{
				case FP:
				{
					Parser::Environment::stack_block.find_variable(content)->operator++();
					ObjectBase *obj = new ObjectBase(*Parser::Environment::stack_block.find_variable(content));
					return obj;
				}
				case BP:
				{
					ObjectBase *obj = new ObjectBase(*Parser::Environment::stack_block.find_variable(content));
					Parser::Environment::stack_block.find_variable(content)->operator++();
					return obj;
				}
				case FM:
				{
					Parser::Environment::stack_block.find_variable(content)->operator--();
					ObjectBase *obj = new ObjectBase(*Parser::Environment::stack_block.find_variable(content));
					return obj;
				}
				case BM:
				{
					ObjectBase *obj = new ObjectBase(*Parser::Environment::stack_block.find_variable(content));
					Parser::Environment::stack_block.find_variable(content)->operator--();
					return obj;
				}
				case CALL:
				{
					auto result = Parser::Function::function_table.find(Parser::Environment::this_token());
					if (result == Parser::Function::function_table.end())
					{
						throw std::runtime_error("function no found");
					}
					ObjectBase *obj = result->second->execute(param);
					return obj;
				}
				case ID:
					return new ObjectBase(*Parser::Environment::stack_block.find_variable(content));
				default:
					break;
				}
			}
			Lexer::Tag get_cs()
			{
				return content->get_tag();
			}
			Lexer::Token *content;
			ActionType action_type;
		private:
			Parser::Param *param=nullptr;
		};
	}
}