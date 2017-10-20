#include "../HPP/Token.hpp"
using namespace yt::Lexer;
std::unordered_map<std::string, Tag>& yt::Lexer::keyword_map()
{
	static std::unordered_map<std::string, Tag> ret{
		{ "class",Tag::TClass },{ "namespace",Tag::TNamespace },{ "public",Tag::TPublic },{ "private",Tag::TPrivate },
		{ "true",Tag::True },{ "false",Tag::False },
		{ "while",Tag::TWhile },{ "for",Tag::TFor },{ "continue",Tag::TContinue },{ "break",Tag::TBreak },
		{ "case",Tag::TCase },{ "break",Tag::TBreak },{ "goto",Tag::TBreak },
		{ "switch",Tag::TSwitch },{ "if",Tag::TIf },{ "else",Tag::TElse } ,{ "elif",Tag::TElif },
	};
	return ret;
}

std::unordered_map<std::string, Tag>& yt::Lexer::symbol_map()
{
	static std::unordered_map<std::string, Tag> ret{
		{ "+",Tag::Add },{ "-",Tag::Sub },{ "*",Tag::Mul },{ "/",Tag::Div },
		{ "&&",Tag::And },{ "||",Tag::Or },{ "[",Tag::LSB },{ "]",Tag::RSB },
		{ "{",Tag::BlockBegin },{ "}",Tag::BlockEnd },{ "(",Tag::Lk },{ ")",Tag::Rk },
		{ "::",Tag::Place },{ "=",Tag::Assign },{ ">",Tag::Gt },{ "<",Tag::Lt },
		{ ">=",Tag::Ge },{ "<=",Tag::Le },{ "==",Tag::Eq },{ "!=",Tag::Ne },
	};
	return ret;
}