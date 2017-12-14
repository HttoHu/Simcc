#pragma once
#include "Id.hpp"
#include "Literal.hpp"
#include "EndLine.hpp"
#include <fstream>
#include <string>
#include <deque>
typedef std::vector<Simcc::Lexer::Token*> TokenStream;
namespace Simcc
{
	namespace Environment
	{
		extern TokenStream token_stream;
	}
	namespace Lexer
	{
		void read_string();
		void read_char();
		void read_number();
		void read_word();
		void read_symbol();
		void debug();
		void init_token_stream();
		void lex_init(const std::string file_name);
		//======================

		extern std::string content;
		extern size_t index;
	}
}
