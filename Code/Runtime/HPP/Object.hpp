#pragma once
#include "../../Content/Environment.hpp"
namespace Simcc
{
	namespace Runtime
	{
		class Object
		{
		public:
			Object() :pos(Environment::stack_block->pc){
			}
			virtual std::string to_string() const { return ""; }
			virtual ~Object() {}
		protected:
			template<typename _T>
			_T& get_value()const
			{
				return *(_T*)Environment::stack_block->find(pos);
			}
			size_t type;
			// 0- int ,1-long 2-char 3-string 4- double 5-bool
			size_t pos;
		private:
		};
		//基本类型
		class Basic final:public Object 
		{
		public:
			Basic(int v)
			{
				Environment::stack_block->push(v);
				type = 0;
			}
			Basic(int64_t v)
			{
				Environment::stack_block->push(v);
				type = 1;
			}
			Basic(const char * c_str):Basic(std::string(c_str))
			{}
			Basic(const std::string & str)
			{
				Environment::stack_block->push(str);
				type = 3;
			}
			Basic(char ch)
			{
				Environment::stack_block->push(ch);
				type = 2;
			}
			Basic(double d) {
				Environment::stack_block->push(d);
				type = 4;
			}
			Basic(bool b)
			{
				Environment::stack_block->push(b);
				type = 5;
			}
			Basic(const Basic &bas)
			{
				switch (bas.type)
				{
				case 0:
					Environment::stack_block->push(bas.get_value<int>());
					break;
				case 1:
					Environment::stack_block->push(bas.get_value<int64_t>());
					break;
				case 2:
					Environment::stack_block->push(bas.get_value<char>());
					break;
				case 3:
					Environment::stack_block->push(bas.get_value<std::string>());
					break;
				case 4:
					Environment::stack_block->push(bas.get_value<double>());
					break;
				case 5:
					Environment::stack_block->push(bas.get_value<bool>());
					break;
				default:
					throw std::runtime_error("unkown type!");
					break;
				}
			}
			//==============init==============================
			std::string to_string()const override;

		private:
		};
	}
}