#pragma once
#include <string>
namespace yt
{
	namespace Runtime
	{
		class Object {
		public:
			Object() :data(nullptr), user_count(new size_t(1)) {}
			template <typename ValueType>
			Object(const ValueType& vt) : data(new ValueType(vt)), user_count(new size_t(1)) {}
			Object(const char * c_str) :Object(std::string(c_str)) {}
			Object(const Object & obj) {
				++*obj.user_count;
				data = obj.data;
				user_count = obj.user_count;
			}
			Object& operator= (const Object & obj) {
				++*obj.user_count;
				--*user_count;
				_check();
				user_count = obj.user_count;
				data = obj.data;
				return *this;
			}
			~Object() {
				--*user_count;
				_check();
			}
			//=========================
			Object copy()const;
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
