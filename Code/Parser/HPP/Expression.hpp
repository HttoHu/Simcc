#pragma once
#include "Environment.hpp"
#include "../../Runtime/HPP/Object.hpp"
#include "../../Lexer/HPP/Literal.hpp"
#include <stack>
#include <memory>
/*
* ˼· : �﷨������ɶ��ûд��.
* �������ǹ���һ��Expression ��, 
* �������һ������, Ȼ�����ֱ�Ӽ�������ʽ��ֵ, ��Ȼ����idʱ���ǵ���һ��
* �� get_value����, ����һ��Object Ȼ��
*/
namespace yt
{
	namespace Parser
	{
		class _Eunit
		{
		public:
			enum Operator
			{
				Add, Sub, Mul, Div, Lk, Rk, Value = 10
			};
			_Eunit(Runtime::ObjectBase *o) :obj(o), op(Value) {}
			_Eunit(Operator oper) :op(oper), obj(nullptr) 
			{
			}
			void destroData()
			{
				delete obj;
			}
			std::string to_string()const
			{
				if (obj)
				{
					return obj->to_string();
				}
				else 
					switch (op)
					{
					case yt::Parser::_Eunit::Add:
						return "+";
					case yt::Parser::_Eunit::Sub:
						return "-";
					case yt::Parser::_Eunit::Mul:
						return "*";
					case yt::Parser::_Eunit::Div:
						return "/";
					case yt::Parser::_Eunit::Lk:
						return "(";
					case yt::Parser::_Eunit::Rk:
						return ")";
					default:
						return "<Unknown Error>";
					}
			}
			Runtime::ObjectBase *obj;
			Operator op;
		};
		class Expression
		{
		public:
			Expression(Environment *env) :environment(env) {}
			~Expression()
			{
				for (auto &a : outPut)
				{
					a.destroData();
				}
			}
			void CreateExpressionStack();
			Runtime::ObjectBase* GetObjectValue();
			Runtime::ObjectBase* GetResult();
			void Translate();
			void debug();
		private:
			char get_priority(_Eunit & a)
			{
				switch (a.op)
				{
				case _Eunit::Sub:
				case _Eunit::Add:
					return 1;
				case _Eunit::Mul:
				case _Eunit::Div:
					return 2;
				case _Eunit::Lk:
					return 3;
				default:
					throw std::runtime_error("runtime_error4");
				}
			}
			void pop_top()
			{
				outPut.push_back(operatorStack.back());
				operatorStack.pop_back();
			}
			std::vector<_Eunit> tmpStack;
			std::vector<_Eunit> outPut;
			std::vector<_Eunit> operatorStack;
			Environment *environment;
		};
	}
}