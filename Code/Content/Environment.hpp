#pragma once
#include "../Lexer/HPP/Lexer.hpp"
#include "../Runtime/HPP/Memory.hpp"
namespace Simcc
{
	enum IdProperty
	{
		Variable,FunctionName,Type
	};
	class Environment
	{
	public:
		static Runtime::StackMemory *stack_block;
		static TokenStream *token_stream;
	private:
	};
}