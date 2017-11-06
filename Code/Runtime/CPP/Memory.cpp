#include "../HPP/Memory.hpp"
void Simcc::Runtime::StackMemory::check()
{
	if (pc >= length / 2)
	{
		char* newMem = new char[length * 2];
		for (int i = 0; i < pc; i++)
			newMem[i] = mem[i];
		delete[] mem;
		mem = newMem;
		length *= 2;
	}
}

void Simcc::Runtime::StackMemory::newBlock()
{
	pos_stack[pos_stack_index++] = pc;
}

void Simcc::Runtime::StackMemory::endBlock()
{
	pc = pos_stack[pos_stack_index--];
}

char * Simcc::Runtime::StackMemory::find(size_t pos)
{
	return mem + pos;
}

void Simcc::Runtime::StackMemory::push_temp(const char *c_str)
{
	std::string str = c_str;
	char* d = (char*)&str;
	for (int i = 0; i <sizeof(std::string); i++)
		mem[tp_pos++] = d[i];
}

void Simcc::Runtime::StackMemory::push(const char *c_str)
{
	std::string str = c_str;
	check();
	char* d = (char*)&str;
	for (int i = 0; i < sizeof(str); i++)
		mem[pc++] = d[i];
}

