#pragma once
#include "Token.hpp"
namespace yt
{
	namespace Lexer
	{
		class TId :public Token
		{
		public:
			TId(const std::string & str) :Token(Tag::Id),id_name(str){}
			virtual std::string to_string()const override
			{
				return "<id:" + id_name + ">";
			}
		private:
			std::string id_name;
		};
	}
}