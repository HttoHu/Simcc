#include "../HPP/Token.hpp"
using namespace Simcc::Lexer;

size_t Simcc::Lexer::operator_priority(CountSign cs)
{
	switch (cs)
	{
	case CountSign::SAdd:
	case CountSign::SSub:
	case CountSign::SMul:
	case CountSign::SDiv:
	case CountSign::Assign:
		return 8;
	case CountSign::Ne:
	case CountSign::Eq:
	case CountSign::Ge:
	case CountSign::Gt:
	case CountSign::Le:
	case CountSign::Lt:
		return 9;
	case CountSign::Sub:
	case CountSign::Add:
		return 10;
	case CountSign::Div:
	case CountSign::Mul:
		return 11;
	default:
		throw std::runtime_error("unknown operator!");
	}
}

bool Simcc::Lexer::is_single_variable_countsign(CountSign cs)
{
	switch (cs)
	{
	case Simcc::Lexer::Not:
	case Simcc::Lexer::MM:
	case Simcc::Lexer::PP:
		return true;
	default:
		return false;
	}
}

std::unordered_map<std::string, Tag>& Simcc::Lexer::keyword_map()
{
	static std::unordered_map<std::string, Tag> ret{
		{ "class",Tag::TClass },{ "namespace",Tag::TNamespace },{ "public",Tag::TPublic },{ "private",Tag::TPrivate },
		{ "true",Tag::True },{ "false",Tag::False },{"int",Tag::SInt},{"double",Tag::SDouble},{"long",Tag::SLong},
		{"char",Tag::SChar},{"string",Tag::SString},{"bool",Tag::SBool},
		{ "while",Tag::TWhile },{ "for",Tag::TFor },{ "continue",Tag::TContinue },{ "break",Tag::TBreak },
		{ "case",Tag::TCase },{ "break",Tag::TBreak },{ "goto",Tag::TBreak },
		{ "switch",Tag::TSwitch },{ "if",Tag::TIf },{ "else",Tag::TElse } ,{ "elif",Tag::TElif },
		{"return",Tag::TReturn},{"system",Tag::System},{"var",Tag::SVAR},
	};
	return ret;
}

std::unordered_map<std::string,CountSign>& Simcc::Lexer::symbol_map()
{
	static std::unordered_map<std::string, CountSign> ret{
		{"+=",CountSign::SAdd},{"-=",SSub},{"*=",SMul}, {"/=",SDiv},
		{ "+",CountSign::Add },{ "-",CountSign::Sub },{ "*",CountSign::Mul },{ "/",CountSign::Div },
		{ "&&",CountSign::And },{ "||",CountSign::Or },{ "=",CountSign::Assign },{ ">",CountSign::Gt },{ "<",CountSign::Lt },
		{ ">=",CountSign::Ge },{ "<=",CountSign::Le },{ "==",CountSign::Eq },{ "!=",CountSign::Ne },
		{"++",CountSign::PP},{"--",CountSign::MM},
	};
	return ret;
}

bool Simcc::Lexer::Operator::check(Token * tok, CountSign c)
{
	CountSign cs= *(CountSign*)tok->get_value();
	return !(c - cs);
}
