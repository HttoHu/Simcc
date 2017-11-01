#pragma once
#include <string>

namespace Simcc
{
	namespace Error
	{
		class SyntaxError
		{
		public:
			enum ErrorType
			{
				UnkownToken,
			};
			SyntaxError(ErrorType et,size_t ln, const std::string & content) :error_type(et),line_no(ln), error_content(content) {}
			std::string what()const
			{
				return std::to_string(line_no) + ":" + error_content + "\n";
			}
			static SyntaxError unknown_token(const std::string & str)
			{
				return SyntaxError(UnkownToken, 0, str);
			}
		private:
			ErrorType error_type;
			size_t line_no;
			std::string error_content;
		};
	}
}