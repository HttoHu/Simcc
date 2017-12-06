#pragma once
#include <iostream>
#include <string>
#include "../../Context/HPP/Type.hpp"
#include "../../Lexer/HPP/Id.hpp"
namespace Simcc
{
	namespace Stmt
	{
		class Stmt
		{
		public:
			virtual ~Stmt() {};
			virtual void trans() {}
			virtual std::string to_string() { return ""; }
		private:

		};

		class CreateVariable :public Stmt
		{
		public:
			CreateVariable(Context::Type *id_v,Lexer::TId *t) :id(t), type(id_v) {}
			CreateVariable(Context::Type *t, Lexer::TId *i, Lexer::Token* value) :type(t), id(i), init_value(value) {}
			std::string to_string()override;
		private:
			Context::Type *type;
			Lexer::Token *init_value=nullptr;
			Lexer::TId *id;
		};
		// a=b+c;
		class TOS:public Stmt
		{
		public:
			TOS(Lexer::TId *vid, Lexer::TId * op1, Lexer::TId*op2, Lexer::Operator *op):left_id(vid),
			r1(op1),r2(op2),oper(op){}
			std::string to_string()override;
		private:
			Lexer::Operator *oper;
			Lexer::TId *left_id;
			Lexer::TId *r1;
			Lexer::TId* r2;
		};
		//a+=b;
		class Assign :public Stmt
		{
		public:
			Assign(Lexer::TId *vid, Lexer::TId * op1, Lexer::Operator *op) :left_id(vid),
				r1(op1), oper(op) {}
			std::string to_string()override
			{
				return left_id->to_string() + oper->to_string()+r1->to_string();
			}
		private:
			Lexer::Operator *oper;
			Lexer::TId *left_id;
			Lexer::TId *r1;
		};
		// b++;
		class SingleOS :public Stmt
		{
		public:
			SingleOS(Lexer::TId *id, Lexer::Operator *op) :v(id), oper(op) {}
			std::string to_string()override
			{
				return v->to_string() + oper->to_string();
			}
		private:
			Lexer::Operator *oper;
			Lexer::TId *v;
		};
		class AssignWithAction :public Stmt
		{
		public:
			AssignWithAction(Lexer::TId *vid, Lexer::Operator *op, Lexer::Operator * act, Lexer::TId *rid) :action_type(act),
				left(vid), oper(op),right(rid) {}
			std::string to_string()override {
				return left->to_string() + oper->to_string() + action_type->to_string() + right->to_string();
			}
		private:
			Lexer::Operator *oper;
			Lexer::Operator *action_type;
			Lexer::TId *left;
			Lexer::TId *right;
		};
	}
}