#include "../HPP/Object.hpp"
using namespace yt::Runtime;
Value yt::Runtime::Value::copy() const
{
	Value ret;
	ret.data = data;
	ret.user_count = new size_t(1);
	return ret;
}

void yt::Runtime::Value::_check()
{
	if (*user_count == 0)
	{
		delete data;
		delete user_count;
	}
}

void yt::Test::object_test()
{
	Value ob2;
	Value obj(pos(1,23));
	ob2 = obj;
}
