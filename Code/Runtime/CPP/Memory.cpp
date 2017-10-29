#include "..\HPP\Memory.hpp"
using namespace yt::Runtime;
void yt::Runtime::Stack::newBlock()
{
	stack_memory.push_front(std::unordered_map<Lexer::Token*, ObjectBase*>());
}
void yt::Runtime::Stack::endBlock()
{
	for (const auto & a : stack_memory.front())
	{
		delete a.second;
	}
	stack_memory.pop_front();
}
ObjectBase * yt::Runtime::Stack::find_variable(yt::Lexer::Token*tok )
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
	throw std::runtime_error(tok->to_string()+"unknow variable");
}
void yt::Runtime::Stack::push(Lexer::Token*vname, ObjectBase *obj)
{
	stack_memory.front().insert({ vname,obj });
}

void yt::Runtime::Stack::debug()
{
	for (auto & a : stack_memory)
	{
		for (auto & b : a)
		{
			std::cout << "Variable name:" << b.first->to_string() << "\t\t value:" << b.second->to_string() << std::endl;
		}
	}
}