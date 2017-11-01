#pragma once
#include <string>
#include <vector>
#include <map>
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
			StackMemory(size_t sz = 512) :length(512)
			{
				mem = new char[length];
			}
			void extend() {
				char *nmem = new char[length*TIMES];
				for (size_t i = 0; i < PC; i++)
				{
					nmem[i] = mem[i];
				}
				delete[]mem;
				mem = nmem;
				length *= TIMES;
			}
			void cnk()
			{
				if (PC >= length)
				{
					extend();
				}
			}
			template<typename T>
			void push_value(const T&t)
			{
				char *value = (char*)&t;
				size_t tlengh = sizeof(t);
				for (size_t i = 0; i < tlengh; i++)
				{
					mem[PC++]value[i];
				}
			}
			size_t size()const { 
				return length;
			}
		private:
			size_t PC=0;
			const double TIMES=1.7;
			char *mem;
			size_t length;
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