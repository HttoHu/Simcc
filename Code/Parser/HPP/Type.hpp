#pragma once
#include <string>
#include <unordered_map>
#include "Error.hpp"
namespace Simcc
{
	namespace Runtime
	{
		class Object;
	}
	namespace Parser
	{
		// 类型方案: 
		class Type
		{
		public:
			enum TypeStructure
			{
				INT, DOUBLE, LONG, CHAR, STRING, BOOL, CLASS,
			};
			Type() :type_structure(CLASS), default_reference(true) {}
			Type(TypeStructure ts,bool b) :type_structure(ts),default_reference(b){}
			void AddMembers(const std::string &str,bool isPublic);
			static std::unordered_map<std::string, Type*>& type_map();
			static void clearType();
		private:
			friend class Runtime::Object;
			std::unordered_map<std::string, Type*> public_members;
			std::unordered_map<std::string, Type*> private_members;
			bool default_reference;
			TypeStructure type_structure;
		};
	}
}