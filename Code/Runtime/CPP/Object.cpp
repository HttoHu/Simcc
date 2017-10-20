#include "../HPP/Object.hpp"
using namespace yt::Runtime;

Object yt::Runtime::Object::copy() const
{
	Object ret;
	ret.data = data;
	ret.user_count = new size_t(1);
	return ret;
}

void yt::Runtime::Object::_check()
{
	if (*user_count == 0)
	{
		delete data;
		delete user_count;
	}
}

void yt::Test::object_test()
{
	Object ob2;
	Object obj(pos(1,23));
	ob2 = obj;
}
