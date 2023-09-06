/*-----------------------------------------------------------
Module: Time
Filename: Time.cpp
Version 1.1
Author	Kevin Phan
-----------------------------------------------------------*/

#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds {

	Time::Time(unsigned int min)
	{
		m_min = min;
		hour = 0;
		minutes = 0;
	}

	std::ostream& operator<<(std::ostream& ostr, const Time& D)
	{
		D.write(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Time& D)
	{
		D.read(istr);
		return istr;
	}

	Time::operator int()const
	{
		return m_min;
	}

	Time::operator unsigned int()const 
	{
		return m_min;
	}

	Time& Time::setToNow()
	{
		*this = getTime();
		return *this;
	}

	std::ostream& Time::write(std::ostream& ostr) const
	{
		ostr.fill('0');
		ostr.width(2);
		ostr << m_min / 60 << ":";
		ostr.width(2);
		ostr << m_min % 60;
		return ostr;
	}

	std::istream& Time::read(std::istream& istr)
	{
		char delim = '\0';

		istr >> hour >> delim >> minutes; 
		if (hour < 0)
		{
			istr.setstate(ios::failbit);
		}

		if (delim != ':')
		{
			istr.setstate(ios::failbit);
		}

		if (minutes < 0)
		{
			istr.setstate(ios::failbit);
		}


		this->m_min = (hour * 60) + minutes;

		return istr;
	}

	Time& Time::operator-=(const Time& D)
	{
		if ((this->m_min) > (D.m_min))
		{
			this->m_min = (this->m_min) - (D.m_min);
		}
		else if ((this->m_min) < (D.m_min))
		{
			this->m_min = this->m_min + (1440 * (1 + (D.m_min / 1440))) - D.m_min;
		}

		return *this;
	}

	Time Time::operator-(const Time& D)const
	{
		Time T = *this;
		T -= D.m_min;
		return T;
	}

	Time& Time::operator+=(const Time& D)
	{
		this->m_min = this->m_min + D.m_min;
		return *this;
	}

	Time Time::operator+(const Time& D)const
	{
		Time T = D; 
		T += this->m_min; 
		return T;
	}

	Time& Time::operator=(unsigned int val)
	{
		this->m_min = val;
		return *this;
	}

	Time& Time::operator *= (unsigned int val)
	{
		this->m_min = this->m_min * val;
		return *this;
	}

	Time Time::operator *(unsigned int val)const
	{
		Time T = *this;
		T *= val;
		return T;
	}

	Time& Time::operator /= (unsigned int val)
	{
		this->m_min = this->m_min / val;
		return *this;
	}

	Time Time::operator /(unsigned int val)const
	{
		Time T = *this;
		T /= val;
		return T;
	}
}