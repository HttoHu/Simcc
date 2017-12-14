#pragma once
#include <iostream>
#include <list>
#include "Type.hpp"
#include <vector>
#include "../../Lexer/HPP/Id.hpp"
namespace Simcc
{
	class Stmt;
	namespace Context
	{
		struct _SValue
		{
			Type *type;

		};
		std::ostream & operator<< (std::ostream &os, _SValue sv);

		extern std::list<std::unordered_map<Lexer::TId*, _SValue>> id_symbol_table;
		extern std::unordered_map<Lexer::TId*, size_t> case_map;
		void print_id_table();
		void new_block();
		void end_block();
		_SValue& find_id_info(Lexer::TId *id_name);
		void insert_id_info(Lexer::TId *id, Type *t);
	}
}