#pragma once
#include "../../Lexer/HPP/Lexer.hpp"
namespace yt
{
	namespace Parser
	{
		// �������ʱ��Ҫ�����ɵ�����. 
		class Environment
		{
		public:
			Environment(TokenStream* ts):token_stream(ts) {}

			TokenStream* token_stream;
			size_t current_pos;
		};
	}
}