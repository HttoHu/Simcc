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
		// 先写在这里吧, 改一下估计大半代码就要改了. 改了以后估计能带来大幅度性能的提升. 等我将语法稍稍完善后再改.
		// 还好只要表达式改改就好了.
		class StackMemory
		{
		public:
			StackMemory()
			{
				mem = new char[length];
			}
			~StackMemory()
			{
				delete[]mem;
			}
			void check();
			void newBlock();
			void endBlock();
			char* find(size_t pos);
			template <typename T>
			void push(const T&t)
			{
				check();
				char* d = (char*)&t;
				for (int i = 0; i <sizeof(T); i++)
					mem[pc++] = d[i];
			}
			template <typename T>
			void push_temp(const T&t)
			{
				char* d = (char*)&t;
				if (tp_pos > 200)
					tp_pos == 0;
				for (int i = 0; i <sizeof(T); i++)
					mem[tp_pos++] = d[i];
			}
			void push_temp(const char *);
			void push(int a);
			void push(const char *);

		private:
			char *mem;
			int length = 512;
			//前128用做临时变量的存放
			int pc = 256;
			unsigned char tp_pos = 0;
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