#pragma once
#include <string>
#include <vector>
#include "../../Lexer/HPP/Token.hpp"
#include "Object.hpp"
namespace yt
{
	namespace Runtime
	{
		class Stack{
		public:
			Stack()
			{
				newBlock();
			}
			void newBlock();
			void endBlock();
			ObjectBase* find_variable(Lexer::Token* );
			void push(const std::string & vname, ObjectBase *obj);
			void debug();
		private:
			std::list<std::unordered_map<std::string,ObjectBase*>> stack_memory;
		};
	}
}