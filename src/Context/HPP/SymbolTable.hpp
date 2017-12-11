#pragma once
#include <iostream>
#include <list>
#include "Type.hpp"
#include "../../Lexer/HPP/Id.hpp"
namespace Simcc
{
	namespace Context
	{
		struct _SValue
		{
			Type *type;
		};
		extern std::list<std::unordered_map<Lexer::TId*, _SValue>> id_symbol_table;
		void new_block();
		void end_block();
		_SValue& find_id_info(Lexer::TId *id_name);
		void insert_id_info(Lexer::TId *id, Type *t);
	}
}