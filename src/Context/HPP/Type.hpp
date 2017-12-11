#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
namespace Simcc
{
	namespace Context
	{
		enum BasicType
		{
			INT,LONG,DOUBLE,CHAR,BOOL,STRING,USER,
			REF,
		};
		class Type
		{
		public:
			static Type* find_type(const std::string &str);
			static std::map<std::string, size_t>& name_typeid();
			static std::map<size_t, Type* >& type_table();
			static size_t current_type_index;
			Type(const std::string &type_name, const std::vector<size_t> & amembers);
			std::string to_string()const;
			void add_member(size_t m);
			void add_member(const std::string &str);
			size_t length() { return type_size; }
			BasicType basic_type;
		private:

			Type() {}
			static Type* _create_basic_type(const std::string &type_name, size_t length, BasicType bt) 
			{
				Type *ret = new Type();
				ret->type_size = length;
				name_typeid().insert({ type_name, current_type_index });
				ret->basic_type = bt;
				current_type_index++;
				return ret;
			}
			std::vector<Type*> members;
			size_t type_size=0;
		};
		void type_test();
	}
}