#pragma once
#include "VarUnit.hpp"
#include "../../Context/HPP/SymbolTable.hpp"
namespace Simcc
{
	namespace Context
	{
		class Type;
	}
	class Stmt
	{
	public:
		virtual ~Stmt() {}
		virtual std::string trans()const { return "<unknow stmt>"; }
		virtual std::string to_string()const { return "<unknow stmt>"; }
	private:

	};
	// three operator stmt eg: a=c+d 
	class TOP :public Stmt
	{
	public:
		TOP(Action::ActionBase *right, Action::ActionBase *l1, Lexer::CountSign cs, Action::ActionBase *l2)
			:right_v(right), oper1(l1), top_type(cs),oper2(l2) {}
		std::string to_string()const override
		{
			return right_v->to_string() + "=" + oper1->to_string()+std::to_string(top_type)+oper2->to_string();
		}
	private:
		Action::ActionBase *right_v;
		Action::ActionBase *oper1;
		Action::ActionBase *oper2;
		Lexer::CountSign top_type;
	};
	class CreateVar :public Stmt
	{
	public:
		CreateVar(Action::ActionBase *n, Lexer::Token * v):id(n),init(v)
		{
			if (n->action != Action::SINGLE)
				throw std::runtime_error("must create a single var");
			switch (v->get_tag())
			{
			case Lexer::Id:
				type = Context::find_id_info(id->id).type;
				break;
			case Lexer::TLiteralChar:
				type = Context::Type::find_type("char");
				Context::insert_id_info(id->id, type);
				break;
			case Lexer::TLiteralString:
				type = Context::Type::find_type("string");
				Context::insert_id_info(id->id, type);
				break;
			case Lexer::TLiteralInt:
				type = Context::Type::find_type("int");
				Context::insert_id_info(id->id, type);
				break;
			case Lexer::TLiteralLong:
				type = Context::Type::find_type("long");
				Context::insert_id_info(id->id, type);
				break;
			case Lexer::True:
			case Lexer::False:
				type = Context::Type::find_type("bool");
				Context::insert_id_info(id->id, type);
				break;
			case Lexer::TLiteralDouble:
				type = Context::Type::find_type("double");
				Context::insert_id_info(id->id,type);				
				break;
			default:
				break;
			}
		}
		std::string to_string()const override
		{
			return "<var> "+id->to_string() + "=" + init->to_string();
		}
	private:
		Context::Type *type;
		Action::ActionBase *id;
		Lexer::Token *init;
	};
	class TOPCV:public Stmt
	{
	public:
		TOPCV(Action::ActionBase *right, Action::ActionBase *l1, Lexer::CountSign cs, Action::ActionBase *l2)
			:right_v(right), oper1(l1), top_type(cs), oper2(l2) {
		}
		std::string to_string()const override
		{
			return "<var>"+ right_v->to_string() + "=" + oper1->to_string() + std::to_string(top_type) + oper2->to_string();
		}
	private:
		Action::ActionBase *right_v;
		Action::ActionBase *oper1;
		Action::ActionBase *oper2;
		Lexer::CountSign top_type;
	};
	class AssignStmt :public Stmt
	{
	public:
		AssignStmt(Action::ActionBase *l, Lexer::CountSign o, Action::ActionBase *r) :left(l), op(o), right(r) {}
		std::string to_string()const override
		{
			return left->to_string() + std::to_string(op) + right->to_string();
		}
	private:
		Action::ActionBase *left;
		Lexer::CountSign op;
		Action::ActionBase *right;
	};
}