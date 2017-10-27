#pragma once
#include "Environment.hpp"
#include "../../Runtime/HPP/Object.hpp"
#include "../../Lexer/HPP/Literal.hpp"
#include <stack>
#include <memory>
/*
* 思路 : 语法分析我啥都没写哩.
* 首先我们构造一个Expression 类,
* 该类接受一个环境, 然后可以直接计算出表达式的值, 当然遇到id时我们调用一个
* 叫 get_value的类, 返回一个Object 然后
*/
namespace yt
{
	namespace Parser
	{
		class Expression
		{
		public:
			Expression(Environment *env);
			void skip();
			Runtime::ObjectBase* GetResult();
			void debug();
			// 返回的值不要delete
			Runtime::ObjectBase* GetObjectValue( size_t &i);
			~Expression() {
			}
		private:
			Lexer::Token * next_token()
			{
				return environment->token_stream->operator[](environment->current_pos++);
			}
			Lexer::Token * this_token()
			{
				return environment->token_stream->operator[](environment->current_pos);
			}
			bool match(Lexer::Tag t)
			{
				if ((environment->token_stream)->operator[](environment->current_pos++)->get_tag() == t)
				{
					return true;
				}
				return false;
			}
			char get_priority(yt::Lexer::Tag a)
			{
				switch (a)
				{
				case yt::Lexer::And:
				case yt::Lexer::Or:
					return 0;
				case yt::Lexer::Ge:
				case yt::Lexer::Gt:
				case yt::Lexer::Le:
				case yt::Lexer::Lt:
				case yt::Lexer::Ne:
				case yt::Lexer::Eq:
					return 1;
				case yt::Lexer::Add:
				case yt::Lexer::Sub:
					return 2;
				case yt::Lexer::Mul:
				case yt::Lexer::Div:
					return 3;
				case yt::Lexer::Lk:
					return 10;
				default:
					throw std::runtime_error("runtime_error4");
					break;
				}
			}
			std::vector<yt::Lexer::Token*> count_stack;
			Environment *environment;
		};
	}
}