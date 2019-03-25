// MTT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

#include "Foo.h"
#include "Bar.h"

template<typename Number>
auto sum(const Number& num)
{
	return num;
}

template<typename Number, typename ...Others>
auto sum(const Number& num, Others... others)
{
	return num + sum(others...);
}

template<typename OutputItem>
void Output(const OutputItem& output)
{
	std::cout << output << "\r\n";
}

template<typename OutputItem, typename ...Others>
void Output(const OutputItem& output, Others... others)
{
	std::cout << output << "\r\n";
	Output(others...);
}

int main()
{
	auto result = sum(1, 2, 3, 4, 5);
	std::cout << result << "\r\n";

	auto result2 = sum(1.1, 2.2, 3.3, 4.4, 5.5);
	std::cout << result2 << "\r\n";

	Output("Hello World");
	Output(42);
	Output("Hello World", 42);
	Output("Xelous says hello", std::string("Santa Says goodbye"));

	Xelous::Foo::Get()->Output("Fishy");
	Xelous::Foo::Get()->Output(1, 2, 3, 4);

	//auto f = Xelous::Foo::Create();
	//f->Output(10, 11, 12, 13, 14);
	//f->Output("John", "Paul", "George", "Ringo");
	//f->Output("Temperature", 100, std::string("hot"));

	bar();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
