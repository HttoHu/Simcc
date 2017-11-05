#pragma once
#include <string>
#include <vector>
#include <map>
#include <stack>
#include "../../Lexer/HPP/Token.hpp"
#include "Object.hpp"
namespace Simcc
{
	namespace Runtime
	{
		// ��д�������, ��һ�¹��ƴ������Ҫ����. �����Ժ�����ܴ�����������ܵ�����. ���ҽ��﷨�������ƺ��ٸ�.
		// ����ֻҪ���ʽ�ĸľͺ���.
		class StackMemory
		{
		public:
			StackMemory()
			{
				mem = new char[length];
			}
			void check();
			void newBlock();
			void endBlock();
			ObjectBase* find_variable(Lexer::Token*);
			void push(Lexer::Token*, ObjectBase *obj,bool not_temp);
			void push(int a);
			void debug();
		private:
			char *mem;
			int length = 512;
			int pc = 0;
			int pos_stack[20]; 
			int pos_stack_index=0;
		};
		class Stack{
		public:
			Stack()
			{
				newBlock();
			}
			void newBlock();
			void endBlock();
			ObjectBase* find_variable(Lexer::Token* );
			void push(Lexer::Token* , ObjectBase *obj);
			void debug();
		private:
			std::list<std::map<Lexer::Token*,ObjectBase*>> stack_memory;
		};
	}
}