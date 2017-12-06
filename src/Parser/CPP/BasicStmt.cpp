#include "..\HPP\BasicStmt.hpp"

std::string Simcc::Stmt::CreateVariable::to_string()
{
	std::string ret = type->to_string() + "\t" + id->to_string();
	if (init_value != nullptr)
		ret += init_value->to_string();
	return ret;
}

std::string Simcc::Stmt::TOS::to_string()
{
	return left_id->to_string() + " = " + r1->to_string() + oper->to_string() + r2->to_string();
}