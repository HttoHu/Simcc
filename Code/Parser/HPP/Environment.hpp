#pragma once
#include "../../Lexer/HPP/Lexer.hpp"
#include "../../Runtime/HPP/Memory.hpp"
namespace yt
{
	namespace Parser
	{
		// �������ʱ��Ҫ�����ɵ�����. 
		class Environment
		{
		public:
			Environment(TokenStream* ts):token_stream(ts) {}
			yt::Runtime::Stack stack_block;
			TokenStream* token_stream;
			size_t current_pos=0;
			size_t current_line=1;
			//===========
			Lexer::Token* this_token()
			{
				return token_stream->operator[](current_pos);
			}
			bool match(Lexer::Tag t)
			{
				if (this_token()->get_tag()== t)
					return true;
				else
					return false;
			}
		};
	}
}