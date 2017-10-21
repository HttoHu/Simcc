#pragma once
#include <string>
#include "../../Parser/HPP/Type.hpp"
namespace yt
{
	namespace Runtime
	{
		class Value {
		public:
			Value() :data(nullptr), user_count(new size_t(1)) {}
			template <typename ValueType>
			Value(const ValueType& vt) : data(new ValueType(vt)), user_count(new size_t(1)) {}
			Value(const char * c_str) :Value(std::string(c_str)) {}
			Value(const Value & obj) {
				++*obj.user_count;
				data = obj.data;
				user_count = obj.user_count;
			}
			Value& operator= (const Value & obj) {
				++*obj.user_count;
				--*user_count;
				_check();
				user_count = obj.user_count;
				data = obj.data;
				return *this;
			}
			~Value() {
				--*user_count;
				_check();
			}
			//=========================
			Value copy()const;
			template <typename ValueType>
			ValueType & get_value()
			{
				return *(ValueType*)data;
			}
		private:
			void _check();
			void *data;
			size_t *user_count;
		};
		class Object
		{
		public:
			Object(const Parser::Type& t) :type(t) {
				value = set_value(t);
				for (const auto & a : t.private_members)
					private_member_table.insert({ a.first,new Object(*a.second) });
				for (const auto & a : t.public_members)
					public_member_table.insert({ a.first,new Object(*a.second) });
			};
		private:
			Value *set_value(const Parser::Type &t)
			{
				switch (t.type_structure)
				{
				case Parser::Type::INT:
					return new Value((int32_t)0);
				case Parser::Type::DOUBLE:
					return new Value((double_t)0.0);
				case Parser::Type::CHAR:
					return new Value((char)' ');
				case Parser::Type::STRING:
					return new Value(std::string(0));
				case Parser::Type::LONG:
					return new Value((int64_t)0);
				case Parser::Type::BOOL:
					return new Value((bool)false);
				default:
					return nullptr;
				}
			}
			Parser::Type type;
			std::unordered_map<std::string, Object*> private_member_table;
			std::unordered_map<std::string, Object*> public_member_table;
			Value *value;
		};
	}
	namespace Test
	{
		struct pos
		{
			pos(int a, int b) :x(a), y(b) {}
			int x;
			int y;
		};
		void object_test();
	}
}
