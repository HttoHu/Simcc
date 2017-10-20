#pragma once
#include "Id.hpp"
#include "Value.hpp"
#include <string>
#include <deque>
typedef std::deque<yt::Lexer::Token*> TokenStream;
namespace yt
{
	namespace Lexer
	{
		class Lexer
		{
		public:
			Lexer(const std::string & str):content(str){}
			void read_string();
			void read_char();
			void read_number();
			void read_word();
			void read_symbol();
			void debug();
			void init_token_stream();
			TokenStream token_stream;
			~Lexer()
			{
				for (auto & a : token_stream)
				{
					delete a;
				}
				token_stream.clear();
			}
		private:
			std::string content;
			size_t index=0;
		};
	}
}
