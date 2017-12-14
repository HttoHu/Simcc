#pragma once
#include "../../Lexer/HPP/Lexer.hpp"
namespace Simcc
{
	namespace Action
	{
		enum ActionType
		{
			// ID 
			SINGLE,
			//++i ,--i 
			FPP,FMM,
			// i++, i--
			BPP,PMM,
			//!a ,-a,
			NOT,NE,
			//a[23]
			INDEX,
			//Memebrs
			MEMBER,
			LIT,
			COUNTSIGN,
		};
		class ActionBase
		{
		public:
			ActionBase(Lexer::Token *i, ActionType at) :content(i), action(at) {}
			ActionBase(Lexer::Token *i):content(i)
			{
				switch (content->get_tag())
				{
				case Lexer::Id:
					action = SINGLE;
					break;
				case Lexer::TOperator:
					action = COUNTSIGN;
					break;
				case Lexer::TLiteralChar:
				case Lexer::TLiteralDouble:
				case Lexer::TLiteralInt:
				case Lexer::TLiteralLong:
				case Lexer::TLiteralString:
				case Lexer::True:
				case Lexer::False:
					action = LIT;
					break;
				default:
					std::cerr << "God damage ! 12-11";
					abort();
				}
			}
			Lexer::CountSign try_get_count_sign() 
			{
				if (content->get_tag() != Lexer::TOperator)
					throw std::runtime_error("ActionBase - content must be a operator");
				return static_cast<Lexer::Operator*>(content)->count_sign;
			}
			Lexer::Tag get_tag()const { return content->get_tag(); }
			virtual ~ActionBase(){}
			virtual std::string trans()
			{
				return "";
			}
			virtual std::string to_string() 
			{
				std::string front_part= content->to_string();
				switch (action)
				{
				case Simcc::Action::SINGLE:
					return front_part;
				case Simcc::Action::FPP:
					return "++"+front_part;
				case Simcc::Action::FMM:
					return "--"+front_part;
				case Simcc::Action::BPP:
					return front_part+"++";
				case Simcc::Action::PMM:
					return front_part+"--";
				case Simcc::Action::NOT:
					return "!"+front_part;
				case Simcc::Action::NE:
					return "-"+front_part;
				default:
					//std::cerr << "<unknown action>";
					break;
				}
			}
			Lexer::Token *content;
			ActionType action;
		};
		class ActionIndex :public ActionBase
		{
		public:
			ActionIndex(Lexer::TId *i, Lexer::Token *index) :ActionBase(i, ActionType::INDEX), index_id(index) {}
			std::string trans()override {}
			std::string to_string()override {};
		private:
			Lexer::Token* index_id;
		};
	}
}