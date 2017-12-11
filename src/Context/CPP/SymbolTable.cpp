#include "../HPP/SymbolTable.hpp"
using namespace Simcc;
using namespace Context;
std::list<std::unordered_map<Lexer::TId*, _SValue>> 
Simcc::Context::id_symbol_table(1);

void Simcc::Context::new_block()
{
	id_symbol_table.push_front(std::unordered_map<Lexer::TId*, _SValue>());
}
void Simcc::Context::end_block()
{
	id_symbol_table.pop_front();
}

_SValue & Simcc::Context::find_id_info(Lexer::TId * id_name)
{
	for (auto &a : id_symbol_table)
	{
		auto b = a.find(id_name);
		if (b != a.end())
			return b->second;
	}
	throw std::runtime_error("no find such id");
}

void Simcc::Context::insert_id_info(Lexer::TId * id, Type * t)
{
	id_symbol_table.front().insert({ id, { t } });
}
