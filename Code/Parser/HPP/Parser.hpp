#pragma once
#include "Stmt.hpp"
#include "Environment.hpp"
#include "CreateObject.hpp"
#include "Assign.hpp"
namespace yt
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
					case Tag::SInt:
					case Tag::SDouble:
					case Tag::SString:
					case Tag::SChar:
					case Tag::SLong:
						(new CreateBasicTypeObject(environment))->execute();
						break;
					case Tag::Id:
						(new Assign(environment))->execute();
						break;
					case Tag::Endl:
						next_token();
						break;
					default:
						throw std::runtime_error("runtime_error11");
						break;
					}
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
					//a->execute();
				}
			}
		private:
			Environment *environment;
			std::list<Stmt*>lst;
		};
	}
}