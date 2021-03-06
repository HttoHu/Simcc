#pragma once
// By 胡远韬 Simcc Hu
/*
* There are six classed in the header file,
* the purpose of them is storing literal value in the analysis of scanner.
*/
#include "Token.hpp"
namespace Simcc
{
	namespace Lexer
	{
		class VInt :public Token
		{
		public:
			VInt(int v) :Token(TLiteralInt), value(v) {}
			std::string to_string()const override
			{
				return "<VInt: " + std::to_string(value) + ">";
			}
			void* get_value()override
			{
				return (void*)&value;
			}
			const void* const get_value()const override
			{
				return (void*)&value;
			}
		private:
			int value;
		};
		class VDouble :public Token
		{
		public:
			VDouble(double v) :Token(TLiteralDouble), value(v) {}
			std::string to_string()const override
			{
				return "<vdouble: " + std::to_string(value) + ">";
			}
			void* get_value()override
			{
				return (void*)&value;
			}
			const void* const get_value()const override
			{
				return (void*)&value;
			}
		private:
			double value;
		};
		class VLong :public Token
		{
		public:
			VLong(long v) :Token(TLiteralLong), value(v) {}
			std::string to_string()const override
			{
				return "<vdouble: " + std::to_string(value) + ">";
			}
			void* get_value()override
			{
				return (void*)&value;
			}
			const void* const get_value()const override
			{
				return (void*)&value;
			}
		private:
			int64_t value;
		};
		class VString :public Token
		{
		public:
			VString(std::string v) :Token(TLiteralString), value(v) {}
			std::string to_string()const override
			{
				return "<vstring:" + value + ">";
			}
			void* get_value()override
			{
				return (void*)&value;
			}
			const void* const get_value()const override
			{
				return (void*)&value;
			}
		private:
			std::string value;
		};
		class VChar :public Token
		{
		public:
			VChar(char v) :Token(TLiteralChar), value(v) {}
			std::string to_string()const override
			{
				return "<vchar: " + std::string(1,value) + ">";
			}
			void* get_value()override
			{
				return (void*)&value;
			}
			const void* const get_value()const override
			{
				return (void*)&value;
			}
		private:
			char value;
		};
	}
}
