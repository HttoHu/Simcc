#pragma once
#include <iostream>
namespace Simcc
{
	namespace Runtime
	{
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
				for (int i = 0; i < sizeof(T); i++)
				{
					mem[pc++] = d[i];
				}
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
			void push(const char *);
			int pc = 256;
		private:
			char *mem;
			int length = 512;
			//前128用做临时变量的存放

			unsigned char tp_pos = 0;
			int pos_stack[20];
			int pos_stack_index = 0;
		};
	}
}