#pragma once
#include "../../Lexer/HPP/Id.hpp"
#include <unordered_map>
namespace Simcc
{
	namespace Runtime
	{
		class IdTypeTable
		{
		public:
			static std::unordered_map<Lexer::Token*, size_t> type_table;
			static size_t find_type(Lexer::Token* tok)
			{
				auto result=type_table.find(tok);
				if (result == type_table.end())
					throw std::runtime_error("no found type " + tok->to_string());
				return result->second;
			}
		private:
		};
	}
}