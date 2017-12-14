#pragma once
#include <string>
#include "../../Stmts/HPP/Stmts.hpp"
namespace Simcc
{
	namespace Environment
	{
		extern std::vector<Simcc::Stmt*> stmt_stream;
		extern std::vector<Lexer::Token*> token_stream;
		extern size_t token_stream_index;
		Lexer::Token *this_token();
		void next_token();
		void match(Lexer::Tag);
		bool expect(Lexer::Tag);
	}
}