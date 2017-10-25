#include "../HPP/Object.hpp"
using namespace yt::Runtime;
int32_t yt::Runtime::ObjectBase::to_int()const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return *(int32_t*)data;
	case yt::Runtime::ObjectBase::Long:
		return (int32_t)*(long*)data;
	case yt::Runtime::ObjectBase::Double:
		return (int32_t)*(double*)data;
	case yt::Runtime::ObjectBase::Char:
		return (int32_t)*(char*)data;
	case yt::Runtime::ObjectBase::String:
		throw std::runtime_error("double yt::Runtime::ObjectBase::get_float_value()");
	case yt::Runtime::ObjectBase::Bool:
		return (int32_t)*(bool*)data;
	default:
		throw std::runtime_error("double yt::Runtime::ObjectBase::get_float_value() ");
	}
}
float yt::Runtime::ObjectBase::to_float()const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return (float)*(int32_t*)data;
	case yt::Runtime::ObjectBase::Long:
		return (float)*(long*)data;
	case yt::Runtime::ObjectBase::Double:
		return (float)*(double*)data;
	case yt::Runtime::ObjectBase::Char:
		return (float)*(char*)data;
	case yt::Runtime::ObjectBase::String:
		throw std::runtime_error("double yt::Runtime::ObjectBase::get_float_value()");
	case yt::Runtime::ObjectBase::Bool:
		return (float)*(bool*)data;
	default:
		throw std::runtime_error("double yt::Runtime::ObjectBase::get_float_value() ");
	}
}
double yt::Runtime::ObjectBase::to_double()const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return (double)*(int32_t*)data;
	case yt::Runtime::ObjectBase::Long:
		return (double)*(long*)data;
	case yt::Runtime::ObjectBase::Double:
		return (double)*(double*)data;
	case yt::Runtime::ObjectBase::Char:
		return (double)*(char*)data;
	case yt::Runtime::ObjectBase::String:
		throw std::runtime_error("double yt::Runtime::ObjectBase::get_float_value()");
	case yt::Runtime::ObjectBase::Bool:
		return (double)*(bool*)data;
	default:
		throw std::runtime_error("double yt::Runtime::ObjectBase::get_float_value() ");
	}
}
int64_t yt::Runtime::ObjectBase::to_long()const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return (int64_t)*(int32_t*)data;
	case yt::Runtime::ObjectBase::Long:
		return (int64_t)*(long*)data;
	case yt::Runtime::ObjectBase::Double:
		return (int64_t)*(double*)data;
	case yt::Runtime::ObjectBase::Char:
		return (int64_t)*(char*)data;
	case yt::Runtime::ObjectBase::String:
		throw std::runtime_error("double yt::Runtime::ObjectBase::get_float_value()");
	case yt::Runtime::ObjectBase::Bool:
		return (int64_t)*(bool*)data;
	default:
		throw std::runtime_error("double yt::Runtime::ObjectBase::get_float_value() ");
	}
}

bool yt::Runtime::ObjectBase::to_bool() const
{
	return *(bool*)data;
}

std::string yt::Runtime::ObjectBase::to_string()const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return std::to_string(*(int32_t*)data);
	case yt::Runtime::ObjectBase::Long:
		return std::to_string(*(long*)data);
	case yt::Runtime::ObjectBase::Double:
		return std::to_string(*(double*)data);
	case yt::Runtime::ObjectBase::Char:
		return std::to_string((int64_t)*(char*)data);
	case yt::Runtime::ObjectBase::String:
		return *(std::string*)data;
	case yt::Runtime::ObjectBase::Bool:
		if (*(bool*)data)
		{
			return "true";
		}
		return "false";
	default:
		throw std::runtime_error("double yt::Runtime::ObjectBase::to_string() ");
	}
}

