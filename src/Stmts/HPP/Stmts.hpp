#pragma once
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
		TOP(Lexer::TId *right, Lexer::TId *p1, Lexer::CountSign cs, Lexer::TId *p2)
			:right_v(right), oper1(p1), top_type(cs),oper2(p2) {}
		std::string to_string()const override
		{
			return right_v->to_string() + "=" + oper1->to_string()+std::to_string(top_type)+oper2->to_string();
		}
	private:
		Lexer::TId *right_v;
		Lexer::TId *oper1;
		Lexer::TId *oper2;
		Lexer::CountSign top_type;
	};
	class CreateVar :public Stmt
	{
	public:
		CreateVar(Lexer::Token *n, Lexer::Token * v):init(v)
		{
			if (n->get_tag() != Lexer::Id)
			{
				throw std::runtime_error("CreateVar(Lexer::Token *n, Lexer::Token * v):init(v)");
			}
			id = static_cast<Lexer::TId*>(n);
			switch (v->get_tag())
			{
			case Lexer::TLiteralInt:
				type = Context::Type::find_type("int");
				Context::insert_id_info(id, type);
				break;
			case Lexer::TLiteralChar:
				type = Context::Type::find_type("char");
				Context::insert_id_info(id, type);
				break;
			case Lexer::TLiteralDouble:
				type = Context::Type::find_type("double");
				Context::insert_id_info(id, type);
				break;
			case Lexer::TLiteralString:
				type = Context::Type::find_type("string");
				Context::insert_id_info(id, type);
				break;
			case Lexer::TLiteralLong:
				type = Context::Type::find_type("long");
				Context::insert_id_info(id, type);
				break;
			case Lexer::True:
				type = Context::Type::find_type("bool");
				Context::insert_id_info(id, type);
				break;
			case Lexer::False:
				type = Context::Type::find_type("bool");
				Context::insert_id_info(id, type);
				break;
			case Lexer::Id:
				type = Context::find_id_info( static_cast<Lexer::TId*>(init) ).type;
				Context::insert_id_info(id, type);
				break;
			default:
				break;
			}
		}
		CreateVar(Context::Type *t, Lexer::Token *n, Lexer::Token * v): init(v), type(t) 
		{
			if (n->get_tag() != Lexer::Id)
			{
				throw std::runtime_error("CreateVar(Context::Type *t, Lexer::Token *n, Lexer::Token * v): init(v), type(t) ");
			}
			id = static_cast<Lexer::TId*>(n);
			Context::insert_id_info(id, type);
		}
		std::string to_string()const override
		{
			return "<"+type->to_string()+">"+id->to_string() + "=" + init->to_string();
		}
	private:
		Context::Type *type;
		Lexer::TId *id;
		Lexer::Token *init;
	};
	class TOPCV:public Stmt
	{
	public:
		TOPCV(Lexer::Token *right, Lexer::TId *l1, Lexer::CountSign cs, Lexer::TId *l2)
			: oper1(l1), top_type(cs), oper2(l2) {
			if (right->get_tag() != Lexer::Id)
			{
				throw std::runtime_error("TOPCV");

				
			}
			right_v = static_cast<Lexer::TId*>(right);
			auto type = Context::find_id_info(static_cast<Lexer::TId*>(l1)).type;
			Context::insert_id_info(right_v, type);
		}
		std::string to_string()const override
		{
			return "<var>"+ right_v->to_string() + "=" + oper1->to_string() + std::to_string(top_type) + oper2->to_string();
		}
	private:
		Lexer::TId *right_v;
		Lexer::TId *oper1;
		Lexer::TId *oper2;
		Lexer::CountSign top_type;
	};
	class AssignStmt :public Stmt
	{
	public:
		AssignStmt(Lexer::TId *l, Lexer::CountSign o, Lexer::TId *r) :left(l), op(o), right(r) {}
		std::string to_string()const override
		{
			return left->to_string() + std::to_string(op) + right->to_string();
		}
	private:
		Lexer::TId *left;
		Lexer::CountSign op;
		Lexer::TId *right;
	};
}