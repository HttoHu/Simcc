#include "../HPP/Id.hpp"
using namespace Simcc::Lexer;

TId * Simcc::Lexer::TId::find_id(const std::string & str)
{
	for (int i=id_table.size()-1;i>=0;i-- )
	{
		auto result = id_table[i].find(str);
		if (result == id_table[i].end())
			continue;
		return result->second;
	}
	return nullptr;
}

void Simcc::Lexer::TId::delete_id_table()
{
	for (auto & a : id_table)
		for (auto & b : a)
			delete b.second;
	id_table.clear();
}
