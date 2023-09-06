/*-----------------------------------------------------------
Module: Patient
Filename: Patient.cpp
Version 1.1
Author	Kevin Phan
-----------------------------------------------------------*/

#include <iostream>
#include <cstring>
#include <string>
#include "Patient.h"
#include "utils.h"

using namespace std;
namespace sdds
{
	Patient::Patient(int t_num, bool flag)
	{
		theTicket = t_num;
		p_name = nullptr;
		OHIP = 0;
		IOFlag = flag;
	}

	Patient::~Patient()
	{
		delete[] p_name;
		p_name = nullptr;
	}

	bool Patient::fileIO() const
	{
		return IOFlag;
	}

	void Patient::fileIO(bool flag)
	{
		IOFlag = flag;
	}

	void Patient::setArrivalTime()
	{
		theTicket.resetTime();
	}

	bool Patient::operator == (char C) const
	{
		if (this->type() == C)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Patient::operator ==(const Patient& P) const
	{
		if (this->type() == P.type())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int Patient::number() const
	{
		return theTicket.number();
	}

	Patient::operator Time() const
	{
		return theTicket;
	}

	ostream& Patient::csvWrite(std::ostream& ostr)const
	{
		ostr << type() << ",";
		ostr << p_name << "," << OHIP << ",";

		theTicket.Ticket::csvWrite(ostr);
		return ostr;
	}

	istream& Patient::csvRead(std::istream& istr)
	{	
		char delim = ',';

		delete[] p_name;
		p_name = nullptr;

		p_name = getcstr(nullptr, istr, delim);

		istr >> OHIP;
		istr.ignore(10, ',');
		
		theTicket.Ticket::csvRead(istr);
		return istr;
	}

	std::ostream& Patient::write(std::ostream& ostr)const
	{
		ostr << theTicket << endl;
		if (strlen(p_name) > 25)
		{
			for (int i = 0; i < 25; ++i)
			{
				ostr << p_name[i];
			}
		}
		else
		{
			ostr << p_name;
		}
		ostr << ", OHIP: " << OHIP;
		return ostr;
	}

	std::istream& Patient::read(std::istream& istr)
	{
		delete[] p_name;
		p_name = nullptr;
		p_name = getcstr("Name: ", istr, '\n');
		OHIP = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ", true);
		return istr;
	}
}