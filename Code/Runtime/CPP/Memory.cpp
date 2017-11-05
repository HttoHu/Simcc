#include "..\HPP\Memory.hpp"
using namespace Simcc::Runtime;
void Simcc::Runtime::Stack::newBlock()
{
	stack_memory.push_front(std::map<Lexer::Token*, ObjectBase*>());
}
void Simcc::Runtime::Stack::endBlock()
{
	for (const auto & a : stack_memory.front())
	{
		delete a.second;
	}
	stack_memory.pop_front();
}
ObjectBase * Simcc::Runtime::Stack::find_variable(Simcc::Lexer::Token*tok)
{
	//std::cout << "DDD" << *(std::string*)tok->get_value() << std::endl;
	auto current = stack_memory.begin();
	while (current != stack_memory.end())
	{
		auto result = current->find(tok);

		if (result != current->end())
		{
			return result->second;
		}
		current++;
	}
	throw std::runtime_error(tok->to_string() + "unknow variable");
}
void Simcc::Runtime::Stack::push(Lexer::Token*vname, ObjectBase *obj)
{
	stack_memory.front().insert({ vname,obj });
}

void Simcc::Runtime::Stack::debug()
{
	for (auto & a : stack_memory)
	{
		for (auto & b : a)
		{
			std::cout << "Variable name:" << b.first->to_string() << "\t\t value:" << b.second->to_string() << std::endl;
		}
	}
}

void Simcc::Runtime::StackMemory::check()
{
	if (pc >= length / 2)
	{
		std::cout << "RESIZE";
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

void Simcc::Runtime::StackMemory::push(int t)
{
	check();
	char* d = (char*)&t;
	for (int i = 0; i < sizeof(int); i++)
		mem[pc++] = d[i];
}

void Simcc::Runtime::StackMemory::push(const char *c_str)
{
	std::string str= c_str;
	check();
	char* d = (char*)&str;
	for (int i = 0; i < sizeof(str); i++)
		mem[pc++] = d[i];
}

