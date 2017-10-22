#pragma once
#include <string>
#include <vector>
#include "Object.hpp"
namespace yt
{
	namespace Runtime
	{
		class Stack{
		public:
			static void newBlock()
			{
				stack_memory.push_front(std::unordered_map<std::string, Object>());
			}
			static void endBlock()
			{
				stack_memory.pop_front();
			}
			static Object& find_variable(const std::string & variable_name)
			{
				auto current = stack_memory.begin();
				while (current != stack_memory.end())
				{
					auto result = current->find(variable_name);
					if (result != current->end())
					{
						return result->second;
					}
					current++;
				}
				throw std::runtime_error("unknow variable");
			}
			static void push(const std::string & vname, const  Object &obj)
			{
				stack_memory.front().insert({ vname,obj });
			}
		private:
			static std::list<std::unordered_map<std::string,Object>> stack_memory;
		};
	}
}