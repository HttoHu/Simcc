#pragma once
#include <iostream>
namespace Simcc
{
	namespace StackBlock
	{
		void check();
		void new_block();
		void end_block();
		char *find(size_t pos);
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
		size_t push_temp(const T&t)
		{
			char* d = (char*)&t;
			if (tp_pos > 200)
				tp_pos == 0;
			for (int i = 0; i <sizeof(T); i++)
				mem[tp_pos++] = d[i];
			return pc - sizeof(T);
		}
		size_t push_temp(const char *);
		void push(const char *);
		//=============== variables==========================
		extern char *mem;
		extern int length;
		extern int pc;
		extern unsigned char tp_pos;
		extern int pos_stack[20];
		extern int pos_stack_index;
	}
}
