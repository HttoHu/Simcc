#include "..\Parser\HPP\Function.hpp"
#include "../Parser/HPP/Block.hpp"
#include "../Runtime/HPP/Run.hpp"
#include <fstream>
#include <time.h>
#include <Windows.h>
using namespace Simcc::Runtime;
/*

#ifndef _DEBUG
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
#else

int main(int argc, char* argv[])
{
	try
	{
		Init("Text.cc");
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
*/
int main()
{
	{
		Simcc::Runtime::StackMemory sm;
	long a=clock();
	for (int i=0;i<100;i++)
		sm.push_temp("dfa"+std::to_string(i));
	std::cout << *(std::string*)sm.find(5*32)<<std::endl;//*(std::string*)sm.find(sizeof(std::string)*3) << std::endl;
	//long b = clock();
	//
//	std::cout << double(b - a) / CLK_TCK;
	}
	Sleep(1000000);

	return 0;
}
//#endif