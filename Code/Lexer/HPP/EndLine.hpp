#pragma once
#include "Token.hpp"
namespace yt
{
	namespace Lexer
	{
		class EndLine:public Token
		{
		public:
			EndLine():Token(Tag::Endl)
			{
				static size_t currentLineNo = 1;
				line_no = currentLineNo++;
			}
			std::string to_string()const override
			{
				return "\n<Line:" + std::to_string(line_no) + ">";
			}
		private:
			size_t line_no;
		};
	}
}