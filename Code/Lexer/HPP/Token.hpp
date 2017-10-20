#pragma once
// By 胡远韬 Yt Hu
#include <iostream>
#include <string>
#include <unordered_map>
namespace yt
{
	namespace Lexer
	{
		enum Tag
		{
			TLiteralInt, TLiteralLong, TLiteralDouble, TLiteralChar, TLiteralString,
			TWhile, TFor, TBreak, TContinue,
			TIf, TSwitch, TElse, TElif, TCase, TGoto,
			/*else if*/
			TClass, TNamespace, TPublic, TPrivate,
			TReturn,
			Symbol,
			Id,
			Assign, Ge, Gt, Le, Lt, Ne, Eq,
			Add, Sub, Mul, Div,
			True, False,
			TTag,
			MemberPoint,
			Place, //::
			And, Or, // && ,||
			Lk, Rk,// ( and )
			BlockBegin, BlockEnd, // { }
			LSB, RSB,// [ ]
			Comma,// ,
			EndStmt,
		};
		std::unordered_map<std::string, Tag>& keyword_map();
		std::unordered_map<std::string, Tag>& symbol_map();
		class Token
		{
		public:
			Token(Tag t) :tag(t) {}
			virtual std::string to_string()const
			{
				switch (tag)
				{
				case Assign:
					return "< = >";
				case Eq:
					return "< == >";
				case Ne:
					return "< != >";
				case Ge:
					return "< >= >";
				case Gt:
					return "< > >";
				case Le:
					return "< <= >";
				case Lt:
					return "< < >";
				case yt::Lexer::TLiteralInt:
					return "<tint>";
				case yt::Lexer::TLiteralLong:
					return "<tlong>";
				case yt::Lexer::TLiteralDouble:
					return "<tdouble>";
				case yt::Lexer::TLiteralChar:
					return "<tchar>";
				case yt::Lexer::TLiteralString:
					return "<tstring>";
				case yt::Lexer::TWhile:
					return "<while>";
				case yt::Lexer::TIf:
					return "<if>";
				case yt::Lexer::TFor:
					return "<for>";
				case yt::Lexer::TSwitch:
					return "<switch>";
				case yt::Lexer::TClass:
					return "<class>";
				case yt::Lexer::TNamespace:
					return "<namespace>";
				case yt::Lexer::TReturn:
					return "<return>";
				case yt::Lexer::Symbol:
					return "<symbol>";
				case yt::Lexer::Add:
					return "<+>";
				case yt::Lexer::Sub:
					return "<->";
				case yt::Lexer::Mul:
					return "<*>";
				case yt::Lexer::Div:
					return "</>";
				case yt::Lexer::And:
					return "<&&>";
				case yt::Lexer::Or:
					return "<||>";
				case yt::Lexer::Lk:
					return "<(>";
				case yt::Lexer::Rk:
					return "<)>";
				case yt::Lexer::BlockBegin:
					return "<{>";
				case yt::Lexer::BlockEnd:
					return "<}>";
				case yt::Lexer::LSB:
					return "<[>";
				case yt::Lexer::RSB:
					return "<]>";
				case yt::Lexer::MemberPoint:
					return "<.>";
				case yt::Lexer::Comma:
					return "<;>";
				default:
					break;
				}
			}
			virtual void* get_value()
			{
				return nullptr;
			}
			virtual const void* const get_value()const
			{
				return nullptr;
			}
			Tag get_tag()const { return tag; }
			virtual ~Token() {}
		private:
			Tag tag;
		};
	}
}