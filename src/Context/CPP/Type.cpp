#include "../HPP/Type.hpp"
using namespace Simcc;
std::map<size_t, Context::Type* >& Context::Type::type_table()
{
	static std::map<size_t, Context::Type*> ret{
	{ 0,_create_basic_type("int",sizeof(int32_t),Context::INT) },
	{ 1,_create_basic_type("long",sizeof(int64_t),Context::LONG) },
	{ 2,_create_basic_type("char",sizeof(char),Context::CHAR) },
	{ 3,_create_basic_type("string",sizeof(std::string),Context::STRING) },
	{ 4,_create_basic_type("double",sizeof(double),Context::DOUBLE) },
	{ 5,_create_basic_type("bool",sizeof(bool),Context::BOOL) } };
	return ret;
};
std::map<std::string, size_t>& Context::Type::name_typeid()
{
	static std::map<std::string, size_t> ret;
	return ret;
}

size_t Context::Type::current_type_index=0;

Simcc::Context::Type::Type(const std::string & type_name, const std::vector<size_t>& amembers):basic_type(BasicType::USER)
{
	for (auto a :amembers)
	{
		auto b = type_table().find(a);
		if (b == type_table().end())
			throw std::runtime_error("no found such type");
		members.push_back(b->second);
		type_size += b->second->type_size;
	}
	name_typeid().insert({ type_name, current_type_index });
	type_table().insert({ current_type_index++,this });
}

std::string Simcc::Context::Type::to_string() const
{
	std::string ret;
	for (const auto& a : members)
	{
		switch (a->basic_type)
		{
		case BasicType::INT:
			ret+= "int\n";
			break;
		case BasicType::DOUBLE:
			ret += "double\n";
			break;
		case BasicType::CHAR:
			ret += "char\n";
			break;
		case BasicType::BOOL:
			ret += "bool\n";
			break;
		case BasicType::STRING:
			ret += "string\n";
			break;
		case BasicType::LONG:
			ret += "long\n";
			break;
		case BasicType::USER:
			ret += a->to_string() + "\n";
			break;
		}

	}
	return ret;
}

void Simcc::Context::Type::add_member(size_t m)
{
	auto a = type_table().find(m);
	if (a == type_table().end())
	{
		throw std::runtime_error("no found such type");
	}
	type_size += a->second->type_size;
	members.push_back(a->second);
}

void Simcc::Context::Type::add_member(const std::string & str)
{
	auto pos = name_typeid().find(str);
	if (pos == name_typeid().end())
	{
		throw std::runtime_error("no found such type");
	}
	auto a = type_table().find(pos->second);
	if (a == type_table().end())
	{
		throw std::runtime_error("no found such type");
	}
	type_size += a->second->type_size;
	members.push_back(a->second);
}

void Simcc::Context::type_test()
{
	Context::Type t(std::string("Coor"), std::vector<size_t>({ 1,2,1 }));
	Context::Type t2(std::string("D"), std::vector<size_t>({ 3,3,4 }));
	t.add_member(0);
	t2.add_member("Coor");
	std::cout << t2.to_string();
	std::cout << "length:" << t2.length();
}
