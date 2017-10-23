#pragma once
#include <string>
#include <iostream>
#include "../../Parser/HPP/Type.hpp"
namespace yt
{
	namespace Runtime
	{
		class ObjectBase {
		public:
			enum VType
			{
				Int, Long, Double, Char, String,Bool,User
			};
			enum CompareArg
			{
				Ne,Ge,Gt,Le,Lt,Eq,
			};
			ObjectBase(VType vt) :type(vt),data(nullptr) {}
			ObjectBase(int32_t a) :data(new int32_t(a)), type(Int) {}
			ObjectBase(double a) :data(new double(a)), type(Double) {}
			ObjectBase(char a) :data(new char(a)), type(Char) {}
			ObjectBase(std::string a) :data(new std::string(a)), type(String) {}
			ObjectBase(int64_t a) :data(new int64_t(a)), type(Long) {}
			ObjectBase(bool a) :data(new bool(a)), type(Bool) {}
			ObjectBase(const ObjectBase& v)
			{
				switch (v.type)
				{
				case Int:
					data = new int32_t(*(int32_t*)v.data);
					type = Int;
					break;
				case Double:
					data = new int32_t(*(double*)v.data);
					type = Double;
				case Long:
					data = new int64_t(*(int64_t*)v.data);
					type = Long;
					break;
				case Char:
					data = new char(*(char*)v.data);
					type = Char;
					break;
				case String:
					data = new std::string(*(std::string*)v.data);
					type = String;
					break;
				case Bool:
					data = new bool(*(bool*)v.data);
					type = Bool;
					break;
				default:
					throw std::runtime_error("yt::Runtime::ObjectBase(const ObjectBase&) 1");
					break;
				}
			}
			virtual ObjectBase& operator=(const ObjectBase&v)
			{
				if (v.data == data)
					return *this;
				delete data;
				switch (v.type)
				{
				case Int:
					data = new int32_t(*(int32_t*)v.data);
					type = Int;
					break;
				case Double:
					data = new int32_t(*(double*)v.data);
					type = Double;
				case Long:
					data = new int64_t(*(int64_t*)v.data);
					type = Long;
					break;
				case Char:
					data = new char(*(char*)v.data);
					type = Char;
					break;
				case String:
					data = new std::string(*(std::string*)v.data);
					type = String;
					break;
				case Bool:
					data = new bool(*(bool*)v.data);
					type = Bool;
					break;
				default:
					throw std::runtime_error("yt::Runtime::ObjectBase(const ObjectBase&) 1");
					break;
				}
			}
			virtual ~ObjectBase() {
				//std::cout << "BOOB!";
				delete data;
				//std::cout << "???\n";
			}
			template <typename T>
			T& get_value()
			{
				return *(T*)data;
			}
			int32_t to_int()const;
			float to_float()const;
			double to_double()const;
			int64_t to_long()const;
			virtual std::string to_string()const;
			//=========================== ��ʼ����ת��====================
			virtual ObjectBase* Add(const ObjectBase *obj1);// ������ָ�� �����ڴ�й¶, ����������ѣ�<{=�������� 
			virtual ObjectBase* Sub(const ObjectBase *obj1);
			virtual ObjectBase* Mul(const ObjectBase *obj1);
			virtual ObjectBase* Div(const ObjectBase *obj1);
		private:
			//=================== ��Щ����¶����=====================
			ObjectBase operator+ (const ObjectBase&v)const;
			ObjectBase operator- (const ObjectBase&v)const;
			ObjectBase operator*(const ObjectBase&v)const;
			ObjectBase operator/(const ObjectBase&v)const;
			ObjectBase operator==(const ObjectBase&v)const;
			ObjectBase operator>=(const ObjectBase&v)const;
			ObjectBase operator<=(const ObjectBase&v)const;
			ObjectBase operator!=(const ObjectBase&v)const;
			ObjectBase operator>(const ObjectBase&v)const;
			ObjectBase operator<(const ObjectBase&v)const;
			VType type;
			void *data;
		};
		class Object:ObjectBase
		{
		public:
			Object(const Parser::Type& t) :type(t),ObjectBase(ObjectBase::VType::User) {
				for (const auto & a : t.private_members)
				{
					switch (a.second->type_structure)
					{
					case Parser::Type::BOOL:
						private_member_table.insert({ a.first,new ObjectBase(false) });
						break;
					case Parser::Type::DOUBLE:
						private_member_table.insert({ a.first,new ObjectBase((double)0) });
						break;
					case Parser::Type::INT:
						private_member_table.insert({ a.first,new ObjectBase((int32_t)0) });
						break;
					case Parser::Type::LONG:
						private_member_table.insert({ a.first,new ObjectBase((int64_t)0) });
						break;
					case Parser::Type::STRING:
						private_member_table.insert({ a.first,new ObjectBase(std::string(0)) });
						break;
					case Parser::Type::CHAR:
						private_member_table.insert({ a.first,new ObjectBase((char)0) });
						break;
					case Parser::Type::CLASS:
						private_member_table.insert({ a.first,new Object(*a.second) });
						break;
					default:
						throw std::runtime_error("runtime_error1");
						break;
					}
				}
				for (const auto & a : t.public_members)
				{
					switch (a.second->type_structure)
					{
					case Parser::Type::BOOL:
						public_member_table.insert({ a.first,new ObjectBase(false) });
						break;
					case Parser::Type::DOUBLE:
						public_member_table.insert({ a.first,new ObjectBase((double)0) });
						break;
					case Parser::Type::INT:
						public_member_table.insert({ a.first,new ObjectBase((int32_t)0) });
						break;
					case Parser::Type::LONG:
						public_member_table.insert({ a.first,new ObjectBase((int64_t)0) });
						break;
					case Parser::Type::STRING:
						public_member_table.insert({ a.first,new ObjectBase(std::string(0)) });
						break;
					case Parser::Type::CHAR:
						public_member_table.insert({ a.first,new ObjectBase((char)0) });
						break;
					case Parser::Type::CLASS:
						public_member_table.insert({ a.first,new Object(*a.second) });
						break;
					default:
						throw std::runtime_error("runtime_error2");
						break;
					}
				}
				for (const auto & a : t.public_members)
					public_member_table.insert({ a.first,new Object(*a.second) });
			};
			void set_value(const std::string & str, ObjectBase* objb)
			{
				auto result = private_member_table.find(str);
				if(result == private_member_table.end())
					throw std::runtime_error("runtime_error3");
				
			}
		private:
			ObjectBase *set_value(const Parser::Type &t)
			{
				switch (t.type_structure)
				{
				case Parser::Type::INT:
					return new ObjectBase((int32_t)0);
				case Parser::Type::DOUBLE:
					return new ObjectBase((double_t)0.0);
				case Parser::Type::CHAR:
					return new ObjectBase((char)' ');
				case Parser::Type::STRING:
					return new ObjectBase(std::string(0));
				case Parser::Type::LONG:
					return new ObjectBase((int64_t)0);
				case Parser::Type::BOOL:
					return new ObjectBase((bool)false);
				default:
					return nullptr;
				}
			}
			Parser::Type type;
			std::unordered_map<std::string, ObjectBase*> private_member_table;
			std::unordered_map<std::string, ObjectBase*> public_member_table;
		};
	}
	namespace Test
	{
		struct pos
		{
			pos(int32_t a, int32_t b) :x(a), y(b) {}
			int32_t x;
			int32_t y;
		};
		void object_test();
	}
}