ObjectBase * yt::Runtime::ObjectBase::Add(const ObjectBase * obj1)
{
	ObjectBase *ret = new ObjectBase(*obj1 + *this);
	return ret;
}
ObjectBase * yt::Runtime::ObjectBase::Sub(const ObjectBase * obj1)
{
	ObjectBase *ret = new ObjectBase(*this-*obj1 );
	return ret;
}
ObjectBase * yt::Runtime::ObjectBase::Mul(const ObjectBase * obj1)
{
	ObjectBase *ret = new ObjectBase(*obj1 * *this);
	return ret;
}
ObjectBase * yt::Runtime::ObjectBase::Div(const ObjectBase * obj1)
{
	ObjectBase *ret = new ObjectBase(*obj1 / *this);
	return ret;
}
ObjectBase* yt::Runtime::ObjectBase::Compare(const ObjectBase * obj, yt::Lexer::Tag t)
{
	switch (t)
	{
	case yt::Lexer::Ge:
		return new ObjectBase(*this >= *obj);
	case yt::Lexer::Gt:
		return new ObjectBase(*this > *obj);
	case yt::Lexer::Le:
		return new ObjectBase(*this <= *obj);
	case yt::Lexer::Lt:
		return new ObjectBase(*this < *obj);
	case yt::Lexer::Ne:
		return new ObjectBase(*this != *obj);
	case yt::Lexer::Eq:
		return new ObjectBase(*this == *obj);
	case yt::Lexer::And:
		return new ObjectBase(get_value<bool>() &&obj->get_value<bool>());
	case yt::Lexer::Or:
		return new ObjectBase(get_value<bool>() || obj->get_value<bool>());
	default:
		break;
	}


}
ObjectBase yt::Runtime::ObjectBase::operator+(const ObjectBase & v) const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return ObjectBase(*(int32_t*)data + v.to_int());
	case yt::Runtime::ObjectBase::Long:
		return ObjectBase(*(int64_t*)data + v.to_long());
	case yt::Runtime::ObjectBase::Double:
		return ObjectBase(*(double*)data + v.to_double());
	case yt::Runtime::ObjectBase::Char:
		return ObjectBase(*(char*)data + *(char*)v.data);
	case yt::Runtime::ObjectBase::String:
		return ObjectBase(*(std::string*)data + v.to_string());
	default:
		throw std::runtime_error("ObjectBase yt::Runtime::ObjectBase::operator+(const ObjectBase & v) const ");
	}
}
ObjectBase yt::Runtime::ObjectBase::operator-(const ObjectBase & v) const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return ObjectBase(*(int32_t*)data - v.to_int());
	case yt::Runtime::ObjectBase::Long:
		return ObjectBase(*(int64_t*)data - v.to_long());
	case yt::Runtime::ObjectBase::Double:
		return ObjectBase(*(double*)data - v.to_double());
	case yt::Runtime::ObjectBase::Char:
		return ObjectBase(*(char*)data - *(char*)v.data);
	case yt::Runtime::ObjectBase::String:
		throw std::runtime_error("ObjectBase yt::Runtime::ObjectBase::operator-(const ObjectBase & v) const ");
	default:
		throw std::runtime_error("ObjectBase yt::Runtime::ObjectBase::operator-(const ObjectBase & v) const ");
	}
}

