#include "../HPP/SymbolTable.hpp"
using namespace Simcc;
using namespace Context;
std::list<std::unordered_map<Lexer::TId*, _SValue>> Simcc::Context::id_symbol_table(1);
std::unordered_map<Lexer::TId*, size_t> Simcc::Context::case_map;


std::ostream & Simcc::Context::operator<<(std::ostream & os, _SValue sv)
{
	std::cout << "OK" << sv.type->to_string() << "EN";
	os << sv.type->to_string();
	return os;
}

void Simcc::Context::print_id_table()
{
	std::string space;
	std::cout << '\n' + std::string(30, '-') << "print_id_table" + std::string(30, '-') << std::endl;
	for (auto &p1 : id_symbol_table)
	{
		for (auto & p2 : p1)
		{ 
			std::cout << space<<p2.first->to_string()<<p2.second<<std::endl;
		}
	}
	std::cout << '\n'+std::string(30, '-') << "print_id_table"+ std::string(30, '-') << std::endl;
}

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
	print_id_table();
	throw std::runtime_error("no find "+id_name->to_string()+" id");
}

void Simcc::Context::insert_id_info(Lexer::TId * id, Type * t)
{
	id_symbol_table.front().insert({ id, { t } });
}
