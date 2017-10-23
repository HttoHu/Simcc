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
			size_t current_pos;
		};
	}
}