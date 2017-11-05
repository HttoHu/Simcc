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
			//ǰ128������ʱ�����Ĵ��
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