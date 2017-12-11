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
		};
		class ActionBase
		{
		public:
			ActionBase(Lexer::TId *i, ActionType at) :id(i), action(at) {}
			virtual ~ActionBase(){}
			virtual std::string trans()
			{
				return "";
			}
			virtual std::string to_string() 
			{
				std::string front_part= id->to_string();
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
					std::cerr << "<unknown action>";
					abort();
					break;
				}
			}
			Lexer::TId *id;
			ActionType action;
		};
		class ActionIndex :public ActionBase
		{
		public:
			ActionIndex(Lexer::TId *i, Lexer::TId *index) :ActionBase(i, ActionType::INDEX), index_id(index) {}
			std::string trans()override {}
			std::string to_string()override {};
		private:
			Lexer::TId* index_id;
		};
	}
}