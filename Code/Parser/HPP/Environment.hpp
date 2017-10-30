#pragma once
#include "../../Lexer/HPP/Lexer.hpp"
#include "../../Runtime/HPP/Memory.hpp"
namespace yt
{
	namespace Parser
	{
		// 储存编译时需要的生成的数据. 
		class Environment
		{
		public:
			Environment(TokenStream* ts) :token_stream(ts) {}
			yt::Runtime::Stack stack_block;
			TokenStream* token_stream;
			size_t current_pos = 0;
			size_t current_line = 1;
			//===========
			Lexer::Token* this_token()
			{
				return token_stream->operator[](current_pos);
			}
			void match(Lexer::Tag t)
			{
				if (this_token()->get_tag() == t)
				{
					current_pos++;
					return;
				}
				else if (this_token()->get_tag() == Lexer::Endl)
				{
					current_pos++;
					match(t);
				}
				else
					throw std::runtime_error(this_token()->to_string() + "unexpected erorr!");
			}
			bool match_noexcept(Lexer::Tag t)
			{
				if (this_token()->get_tag() == t)
				{
					return true;
				}
				else if (this_token()->get_tag() == Lexer::Endl) {
					current_pos++;
					return match_noexcept(t);
				}
				return false;
			}
		};
	}
}