ObjectBase yt::Runtime::ObjectBase::operator*(const ObjectBase & v) const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return ObjectBase(*(int32_t*)data * v.to_int());
	case yt::Runtime::ObjectBase::Long:
		return ObjectBase(*(int64_t*)data * v.to_long());
	case yt::Runtime::ObjectBase::Double:
		return ObjectBase(*(double*)data * v.to_double());
	case yt::Runtime::ObjectBase::Char:
		return ObjectBase(*(char*)data * *(char*)v.data);
	case yt::Runtime::ObjectBase::String:
		throw std::runtime_error("ObjectBase yt::Runtime::ObjectBase::operator*(const ObjectBase & v) const ");
	default:
		throw std::runtime_error("ObjectBase yt::Runtime::ObjectBase::operator*(const ObjectBase & v) const ");
	}
}
ObjectBase yt::Runtime::ObjectBase::operator/(const ObjectBase & v) const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return ObjectBase(*(int32_t*)data / v.to_int());
	case yt::Runtime::ObjectBase::Long:
		return ObjectBase(*(int64_t*)data / v.to_long());
	case yt::Runtime::ObjectBase::Double:
		return ObjectBase(*(double*)data / v.to_double());
	case yt::Runtime::ObjectBase::Char:
		return ObjectBase(*(char*)data / *(char*)v.data);
	case yt::Runtime::ObjectBase::String:
		throw std::runtime_error("ObjectBase yt::Runtime::ObjectBase::operator/(const ObjectBase & v) const ");
	default:
		throw std::runtime_error("ObjectBase yt::Runtime::ObjectBase::operator/(const ObjectBase & v) const ");
	}
}
ObjectBase yt::Runtime::ObjectBase::operator==(const ObjectBase & v) const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return ObjectBase(*(int32_t*)data == v.to_int());
	case yt::Runtime::ObjectBase::Long:
		return ObjectBase(*(int64_t*)data == v.to_long());
	case yt::Runtime::ObjectBase::Double:
		return ObjectBase(*(double*)data == v.to_double());
	case yt::Runtime::ObjectBase::Char:
		return ObjectBase(*(char*)data == *(char*)v.data);
	case yt::Runtime::ObjectBase::String:
		return ObjectBase(*(std::string*)data == v.to_string());
	default:
		throw std::runtime_error("ObjectBase yt::Runtime::ObjectBase::operator==(const ObjectBase & v) const ");
	}
}
ObjectBase yt::Runtime::ObjectBase::operator>=(const ObjectBase & v) const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return ObjectBase(*(int32_t*)data >= v.to_int());
	case yt::Runtime::ObjectBase::Long:
		return ObjectBase(*(int64_t*)data >= v.to_long());
	case yt::Runtime::ObjectBase::Double:
		return ObjectBase(*(double*)data >= v.to_double());
	case yt::Runtime::ObjectBase::Char:
		return ObjectBase(*(char*)data >= *(char*)v.data);
	case yt::Runtime::ObjectBase::String:
		return ObjectBase(*(std::string*)data >= v.to_string());
	default:
		throw std::runtime_error("ObjectBase yt::Runtime::ObjectBase::operator>=(const ObjectBase & v) const ");
	}
}
ObjectBase yt::Runtime::ObjectBase::operator<=(const ObjectBase & v) const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return ObjectBase(*(int32_t*)data <= v.to_int());
	case yt::Runtime::ObjectBase::Long:
		return ObjectBase(*(int64_t*)data <= v.to_long());
	case yt::Runtime::ObjectBase::Double:
		return ObjectBase(*(double*)data <= v.to_double());
	case yt::Runtime::ObjectBase::Char:
		return ObjectBase(*(char*)data <= *(char*)v.data);
	case yt::Runtime::ObjectBase::String:
		return ObjectBase(*(std::string*)data <= v.to_string());
	default:
		throw std::runtime_error("ObjectBase yt::Runtime::ObjectBase::operator<=(const ObjectBase & v) const ");
	}
}
ObjectBase yt::Runtime::ObjectBase::operator!=(const ObjectBase & v) const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return ObjectBase(*(int32_t*)data != v.to_int());
	case yt::Runtime::ObjectBase::Long:
		return ObjectBase(*(int64_t*)data != v.to_long());
	case yt::Runtime::ObjectBase::Double:
		return ObjectBase(*(double*)data != v.to_double());
	case yt::Runtime::ObjectBase::Char:
		return ObjectBase(*(char*)data != *(char*)v.data);
	case yt::Runtime::ObjectBase::String:
		return ObjectBase(*(std::string*)data != v.to_string());
	default:
		throw std::runtime_error("ObjectBase yt::Runtime::ObjectBase::operator!=(const ObjectBase & v) const ");
	}
}
ObjectBase yt::Runtime::ObjectBase::operator>(const ObjectBase & v) const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return ObjectBase(*(int32_t*)data > v.to_int());
	case yt::Runtime::ObjectBase::Long:
		return ObjectBase(*(int64_t*)data > v.to_long());
	case yt::Runtime::ObjectBase::Double:
		return ObjectBase(*(double*)data > v.to_double());
	case yt::Runtime::ObjectBase::Char:
		return ObjectBase(*(char*)data > *(char*)v.data);
	case yt::Runtime::ObjectBase::String:
		return ObjectBase(*(std::string*)data > v.to_string());
	default:
		throw std::runtime_error("ObjectBase yt::Runtime::ObjectBase::operator>(const ObjectBase & v) const ");
	}
}
ObjectBase yt::Runtime::ObjectBase::operator<(const ObjectBase & v) const
{
	switch (type)
	{
	case yt::Runtime::ObjectBase::Int:
		return ObjectBase(*(int32_t*)data < v.to_int());
	case yt::Runtime::ObjectBase::Long:
		return ObjectBase(*(int64_t*)data < v.to_long());
	case yt::Runtime::ObjectBase::Double:
		return ObjectBase(*(double*)data < v.to_double());
	case yt::Runtime::ObjectBase::Char:
		return ObjectBase(*(char*)data < *(char*)v.data);
	case yt::Runtime::ObjectBase::String:
		return ObjectBase(*(std::string*)data < v.to_string());
	default:
		throw std::runtime_error("ObjectBase yt::Runtime::ObjectBase::operator<(const ObjectBase & v) const ");
	}
}