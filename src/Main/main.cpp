#include "..\Parser\HPP\Function.hpp"
#include "../Parser/HPP/Block.hpp"
#include "../Test/HPP/TObject.hpp"
#include "../Runtime/HPP/Run.hpp"
#include <fstream>
#include <time.h>
#include <Windows.h>
using namespace Simcc::Runtime;
int main(int argc,char* argv[])
{
	try
	{
		if (argc != 2)
			throw std::runtime_error("invaild input");
		Init(argv[1]);
		CreateFunctionTable();
		time_t s = clock();
		Execute();
		std::cin.get();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	Sleep(1000000);
	return 0;
}