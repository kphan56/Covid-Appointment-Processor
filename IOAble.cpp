/*-----------------------------------------------------------
Module: IOAble
Filename: IOAble.cpp
Version 1.0
Author	Kevin Phan
-----------------------------------------------------------*/

#include "IOAble.h"

using namespace std;

namespace sdds
{
	istream& operator >>(std::istream& is, IOAble& IA)
	{
		IA.read(is);
		return is;
	}
	ostream& operator <<(std::ostream& os, const IOAble& OA)
	{
		OA.write(os);
		return os;
	}
}
