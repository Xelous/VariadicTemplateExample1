#pragma once

#include "Foo.h"

void bar()
{
	auto f = Xelous::Foo::Create("C:\\code\\blog2.txt");
	f->Output("This is the end of the world", "as we know it.");
	f->Output(1, 2, 3, 4, 5, 6, 7, std::string("Michael"));
}
