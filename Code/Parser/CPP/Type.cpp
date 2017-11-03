#include "..\HPP\Type.hpp"
using namespace Simcc::Parser;
void Simcc::Parser::Type::AddMembers(const std::string & str, bool isPublic)
{
	auto result = type_map().find(str);
	if (result == type_map().end())
		;//throw Error::SyntaxError::unknown_token("unknown type");
	isPublic ? public_members.insert({ str,result->second }) : private_members.insert({ str,result->second });
}
std::unordered_map<std::string, Type*>& Simcc::Parser::Type::type_map()
{
	static std::unordered_map<std::string, Type*> ret
	{
		{"int32_t",new Type(INT,false)},{"double",new Type(DOUBLE,false)},{"char",new Type(CHAR,false)},
		{"string",new Type(STRING,false)},{"long",new Type(LONG,false)}
	};
	return ret;
}
