#pragma once
#include "Stmt.hpp"
#include "Environment.hpp"
#include "CreateObject.hpp"
#include "Single.hpp"
namespace Simcc
{
	namespace Parser
	{
		class Parser
		{
		public:
			// 这只是用来测试的类, 远不是这样.
			Parser(Environment *env) :environment(env)
			{
				using namespace Lexer;
				while (environment->current_pos < environment->token_stream->size())
				{

					switch (this_token()->get_tag())
					{
					case Tag::SBool:
					case Tag::SInt:
					case Tag::SDouble:
					case Tag::SString:
					case Tag::SChar:
					case Tag::SLong:
						lst.push_back(new CreateBasicTypeObject(environment));
					case Tag::Id:
						lst.push_back(new Single(environment));
					case Tag::Endl:
						environment->current_line++;
						next_token();
						break;
					default:
						std::cout << "\n\nError:" << this_token()->to_string();
						throw std::runtime_error(std::to_string(environment->current_line)+"runtime_error11");
						break;
					}
					environment->current_pos++;
				}
			}
			Lexer::Token * next_token()
			{
				return environment->token_stream->operator[](environment->current_pos++);
			}
			Lexer::Token * this_token()
			{
				return environment->token_stream->operator[](environment->current_pos);
			}
			void execute()
			{
				for (auto & a : lst)
				{
					a->execute();
				}
			}
		private:
			Environment *environment;
			std::list<Stmt*>lst;
		};
	}
}